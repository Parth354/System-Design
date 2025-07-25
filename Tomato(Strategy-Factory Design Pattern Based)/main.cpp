#include<iostream>
#include "TomatoApp.h"
using namespace std;

int main() {
    TomatoApp* tomato = new TomatoApp();

    User* user = new User(007,"James Bond","London");
    cout << "User Created: " << user->getName() << endl;

    vector<Restaurant*> restaurants = tomato->searchRestaurantsByLocation("Downtown");

    if(restaurants.empty()) {
        cout << " No Restaurants found in the specified location." << endl;
    }else{
        cout << "Restaurants found in Downtown:" << endl;
        for(const auto& restaurant : restaurants) {
            cout << " - " << restaurant->getName() << " at " << restaurant->getLocation() << endl;
        }

        // Select the first restaurant
        tomato->selectRestaurant(user, restaurants[0]);

        tomato->printUserCart(user);
        // Add items to cart
        tomato->addToCart(user, "P001"); // Margherita Pizza
        tomato->addToCart(user, "P002"); // Pepperoni Pizza

        // Checkout with Credit Card payment
        PaymentStrategy* paymentStrategy = new CreditCardPaymentStrategy("1234-5678-9876-5432");
        Order* order = tomato->checkoutNow(user, "Delivery", paymentStrategy);

        tomato->payForOrder(user,order);
        
        delete tomato;
        delete paymentStrategy;
    }
    return 0;
}