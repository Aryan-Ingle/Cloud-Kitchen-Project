#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <iostream>
#include <string>
using namespace std;

struct MenuItem
{
    int foodID;
    string foodName;
    float price, rating;
};

struct OrderItem
{
    int foodID;
    string foodName;
    float price;
    int quantity;
};

struct Order
{
    int orderID;
    string customerID, customerName;
    OrderItem items[10];
    int itemCount;
    float totalAmount;
    int customerNode;
    string orderType, status;
    int priority;
};

struct OrderNode
{
    Order order;
    OrderNode *next;
};

extern MenuItem menu[50];
extern int menuCount;
extern OrderNode *head;
extern int nextOrderID;

void initializeMenu();
void displayMenu();
void addFood();
void removeFood();
void updatePrice();
void updateRating();
void updateMenu();
void placeOrder(string, string);
void customerLogin();
void kitchenLogin();
void displayOrder(Order);
void viewMyOrders(string);
void viewMyDistance(string);
void viewOrdersByPriority();
void viewCustomersDistance();
void manageDeliveryStatus();

#endif