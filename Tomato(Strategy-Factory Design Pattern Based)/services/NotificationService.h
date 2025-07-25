#ifndef NOTIFICATION_SERVICE_H
#define NOTIFICATION_SERVICE_H

#include<iostream>
#include "../models/Order.h"
using namespace std;

class NotificationService{
    public:
        static void notify(Order* order) {
            cout<<"\n Notification New "<<order->getType()<<" Order Placed for "<<order->getUser()->getName()<<endl;
            cout<<"========================================================"<<endl;
            order->printOrderDetails();
            cout<<"\n";
            cout<<"========================================================"<<endl;
            cout<<"Scheduled For : "<<order->getScheduled()<<endl;
            cout<<"Payment : Done ✔" <<endl;
            cout<<"========================================================"<<endl;
        }
};

#endif