#ifndef CART_H
#define CART_H

#include<iostream>
#include<string>
#include<vector>
#include "../models/Restaurant.h"
#include "../models/MenuItem.h"
using namespace std;

class Cart{
    private:
        Restaurant* restaurant;
        vector<MenuItem> items;
    public:
       Cart() : restaurant(nullptr) {}

       void addItem(const MenuItem& item){
        if(!restaurant) {
            cerr << "Cart : Set a restaurant before adding items" <<endl;
            return;
        }
        items.push_back(item);
       }

       double getTotalCost() const {
        double total = 0.0;
        for(const auto& it: items){
            total += it.getPrice();
        }
        return total;
       }

       bool isEmpty(){
        return (!restaurant||items.empty());
       }
       void setRestaurant(Restaurant* res) {
        restaurant = res;
       }
       Restaurant* getRestaurant() const {
        return restaurant;
       }
       const vector<MenuItem>& getItems() const {
        return items;
       }

    void clear() {
        items.clear();
        restaurant = nullptr;
    }

};

#endif // CART_H