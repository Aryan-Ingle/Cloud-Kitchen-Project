#include <iostream>
#include <string>
#include "structures.h"
#include "queue.h"
#include "sort.h"
#include "graph.h"

using namespace std;

MenuItem menu[50];
int menuCount = 0;
OrderNode *head = NULL;
int nextOrderID = 101;

Queue normalQueue;
PriorityQueue priorityQueue;

// ---------- LINKED LIST ----------

void addOrder(Order order)
{
    OrderNode *n = new OrderNode;
    n->order = order;
    n->next = NULL;

    if(head == NULL)
        head = n;
    else
    {
        OrderNode *t = head;
        while(t->next != NULL)
            t = t->next;
        t->next = n;
    }
}

OrderNode* findOrder(int id)
{
    OrderNode *t = head;

    while(t != NULL)
    {
        if(t->order.orderID == id)
            return t;
        t = t->next;
    }

    return NULL;
}

// ---------- MENU ----------

void initializeMenu()
{
    menu[0] = {1, "Pizza", 250, 4.5};
    menu[1] = {2, "Burger", 150, 4.2};
    menu[2] = {3, "Biryani", 220, 4.8};
    menu[3] = {4, "Pasta", 180, 4.0};
    menu[4] = {5, "Sandwich", 120, 3.9};
    menuCount = 5;
}

void displayMenu()
{
    cout << "\nID\tFood\t\tPrice\tRating\n";

    for(int i = 0; i < menuCount; i++)
        cout << menu[i].foodID << "\t"
             << menu[i].foodName << "\t\t"
             << menu[i].price << "\t"
             << menu[i].rating << endl;
}

void addFood()
{
    if(menuCount == 50)
    {
        cout << "Menu full.\n";
        return;
    }

    MenuItem f;

    cout << "Food ID: ";
    cin >> f.foodID;

    if(findFood(f.foodID) != -1)
    {
        cout << "ID already exists.\n";
        return;
    }

    cin.ignore();
    cout << "Food name: ";
    getline(cin, f.foodName);

    cout << "Price and rating: ";
    cin >> f.price >> f.rating;

    if(f.price <= 0 || f.rating < 0 || f.rating > 5)
    {
        cout << "Invalid price or rating.\n";
        return;
    }

    menu[menuCount++] = f;
    cout << "Food added.\n";
}

void removeFood()
{
    int id;
    cout << "Food ID to remove: ";
    cin >> id;

    int i = findFood(id);

    if(i == -1)
    {
        cout << "Food not found.\n";
        return;
    }

    for(int j = i; j < menuCount - 1; j++)
        menu[j] = menu[j + 1];

    menuCount--;
    cout << "Food removed.\n";
}

void updatePrice()
{
    int id;
    float p;

    cout << "Food ID: ";
    cin >> id;

    int i = findFood(id);

    if(i == -1)
    {
        cout << "Food not found.\n";
        return;
    }

    cout << "New price: ";
    cin >> p;

    if(p <= 0)
    {
        cout << "Invalid price.\n";
        return;
    }

    menu[i].price = p;
    cout << "Price updated.\n";
}

void updateRating()
{
    int id;
    float r;

    cout << "Food ID: ";
    cin >> id;

    int i = findFood(id);

    if(i == -1)
    {
        cout << "Food not found.\n";
        return;
    }

    cout << "New rating (0-5): ";
    cin >> r;

    if(r < 0 || r > 5)
    {
        cout << "Invalid rating.\n";
        return;
    }

    menu[i].rating = r;
    cout << "Rating updated.\n";
}

void updateMenu()
{
    int c;

    do
    {
        cout << "\n1.Add Food  2.Remove Food\n";
        cout << "3.Update Price  4.Update Rating\n";
        cout << "5.Show Menu  6.Back\nChoice: ";
        cin >> c;

        switch(c)
        {
            case 1: addFood(); break;
            case 2: removeFood(); break;
            case 3: updatePrice(); break;
            case 4: updateRating(); break;
            case 5: displayMenu(); break;
        }
    } while(c != 6);
}

// ---------- DISPLAY ORDER ----------

void displayOrder(Order o)
{
    cout << "\nOrder ID: " << o.orderID
         << "\nCustomer: " << o.customerName
         << "\nType: " << o.orderType
         << "\nNode: " << o.customerNode
         << "\nStatus: " << o.status << endl;

    for(int i = 0; i < o.itemCount; i++)
        cout << o.items[i].foodName
             << " x " << o.items[i].quantity
             << " = Rs. "
             << o.items[i].price * o.items[i].quantity
             << endl;

    cout << "Total: Rs. " << o.totalAmount << endl;
}

// ---------- PLACE ORDER ----------

void placeOrder(string cid, string name)
{
    if(menuCount == 0)
    {
        cout << "Menu empty.\n";
        return;
    }

    Order o = {};
    o.orderID = nextOrderID;
    o.customerID = cid;
    o.customerName = name;

    displayMenu();

    int choice;

    do
    {
        if(o.itemCount == 10)
            break;

        int id, qty;

        cout << "Food ID (0 to finish): ";
        cin >> id;

        if(id == 0)
            break;

        int i = findFood(id);

        if(i == -1)
        {
            cout << "Invalid food ID.\n";
            continue;
        }

        cout << "Quantity: ";
        cin >> qty;

        if(qty <= 0)
        {
            cout << "Invalid quantity.\n";
            continue;
        }

        int k = o.itemCount++;

        o.items[k].foodID = menu[i].foodID;
        o.items[k].foodName = menu[i].foodName;
        o.items[k].price = menu[i].price;
        o.items[k].quantity = qty;

        o.totalAmount += menu[i].price * qty;

    } while(true);

    if(o.itemCount == 0)
    {
        cout << "No order created.\n";
        return;
    }

    cout << "Customer node (1-6): ";
    cin >> o.customerNode;

    if(o.customerNode < 1 || o.customerNode > 6)
    {
        cout << "Invalid node.\n";
        return;
    }

    int type;

    cout << "1.Normal  2.Express  3.VIP\nChoice: ";
    cin >> type;

    if(type < 1 || type > 3)
    {
        cout << "Invalid order type.\n";
        return;
    }

    if(type == 1)
    {
        o.orderType = "Normal";
        o.priority = 1;
    }
    else if(type == 2)
    {
        o.orderType = "Express";
        o.priority = 2;
    }
    else
    {
        o.orderType = "VIP";
        o.priority = 3;
    }

    o.status = "PLACED";
    o.orderID = nextOrderID++;

    addOrder(o);

    if(type == 1)
        normalQueue.enqueue(o.orderID);
    else
        priorityQueue.enqueue(o.orderID, o.priority);

    cout << "Order placed! ID: " << o.orderID
         << "\nTotal: Rs. " << o.totalAmount << endl;
}

// ---------- CUSTOMER FUNCTIONS ----------

void viewMyOrders(string cid)
{
    OrderNode *t = head;
    bool found = false;

    while(t != NULL)
    {
        if(t->order.customerID == cid)
        {
            displayOrder(t->order);
            found = true;
        }
        t = t->next;
    }

    if(!found)
        cout << "No orders found.\n";
}

void viewMyDistance(string cid)
{
    OrderNode *t = head;
    bool found = false;

    while(t != NULL)
    {
        if(t->order.customerID == cid &&
           t->order.status != "DELIVERED")
        {
            dijkstra(0, t->order.customerNode);
            found = true;
        }
        t = t->next;
    }

    if(!found)
        cout << "No active orders.\n";
}

void customerLogin()
{
    string id, name;

    cout << "Customer ID: ";
    cin >> id;
    cin.ignore();

    cout << "Customer name: ";
    getline(cin, name);

    int c;

    do
    {
        cout << "\nCUSTOMER DASHBOARD\n";
        cout << "1.Menu by Rating\n2.Menu by Price\n";
        cout << "3.Order Food\n4.View My Orders\n";
        cout << "5.View Delivery Distance\n6.Logout\nChoice: ";
        cin >> c;

        switch(c)
        {
            case 1: sortByRating(); displayMenu(); break;
            case 2: sortByPrice(); displayMenu(); break;
            case 3: placeOrder(id, name); break;
            case 4: viewMyOrders(id); break;
            case 5: viewMyDistance(id); break;
        }
    } while(c != 6);
}

// ---------- KITCHEN FUNCTIONS ----------

void viewOrdersByPriority()
{
    bool found = false;

    cout << "\nPRIORITY ORDERS\n";

    for(int i = 0; i < priorityQueue.getCount(); i++)
    {
        OrderNode *n = findOrder(priorityQueue.getAt(i));

        if(n != NULL && n->order.status != "DELIVERED")
        {
            displayOrder(n->order);
            found = true;
        }
    }

    cout << "\nNORMAL ORDERS (FIFO)\n";

    for(int i = normalQueue.getFrontIndex();
        i <= normalQueue.getRearIndex(); i++)
    {
        OrderNode *n = findOrder(normalQueue.getAt(i));

        if(n != NULL && n->order.status != "DELIVERED")
        {
            displayOrder(n->order);
            found = true;
        }
    }

    if(!found)
        cout << "No active orders.\n";
}

void viewCustomersDistance()
{
    OrderNode *t = head;

    while(t != NULL)
    {
        if(t->order.status != "DELIVERED")
        {
            cout << "\nOrder: " << t->order.orderID
                 << ", Customer: " << t->order.customerName
                 << ", Node: " << t->order.customerNode << endl;

            dijkstra(0, t->order.customerNode);
        }

        t = t->next;
    }
}

void manageDeliveryStatus()
{
    int id, c;

    cout << "Order ID: ";
    cin >> id;

    OrderNode *n = findOrder(id);

    if(n == NULL)
    {
        cout << "Order not found.\n";
        return;
    }

    if(n->order.status == "DELIVERED")
    {
        cout << "Already delivered.\n";
        return;
    }

    cout << "1.Cooking\n2.Out for Delivery\n3.Delivered\nChoice: ";
    cin >> c;

    if(c == 1)
        n->order.status = "COOKING";
    else if(c == 2)
        n->order.status = "OUT FOR DELIVERY";
    else if(c == 3)
        n->order.status = "DELIVERED";
    else
    {
        cout << "Invalid choice.\n";
        return;
    }

    cout << "Status updated.\n";
}

void kitchenLogin()
{
    string id, password;

    cout << "Kitchen ID: ";
    cin >> id;
    cout << "Password: ";
    cin >> password;

    if(id != "K001" || password != "admin")
    {
        cout << "Invalid login.\n";
        return;
    }

    int c;

    do
    {
        cout << "\nKITCHEN DASHBOARD\n";
        cout << "1.Update Menu\n2.View Orders by Priority\n";
        cout << "3.View Customer Distances\n";
        cout << "4.Update Delivery Status\n5.Logout\nChoice: ";
        cin >> c;

        switch(c)
        {
            case 1: updateMenu(); break;
            case 2: viewOrdersByPriority(); break;
            case 3: viewCustomersDistance(); break;
            case 4: manageDeliveryStatus(); break;
        }
    } while(c != 5);
}

// ---------- MAIN ----------

int main()
{
    initializeMenu();

    int c;

    do
    {
        cout << "\nCLOUD KITCHEN ORDER OPTIMIZATION\n";
        cout << "1.Customer Login\n2.Kitchen Login\n3.Exit\nChoice: ";
        cin >> c;

        switch(c)
        {
            case 1: customerLogin(); break;
            case 2: kitchenLogin(); break;
            case 3: cout << "Thank you!\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while(c != 3);

    return 0;
}