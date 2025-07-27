#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

class ISubscriber;

class IChannel {
    public:
        virtual void subscribe(ISubscriber* subscriber)=0;
        virtual void unsubscribe(ISubscriber* subscriber) =0 ;
        virtual void notifySubscribers() =0;
        virtual ~IChannel() {}
};

class ISubscriber {
    public:
        virtual void update() = 0;
        virtual ~ISubscriber() {}
};

class Channel : public IChannel {
    private: 
        string name;
        vector<ISubscriber*> subscribers;
        string latestVideo;
    public:
        Channel(const string& name) {
            this-> name = name;
        }
        void subscribe(ISubscriber* subscriber ) override {
            if(find(subscribers.begin(),subscribers.end(), subscriber) == subscribers.end()) {
                subscribers.push_back(subscriber);
                cout << "Subscribed to " << name << endl;
            }
            else {
                cout<<"Already subscribed to "<<name<<endl;
            }
        }
        void unsubscribe(ISubscriber* subscriber) override{
            if(find(subscribers.begin(), subscribers.end(), subscriber) != subscribers.end()) {
                subscribers.erase(remove(subscribers.begin(), subscribers.end(), subscriber), subscribers.end());
            } else {
                cout << "Subscriber not found." << endl;
            }
        }
        void notifySubscribers() override {
            for(auto& subscriber : subscribers) {
                subscriber->update();
            }
        }
        void uploadVideo(const string& video) {
            latestVideo = video;
            cout << "New video uploaded: " << latestVideo << endl;
            notifySubscribers();
        }
        string getLatestVideo() const {
            return latestVideo;
        }
};

class Subscriber : public ISubscriber {
    private:
        string name;
        Channel* channel;
    public:
        Subscriber(const string& name, Channel* channel) {
            this->name = name;
            this->channel = channel;
            channel->subscribe(this);
        }
        void update() override {
            cout << "Notification for " << name << ": New video is available!" <<channel->getLatestVideo()<< endl;
        }
        ~Subscriber() {
            channel->unsubscribe(this);
        }
    };

int main() {
Channel* channel = new Channel("Cosmic Jewels");
Subscriber* s1= new Subscriber("Alice", channel);
Subscriber* s2 = new Subscriber("Bob", channel);
channel->uploadVideo("Latest Collection of Cosmic Jewels");
channel->unsubscribe(s1);
channel->uploadVideo("New Cosmic Jewelry Designs");
delete s1;
delete s2;
channel->uploadVideo(" Designs");
return 0;   
}