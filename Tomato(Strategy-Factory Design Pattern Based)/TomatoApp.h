#ifndef TOMATO_H
#define TOMATO_H

#include<vector>
#include<string>
#include "models/User.h"
#include "models/Restaurant.h"
#include "models/Cart.h"
#include "managers/RestaurantManager.h"
#include "managers/OrderManager.h"
#include "strategies/PaymentStrategy.h"
#include "strategies/CreditCardPaymentStrategy.h"
#include "strategies/UpiPaymentStrategy.h"
#include "factories/OrderFactory.h"
#include "factories/NowOrderFactory.h"
#include "factories/ScheduledOrderFactory.h"
#include "services/NotificationService.h"
#include "utils/TimeUtils.h"

using namespace std;
class TomatoApp {
    public:
        TomatoApp() {
            // Initialize the application, load data, etc.
            cout << "Welcome to Tomato App!" << endl;
            initializeRestaurants();
        }
        void initializeRestaurants() {
            // Example initialization of restaurants
            Restaurant* res1 = new Restaurant("Pizza Place", "Downtown");
            res1->addMenuItem(MenuItem("Margherita Pizza", "P001", 8.99));
            res1->addMenuItem(MenuItem("Pepperoni Pizza", "P002", 9.99));

            Restaurant* res2 = new Restaurant("Burger Joint", "Uptown");
            res2->addMenuItem(MenuItem("Cheeseburger", "B001", 5.99));
            res2->addMenuItem(MenuItem("Veggie Burger", "B002", 6.99));

            Restaurant* res3 = new Restaurant("Sushi Spot", "Downtown");
            res3->addMenuItem(MenuItem("California Roll", "S001", 12.99));
            res3->addMenuItem(MenuItem("Spicy Tuna Roll", "S002",12.22));

            RestaurantManager* restaurantManager = RestaurantManager::getInstance();
            restaurantManager->addRestaurant(res1);
            restaurantManager->addRestaurant(res2);
            restaurantManager->addRestaurant(res3);
        }

        vector<Restaurant*> searchRestaurantsByLocation(const string& location) {
            return RestaurantManager::getInstance()->searchByLocation(location);
        }

        void selectRestaurant(User* user , Restaurant* restaurant){
            Cart* cart = user->getCart();
            cart->setRestaurant(restaurant);
            cout << "Selected Restaurant: " << restaurant->getName() << endl;
        }

        void addToCart(User* user , const string& itemCode){
            Restaurant* restaurant = user-> getCart()->getRestaurant();
            if (!restaurant) {
                cerr << "Please select a restaurant first." << endl;
                return;
            }
            for(const auto&item : restaurant->getMenu()){
                if(item.getCode() == itemCode) {
                    user->getCart()->addItem(item);
                    cout << "Added " << item.getName() << " to cart." << endl;
                    break;
                }
            }
        }

        Order* checkoutNow(User* user , const string& orderType , PaymentStrategy* paymentStrategy){
            return checkout(user, orderType, paymentStrategy, new NowOrderFactory() );
        }

        Order* checkoutScheduled(User* user , const string& orderType , PaymentStrategy* paymentStrategy, const string& scheduleTime){
            return checkout(user, orderType, paymentStrategy, new ScheduledOrderFactory(scheduleTime));
        }

        Order* checkout(User* user , const string& orderType , PaymentStrategy* paymentStrategy , OrderFactory* orderFactory) {
            if(user->getCart()->isEmpty()) {
                cerr << "Cart is empty. Please add items to the cart." << endl;
                return nullptr;
            }

            Cart* userCart = user->getCart();
            Restaurant* restaurant = userCart->getRestaurant();
            vector<MenuItem> itemsOrdered = userCart->getItems();
            double totalCost = userCart->getTotalCost();
            cout<< "Total Cost: $" << totalCost << endl;
            Order* order = orderFactory->createOrder(user, userCart, restaurant, itemsOrdered, paymentStrategy, orderType);
            OrderManager::getInstance()->addOrder(order);
            return order;
        }

        void payForOrder(User* user,Order* order) {
            bool paymentSuccess = order->processPayment();
            if (paymentSuccess) {
                NotificationService* notification = new NotificationService();
                notification->notify(order);
                user->getCart()->clear();
            }
        }

        void printUserCart(User* user) {
            Cart* cart = user->getCart();
            if (cart->isEmpty()) {
                cout << "Your cart is empty." << endl;
                return;
            }
            cout << "Cart Items for " << user->getName() << ":" << endl;
            for (const auto& item : cart->getItems()) {
                cout << "- " << item.getName() << " ($" << item.getPrice() << ")" << endl;
            }
            cout << "Total Cost: $" << cart->getTotalCost() << endl;
        }
        
};

#endif