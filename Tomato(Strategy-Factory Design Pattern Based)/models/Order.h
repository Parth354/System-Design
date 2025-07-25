#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <string>
#include <vector>
#include "../models/User.h"
#include "../models/MenuItem.h"
#include "../utils/TimeUtils.h"
#include "../strategies/PaymentStrategy.h"
using namespace std;

class Order {
    protected:
        static int nextOrderId;
        int orderId;
        User* user;
        Restaurant* restaurant;
        vector<MenuItem> items;
        PaymentStrategy* paymentStrategy;
        double total;
        string scheduled;
    
    public:
        Order(): user(nullptr), restaurant(nullptr), paymentStrategy(nullptr), total(0.0), scheduled(""), orderId(++nextOrderId) {}

    virtual ~Order() {
        delete paymentStrategy;
    }

    bool processPayment() {
        if(paymentStrategy) {
            paymentStrategy->pay(total);
            return true;
        }else{
            cout<<"Please choose a payment mode first."<<endl;
            return false;
        }
    }

    virtual string getType() const =0;

    int getOrderId() const {
        return orderId;
    }

    void setUser(User* user) {
        this->user = user;
    }

    User* getUser() const {
        return user;
    }

    void setRestaurant(Restaurant* restaurant) {
        this->restaurant = restaurant;
    }
    Restaurant* getRestaurant() const {
        return restaurant;
    }

    void addItem(const MenuItem& item) {
        if(restaurant) {
            items.push_back(item);
            total += item.getPrice();
        } else {
            cerr << "Order: Set a restaurant before adding items" << endl;
        }
    }
    double getTotal() const {
        return total;
    }
    void setPaymentStrategy(PaymentStrategy* strategy) {
        if (strategy) {
            delete paymentStrategy; // Clean up previous strategy
            paymentStrategy = strategy;
        } else {
            cerr << "Invalid payment strategy." << endl;
        }
    }
    PaymentStrategy* getPaymentStrategy() const {
        return paymentStrategy;
    }
    const vector<MenuItem>& getItems() const {
        return items;
    }
    void setScheduled(const string& time) {
        scheduled = time;
    }
    string getScheduled() const {
        return scheduled;
    }
    virtual void printOrderDetails() const {
        cout << "Order ID: " << orderId << endl;
        cout << "User: " << (user ? user->getName() : "Unknown") << endl;
        cout << "Restaurant: " << (restaurant ? restaurant->getName() : "Unknown") << endl;
        cout << "Items: " << endl;
        for (const auto& item : items) {
            cout << "- " << item.getName() << ": $" << item.getPrice() << endl;
        }
        cout << "Total: $" << total << endl;
        cout << "Scheduled Time: " << scheduled << endl;
    }

    void setTotal(double total) {
        this->total = total;
    }

    void setItems(const vector<MenuItem>& items) {
        this->items = items;
        total = 0.0;
        for (const auto& item : items) {
            total += item.getPrice();
        }
    }
};

int Order::nextOrderId = 0;

#endif // ORDER_H