#include<iostream>
#include<vector>
#include<string>
#include<ctime>
#include<algorithm>
using namespace std;

class NotificationService;

class INotification {
    public:
    virtual string getContent() =0;
};

class SimpleNotification : public INotification {
    string content;
    public:
    SimpleNotification(const string& content) : content(content) {}
    
    string getContent() override {
        return content;
    }
};

class INotificationDecorator : public INotification {
    protected:
    INotification* notification;
    public:
    INotificationDecorator(INotification* notification) : notification(notification) {}
};

class TimestampDecorator : public INotificationDecorator {
    public:
    TimestampDecorator(INotification* notification) : INotificationDecorator(notification) {}   
    string getContent() override {
        return notification->getContent() + " [Timestamp: " + to_string(time(0)) + "]";
    }
};
class SignatureDecorator : public INotificationDecorator {
    private:
    string signature;
    public:
    SignatureDecorator(INotification* notification, const string& signature) : INotificationDecorator(notification), signature(signature) {}
    string getContent() override {
        return notification->getContent() + " [Signature: " + signature + "]";
    }
};


// Observer Pattern Components

class IObserver {
    public:
    virtual void update() = 0;
};
class IObservable {
    public:
    virtual void addObserver(IObserver* observer) = 0;
    virtual void removeObserver(IObserver* observer) = 0;
    virtual void notifyObservers() = 0;
};

class NotificationObservable : public IObservable {
    INotification* currentNotification;
    vector<IObserver*> observers;
    public:
    NotificationObservable() : currentNotification(nullptr) {}
    void addObserver(IObserver* observer) override {
        observers.push_back(observer);
    }
    void removeObserver(IObserver* observer) override {
        observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
    }
    void notifyObservers() override {
        for (IObserver* observer : observers) {
            observer->update();
        }
    }
    void setNotification(INotification* notification) {
        currentNotification = notification;
        notifyObservers();
    }
    string getNotificationContent() {
        return  currentNotification->getContent();
    }
    INotification* getNotification() {
        return currentNotification;
    }
};


// Notification Service
class NotificationService {
    NotificationObservable* observable;
    static NotificationService* instance;
    vector<INotification*> notifications;
    NotificationService() {
        observable = new NotificationObservable();
    }
    public:
    static NotificationService* getInstance() {
        if(instance == nullptr){
            instance = new NotificationService();
        }
        return instance;
    }

    NotificationObservable* getObservable() {
        return observable;
    }

    void sendNotification(INotification* notification){
         observable->setNotification(notification);
         notifications.push_back(notification);
    }
    ~NotificationService() {
        delete observable; 
    }
};

NotificationService* NotificationService::instance = nullptr;

//Concrete Observer Implementation 
class Logger : public IObserver{
    NotificationObservable* notificationObservable;
    public:
    Logger() {
        this->notificationObservable = NotificationService::getInstance()->getObservable();
        this->notificationObservable->addObserver(this);
    }
    void update() override {
        cout<<"Logging new Notification : \n "<< notificationObservable->getNotificationContent()<<endl;
    }
};

// Notification Strategy 
class INotificationStrategy {
    public :
    virtual void sendNotification(const string& content) = 0;
};
class EmailNotificationStrategy : public INotificationStrategy {
    public:
    void sendNotification(const string& content) override {
        cout << "Sending Email Notification: " << content << endl;
    }
};
class SMSNotificationStrategy : public INotificationStrategy {
    public:
    void sendNotification(const string& content) override {
        cout << "Sending SMS Notification: " << content << endl;
    }
};

class NotificationEngine : public IObserver{
    NotificationObservable* notificationObservable;
    vector<INotificationStrategy*> strategies;
    public:
    NotificationEngine(){
        this->notificationObservable= NotificationService::getInstance()->getObservable();
        this->notificationObservable->addObserver(this);
    }
    
    void addNotificationStrategy(INotificationStrategy* strategy) {
        strategies.push_back(strategy);
    }
    void update() override {
        string notificationContent = notificationObservable->getNotificationContent();
        for(auto notificationStrategy : strategies){
            notificationStrategy->sendNotification(notificationContent);
        }
    }
};

int main(){
    NotificationService* notificationService = NotificationService::getInstance();
    Logger* logger = new Logger();
    NotificationEngine* notificationEngine = new NotificationEngine();
    notificationEngine->addNotificationStrategy(new EmailNotificationStrategy());
    INotification* notification = new SimpleNotification("Hello");
    notification = new TimestampDecorator(notification);
    notificationService->sendNotification(notification);
    delete logger;
    delete notificationEngine;
    return 0;
}
