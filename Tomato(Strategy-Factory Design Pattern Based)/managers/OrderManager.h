#ifndef ORDER_MANAGER_H
#define ORDER_MANAGER_H

#include<vector>
#include<iostream>
#include "../models/Order.h"
using namespace std;

class OrderManager {
    private:
    vector<Order*> orders;
    static OrderManager* instance;
    OrderManager(){};
    public:
    static OrderManager* getInstance(){
        if(!instance){
            instance = new OrderManager();
        }
        return instance;
    };

    void addOrder(Order* order){
        orders.push_back(order);
    }
    void listOrders(){
        cout<<"\n ---------All Orders--------"<<endl;
        for(auto order : orders){
            order->printOrderDetails();
            cout<<endl;
        }
    }
};

OrderManager* OrderManager::instance = nullptr;

#endif