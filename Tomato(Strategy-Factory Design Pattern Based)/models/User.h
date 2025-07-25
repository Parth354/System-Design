#ifndef USER_H
#define USER_H

#include<iostream>
#include "../models/Cart.h"
using namespace std;

class User {
private:
    int userId;
    string name;
    string address;
    Cart* cart;
public:
    User(int id, const string &name, const string &address) : userId(id), name(name), address(address) {
        cart = new Cart();
    }

    ~User() {
        delete cart;
        cout << "Destroying User: " << name << endl;
    }

    int getUserId() const {
        return userId;
    }

    string getName() const {
        return name;
    }

    void setName(const string &name) {
        this->name = name;
    }

    string getAddress() const {
        return address;
    }

    void setAddress(const string &address) {
        this->address = address;
    }

    Cart* getCart() const {
        return cart;
    }
};

#endif