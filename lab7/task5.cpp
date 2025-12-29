#include<iostream>
#include<string>
using namespace std;

struct Order {
    int id;
    string customerName;
    string items;
    int deliveryTime;
    double orderValue;
    bool cancelled;
};

class OrderManager {
    Order orders[100];
    int count;

public:
    OrderManager() {
        count = 0;
    }

    void addOrder(int id, string customer, string items, int time, double value) {
        orders[count].id = id;
        orders[count].customerName = customer;
        orders[count].items = items;
        orders[count].deliveryTime = time;
        orders[count].orderValue = value;
        orders[count].cancelled = false;
        count++;
        
        sortByPriority();
        cout << "Order " << id << " added for " << customer << endl;
    }

    void sortByPriority() {
        for(int i = 0; i < count-1; i++) {
            for(int j = 0; j < count-i-1; j++) {
                if(orders[j].deliveryTime > orders[j+1].deliveryTime) {
                    Order temp = orders[j];
                    orders[j] = orders[j+1];
                    orders[j+1] = temp;
                }
            }
        }
    }

    void cancelOrder(int id) {
        for(int i = 0; i < count; i++) {
            if(orders[i].id == id) {
                orders[i].cancelled = true;
                cout << "Order " << id << " cancelled" << endl;
                return;
            }
        }
    }

    void modifyOrder(int id, string newItems) {
        for(int i = 0; i < count; i++) {
            if(orders[i].id == id && !orders[i].cancelled) {
                orders[i].items = newItems;
                cout << "Order " << id << " modified" << endl;
                return;
            }
        }
    }

    void getQueuePosition(int id) {
        int position = 1;
        for(int i = 0; i < count; i++) {
            if(orders[i].cancelled) continue;
            if(orders[i].id == id) {
                cout << "Order " << id << " is at position " << position << " in queue" << endl;
                return;
            }
            position++;
        }
        cout << "Order not found!" << endl;
    }

    void processNextOrder() {
        for(int i = 0; i < count; i++) {
            if(!orders[i].cancelled) {
                cout << "\nProcessing Order " << orders[i].id << endl;
                cout << "Customer: " << orders[i].customerName << endl;
                cout << "Items: " << orders[i].items << endl;
                cout << "Delivery Time: " << orders[i].deliveryTime << " mins" << endl;
                
                for(int j = i; j < count-1; j++)
                    orders[j] = orders[j+1];
                count--;
                return;
            }
        }
        cout << "No orders to process!" << endl;
    }

    void displayQueue() {
        cout << "\n--- Order Queue (Priority: Earliest First) ---" << endl;
        int position = 1;
        for(int i = 0; i < count; i++) {
            if(!orders[i].cancelled) {
                cout << position << ". Order #" << orders[i].id;
                cout << " | " << orders[i].customerName;
                cout << " | " << orders[i].deliveryTime << " mins";
                cout << " | $" << orders[i].orderValue << endl;
                position++;
            }
        }
    }
};

int main() {
    OrderManager manager;
    
    manager.addOrder(101, "Ali", "Pizza, Coke", 30, 25.99);
    manager.addOrder(102, "Sara", "Burger, Fries", 15, 18.50);
    manager.addOrder(103, "Ahmed", "Pasta, Salad", 45, 32.00);
    manager.addOrder(104, "Fatima", "Sandwich", 20, 12.99);
    
    manager.displayQueue();
    
    manager.getQueuePosition(101);
    manager.getQueuePosition(103);
    
    manager.modifyOrder(101, "Pizza, Coke, Wings");
    
    manager.cancelOrder(103);
    manager.displayQueue();
    
    manager.processNextOrder();
    manager.displayQueue();
    
    return 0;
}
