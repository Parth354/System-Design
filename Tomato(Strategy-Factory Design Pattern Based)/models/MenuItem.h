#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include<iostream>
#include<string>
using namespace std;

class MenuItem {
    string name;
    string code;
    double price;
    public:
    MenuItem(string name, string code, double price) {
        this->name = name;
        this->code = code;
        this->price = price;
    }
    string getName() const {
        return name;
    }
    string getCode() const {
        return code;
    }
    double getPrice() const {
        return price;
    }
    void setPrice(double price) {
        this->price = price;
    }
    
    void setName(string name){
        this->name = name;
    }
    void setCode(string code){
        this->code = code;
    }
};

#endif