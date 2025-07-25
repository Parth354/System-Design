#ifndef NOW_SCHEULED_FACTORY_H
#define NOW_SCHEDULED_FACOTRY_H

#include "../factories/OrderFactory.h"
#include "../models/DeliveryOrder.h"
#include "../models/PickupOrder.h"
#include "../utils/TimeUtils.h"
using namespace std;

class ScheduledOrderFactory : public OrderFactory {
    private:
        string scheduleTime;
    public:
        ScheduledOrderFactory(const string& scheduleTime) : scheduleTime(scheduleTime) {}
        
        Order* createOrder(User* user , Cart* cart , Restaurant* restaurant , const vector<MenuItem>& menuItems , PaymentStrategy* paymentStrategy , const string& orderType) override {
        
            Order* order  = nullptr;
            if(orderType ==  "Delivery"){
                auto deliveryOrder = new DeliveryOrder();
                deliveryOrder->setUserAddress(user->getAddress());
                order= deliveryOrder;
            }else{
                auto pickupOrder = new PickupOrder();
                order = pickupOrder;
                pickupOrder->setRestaurantAddress(restaurant->getLocation());
            }
            order->setUser(user);
            order->setRestaurant(restaurant);
            order->setItems(menuItems);
            order->setScheduled(scheduleTime);
            order->setPaymentStrategy(paymentStrategy);
            order->setTotal(cart->getTotalCost());
            return order;
        }
        void setScheduleTime(const string& scheduleTime){
            this->scheduleTime = scheduleTime;
        }
};

#endif //ScheduledOrderFactory.h