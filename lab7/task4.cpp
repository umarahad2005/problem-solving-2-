#include<iostream>
#include<string>
using namespace std;

struct Product {
    int id;
    string name;
    double price;
    int quantity;
    bool savedForLater;
    Product* prev;
    Product* next;
};

class ShoppingCart {
    Product* cartHead;
    Product* cartTail;
    Product* recentHead;
    int cartCount;

public:
    ShoppingCart() {
        cartHead = nullptr;
        cartTail = nullptr;
        recentHead = nullptr;
        cartCount = 0;
    }

    void addToCart(int id, string name, double price, int qty) {
        Product* newProduct = new Product();
        newProduct->id = id;
        newProduct->name = name;
        newProduct->price = price;
        newProduct->quantity = qty;
        newProduct->savedForLater = false;
        newProduct->prev = nullptr;
        newProduct->next = nullptr;

        if(cartHead == nullptr) {
            cartHead = newProduct;
            cartTail = newProduct;
        } else {
            cartTail->next = newProduct;
            newProduct->prev = cartTail;
            cartTail = newProduct;
        }
        cartCount++;
        addToRecentlyViewed(id, name, price);
        cout << name << " added to cart" << endl;
    }

    void addToRecentlyViewed(int id, string name, double price) {
        Product* newProduct = new Product();
        newProduct->id = id;
        newProduct->name = name;
        newProduct->price = price;
        newProduct->quantity = 1;
        newProduct->next = recentHead;
        newProduct->prev = nullptr;
        recentHead = newProduct;
    }

    void removeFromCart(int id) {
        Product* temp = cartHead;
        while(temp != nullptr) {
            if(temp->id == id) {
                if(temp->prev) temp->prev->next = temp->next;
                else cartHead = temp->next;
                
                if(temp->next) temp->next->prev = temp->prev;
                else cartTail = temp->prev;
                
                cout << temp->name << " removed from cart" << endl;
                delete temp;
                cartCount--;
                return;
            }
            temp = temp->next;
        }
    }

    void updateQuantity(int id, int newQty) {
        Product* temp = cartHead;
        while(temp != nullptr) {
            if(temp->id == id) {
                temp->quantity = newQty;
                cout << temp->name << " quantity updated to " << newQty << endl;
                return;
            }
            temp = temp->next;
        }
    }

    void saveForLater(int id) {
        Product* temp = cartHead;
        while(temp != nullptr) {
            if(temp->id == id) {
                temp->savedForLater = true;
                cout << temp->name << " saved for later" << endl;
                return;
            }
            temp = temp->next;
        }
    }

    void moveToCart(int id) {
        Product* temp = cartHead;
        while(temp != nullptr) {
            if(temp->id == id && temp->savedForLater) {
                temp->savedForLater = false;
                cout << temp->name << " moved back to cart" << endl;
                return;
            }
            temp = temp->next;
        }
    }

    void displayCart() {
        cout << "\n--- Shopping Cart ---" << endl;
        Product* temp = cartHead;
        double total = 0;
        while(temp != nullptr) {
            if(!temp->savedForLater) {
                cout << temp->name << " x" << temp->quantity;
                cout << " @ $" << temp->price << " = $" << temp->price * temp->quantity << endl;
                total += temp->price * temp->quantity;
            }
            temp = temp->next;
        }
        cout << "Total: $" << total << endl;
    }

    void displaySavedItems() {
        cout << "\n--- Saved for Later ---" << endl;
        Product* temp = cartHead;
        while(temp != nullptr) {
            if(temp->savedForLater)
                cout << temp->name << " - $" << temp->price << endl;
            temp = temp->next;
        }
    }

    void displayRecentlyViewed() {
        cout << "\n--- Recently Viewed ---" << endl;
        Product* temp = recentHead;
        int count = 0;
        while(temp != nullptr && count < 5) {
            cout << temp->name << " - $" << temp->price << endl;
            temp = temp->next;
            count++;
        }
    }

    void navigateCart() {
        cout << "\n--- Cart Navigation ---" << endl;
        cout << "Forward: ";
        Product* temp = cartHead;
        while(temp != nullptr) {
            cout << temp->name;
            if(temp->next) cout << " -> ";
            temp = temp->next;
        }
        cout << endl << "Backward: ";
        temp = cartTail;
        while(temp != nullptr) {
            cout << temp->name;
            if(temp->prev) cout << " -> ";
            temp = temp->prev;
        }
        cout << endl;
    }

    void getRecommendations() {
        cout << "\n--- Recommendations based on viewing ---" << endl;
        cout << "Based on your history, you might like similar products!" << endl;
    }
};

int main() {
    ShoppingCart cart;
    
    cart.addToCart(1, "Laptop", 999.99, 1);
    cart.addToCart(2, "Mouse", 29.99, 2);
    cart.addToCart(3, "Keyboard", 79.99, 1);
    cart.addToCart(4, "Monitor", 299.99, 1);
    
    cart.displayCart();
    
    cart.updateQuantity(2, 3);
    cart.displayCart();
    
    cart.saveForLater(4);
    cart.displayCart();
    cart.displaySavedItems();
    
    cart.navigateCart();
    
    cart.displayRecentlyViewed();
    cart.getRecommendations();
    
    cart.removeFromCart(2);
    cart.displayCart();
    
    return 0;
}
