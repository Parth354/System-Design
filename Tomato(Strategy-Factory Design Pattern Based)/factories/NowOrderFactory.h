#ifndef NOW_ORDER_FACTORY_H
#define NOW_ORDER_FACOTRY_H

#include "../factories/OrderFactory.h"
#include "../models/DeliveryOrder.h"
#include "../models/PickupOrder.h"
#include "../utils/TimeUtils.h"
using namespace std;

class NowOrderFactory : public OrderFactory {
    public:
        NowOrderFactory() {}
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
            order->setPaymentStrategy(paymentStrategy);
            order->setScheduled(TimeUtils::getCurrentTime());
            order->setTotal(cart->getTotalCost());
            return order;
        }
};

#endif //NowOrderFactory.h