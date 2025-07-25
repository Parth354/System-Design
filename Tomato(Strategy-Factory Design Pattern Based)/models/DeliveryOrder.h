#ifndef DELIVERY_ORDER_H
#define DELIVERY_ORDER_H

#include <iostream>
#include <string>
#include "../models/Order.h"
using namespace std;

class DeliveryOrder : public Order {
    private:
        string userAddress;
    
    public:
        DeliveryOrder() : userAddress("") {
            // Default constructor
        }

        string getType() const override {
            return "Delivery";
        }
        void setUserAddress(const string& addr){
            userAddress= addr;
        }

        string getUserAddress() const {
            return userAddress;
        }

};

#endif