#ifndef RESTAURANT_MANAGER_H
#define RESTAURANT_MANAGER_H

#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<mutex>
#include "../models/Restaurant.h"
using namespace std;

class RestaurantManager {
    private:
        // static std::mutex mtx;
        vector<Restaurant*> restaurants;
        static RestaurantManager* instance;
        RestaurantManager() {

        }
    public:
    static RestaurantManager* getInstance() {
        if (instance == nullptr) {
            // std::lock_guard<mutex> lock(mtx);
            if (instance == nullptr) {
                instance = new RestaurantManager();
            }
        }
        return instance;
    }

    void addRestaurant(Restaurant* res){
        restaurants.push_back(res);
    }

    vector<Restaurant*> searchByLocation(string loc){
        transform(loc.begin(),loc.end(),loc.begin(), ::tolower);
        vector<Restaurant*> result;
        for (auto& restaurant : restaurants) {
            string rl = restaurant->getLocation();
            transform(rl.begin(), rl.end(), rl.begin(), ::tolower);
            if (rl.find(loc) != string::npos) {
                result.push_back(restaurant);
            }
        }
        return result;
    }
};
// std::mutex RestaurantManager::mtx;
RestaurantManager* RestaurantManager::instance = new RestaurantManager();
#endif // RESTAURANT_MANAGER_H