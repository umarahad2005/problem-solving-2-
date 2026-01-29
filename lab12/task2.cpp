#include<iostream>
#include<string>
using namespace std;

// Order structure for trading
struct Order {
    int orderId;
    string type;      // "BUY" or "SELL"
    double price;
    int shares;
    bool isInstitutional; // >10000 shares
    int timestamp;
    
    Order() : orderId(0), type(""), price(0), shares(0), isInstitutional(false), timestamp(0) {}
    Order(int id, string t, double p, int s, int ts) 
        : orderId(id), type(t), price(p), shares(s), timestamp(ts) {
        isInstitutional = (s > 10000);
    }
};

// Max-Heap for Buy Orders (highest bid first)
class BuyOrderHeap {
    Order heap[1000];
    int size;
    
    bool hasPriority(Order& a, Order& b) {
        // Institutional orders get priority
        if(a.isInstitutional != b.isInstitutional)
            return a.isInstitutional;
        // Then by price (higher is better for buy)
        if(a.price != b.price)
            return a.price > b.price;
        // Then by timestamp (earlier first)
        return a.timestamp < b.timestamp;
    }
    
    void heapifyUp(int index) {
        while(index > 0) {
            int parent = (index - 1) / 2;
            if(hasPriority(heap[index], heap[parent])) {
                swap(heap[index], heap[parent]);
                index = parent;
            } else break;
        }
    }
    
    void heapifyDown(int index) {
        while(true) {
            int best = index;
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            
            if(left < size && hasPriority(heap[left], heap[best])) best = left;
            if(right < size && hasPriority(heap[right], heap[best])) best = right;
            
            if(best == index) break;
            swap(heap[index], heap[best]);
            index = best;
        }
    }
    
public:
    BuyOrderHeap() : size(0) {}
    bool isEmpty() { return size == 0; }
    
    void addOrder(Order o) {
        heap[size] = o;
        heapifyUp(size++);
    }
    
    Order getTop() {
        if(isEmpty()) return Order();
        Order top = heap[0];
        heap[0] = heap[--size];
        heapifyDown(0);
        return top;
    }
    
    Order peekTop() { return isEmpty() ? Order() : heap[0]; }
    int getSize() { return size; }
};

// Min-Heap for Sell Orders (lowest ask first)
class SellOrderHeap {
    Order heap[1000];
    int size;
    
    bool hasPriority(Order& a, Order& b) {
        if(a.isInstitutional != b.isInstitutional)
            return a.isInstitutional;
        if(a.price != b.price)
            return a.price < b.price; // Lower is better for sell
        return a.timestamp < b.timestamp;
    }
    
    void heapifyUp(int index) {
        while(index > 0) {
            int parent = (index - 1) / 2;
            if(hasPriority(heap[index], heap[parent])) {
                swap(heap[index], heap[parent]);
                index = parent;
            } else break;
        }
    }
    
    void heapifyDown(int index) {
        while(true) {
            int best = index;
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            
            if(left < size && hasPriority(heap[left], heap[best])) best = left;
            if(right < size && hasPriority(heap[right], heap[best])) best = right;
            
            if(best == index) break;
            swap(heap[index], heap[best]);
            index = best;
        }
    }
    
public:
    SellOrderHeap() : size(0) {}
    bool isEmpty() { return size == 0; }
    
    void addOrder(Order o) {
        heap[size] = o;
        heapifyUp(size++);
    }
    
    Order getTop() {
        if(isEmpty()) return Order();
        Order top = heap[0];
        heap[0] = heap[--size];
        heapifyDown(0);
        return top;
    }
    
    Order peekTop() { return isEmpty() ? Order() : heap[0]; }
    int getSize() { return size; }
};

class TradingPlatform {
    BuyOrderHeap buyOrders;
    SellOrderHeap sellOrders;
    int orderCounter;
    int timeCounter;
    
public:
    TradingPlatform() : orderCounter(0), timeCounter(0) {}
    
    void placeBuyOrder(double price, int shares) {
        Order o(++orderCounter, "BUY", price, shares, ++timeCounter);
        buyOrders.addOrder(o);
        cout << "Buy Order #" << o.orderId << " placed: " << shares << " shares @ $" << price;
        if(o.isInstitutional) cout << " [INSTITUTIONAL]";
        cout << endl;
        matchOrders();
    }
    
    void placeSellOrder(double price, int shares) {
        Order o(++orderCounter, "SELL", price, shares, ++timeCounter);
        sellOrders.addOrder(o);
        cout << "Sell Order #" << o.orderId << " placed: " << shares << " shares @ $" << price;
        if(o.isInstitutional) cout << " [INSTITUTIONAL]";
        cout << endl;
        matchOrders();
    }
    
    void matchOrders() {
        while(!buyOrders.isEmpty() && !sellOrders.isEmpty()) {
            Order buy = buyOrders.peekTop();
            Order sell = sellOrders.peekTop();
            
            if(buy.price >= sell.price) {
                buyOrders.getTop();
                sellOrders.getTop();
                int traded = min(buy.shares, sell.shares);
                cout << "MATCHED: " << traded << " shares @ $" << sell.price << endl;
            } else break;
        }
    }
    
    void displayOrderBook() {
        cout << "\n=== ORDER BOOK ===" << endl;
        cout << "Buy Orders: " << buyOrders.getSize() << " pending" << endl;
        cout << "Sell Orders: " << sellOrders.getSize() << " pending" << endl;
        if(!buyOrders.isEmpty()) {
            Order top = buyOrders.peekTop();
            cout << "Best Bid: $" << top.price << (top.isInstitutional ? " [INST]" : "") << endl;
        }
        if(!sellOrders.isEmpty()) {
            Order top = sellOrders.peekTop();
            cout << "Best Ask: $" << top.price << (top.isInstitutional ? " [INST]" : "") << endl;
        }
    }
};

int main() {
    cout << "welcome to world of programming with umar usmani sap : 60199" << endl;
    cout << "Lab 12 Task 2: Trading Platform with Dual-Heap Order Matching" << endl;
    cout << "==============================================================" << endl;
    
    TradingPlatform platform;
    int choice;
    
    while(true) {
        cout << "\n1. Place Buy Order" << endl;
        cout << "2. Place Sell Order" << endl;
        cout << "3. Display Order Book" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        
        if(choice == 1) {
            double price;
            int shares;
            cout << "Enter price: $";
            cin >> price;
            cout << "Enter shares (>10000 for institutional): ";
            cin >> shares;
            platform.placeBuyOrder(price, shares);
        }
        else if(choice == 2) {
            double price;
            int shares;
            cout << "Enter price: $";
            cin >> price;
            cout << "Enter shares: ";
            cin >> shares;
            platform.placeSellOrder(price, shares);
        }
        else if(choice == 3) {
            platform.displayOrderBook();
        }
        else if(choice == 4) {
            cout << "Exiting..." << endl;
            break;
        }
        else {
            cout << "Invalid choice!" << endl;
        }
    }
    
    return 0;
}
