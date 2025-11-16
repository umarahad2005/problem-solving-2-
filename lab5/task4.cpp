#include<iostream>
#include<string>
using namespace std;

class DeliveryLocation {
public:
    string address;
    int distance; // in km from previous location
    DeliveryLocation* prev;
    DeliveryLocation* next;
    
    DeliveryLocation(string addr, int dist) {
        address = addr;
        distance = dist;
        prev = NULL;
        next = NULL;
    }
};

class DeliveryRoute {
    DeliveryLocation* head;
    DeliveryLocation* current;
    
public:
    DeliveryRoute() {
        head = NULL;
        current = NULL;
    }
    
    // Add delivery location
    void addLocation(string address, int distance) {
        DeliveryLocation* newLoc = new DeliveryLocation(address, distance);
        
        if(head == NULL) {
            head = newLoc;
            current = newLoc;
            cout << "Added first location: " << address << endl;
            return;
        }
        
        DeliveryLocation* temp = head;
        while(temp->next != NULL) {
            temp = temp->next;
        }
        
        temp->next = newLoc;
        newLoc->prev = temp;
        cout << "Added location: " << address << " (" << distance << "km from previous)" << endl;
    }
    
    // Remove completed delivery
    void removeCompleted(string address) {
        if(head == NULL) {
            cout << "No deliveries in route" << endl;
            return;
        }
        
        DeliveryLocation* temp = head;
        
        while(temp != NULL && temp->address != address) {
            temp = temp->next;
        }
        
        if(temp == NULL) {
            cout << "Location not found" << endl;
            return;
        }
        
        // Update current if it's being deleted
        if(current == temp) {
            if(temp->next != NULL) {
                current = temp->next;
            } else {
                current = temp->prev;
            }
        }
        
        // Remove node
        if(temp->prev != NULL) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next;
        }
        
        if(temp->next != NULL) {
            temp->next->prev = temp->prev;
        }
        
        cout << "Removed delivery: " << address << endl;
        delete temp;
    }
    
    // Move forward in route
    void moveForward() {
        if(current == NULL) {
            cout << "No current location" << endl;
            return;
        }
        
        if(current->next == NULL) {
            cout << "Already at last location" << endl;
            return;
        }
        
        current = current->next;
        cout << "Moved to: " << current->address << endl;
    }
    
    // Move backward in route
    void moveBackward() {
        if(current == NULL) {
            cout << "No current location" << endl;
            return;
        }
        
        if(current->prev == NULL) {
            cout << "Already at first location" << endl;
            return;
        }
        
        current = current->prev;
        cout << "Moved back to: " << current->address << endl;
    }
    
    // Swap two consecutive deliveries
    void swapConsecutive(string address1) {
        if(head == NULL) {
            cout << "Route is empty" << endl;
            return;
        }
        
        DeliveryLocation* loc1 = head;
        while(loc1 != NULL && loc1->address != address1) {
            loc1 = loc1->next;
        }
        
        if(loc1 == NULL || loc1->next == NULL) {
            cout << "Cannot swap - location not found or is last" << endl;
            return;
        }
        
        DeliveryLocation* loc2 = loc1->next;
        
        // Swap data instead of pointers (simpler)
        string tempAddr = loc1->address;
        int tempDist = loc1->distance;
        
        loc1->address = loc2->address;
        loc1->distance = loc2->distance;
        
        loc2->address = tempAddr;
        loc2->distance = tempDist;
        
        cout << "Swapped " << loc2->address << " and " << loc1->address << endl;
    }
    
    // Calculate total route distance
    int calculateTotalDistance() {
        int total = 0;
        DeliveryLocation* temp = head;
        
        while(temp != NULL) {
            total += temp->distance;
            temp = temp->next;
        }
        
        return total;
    }
    
    // Display route
    void displayRoute() {
        if(head == NULL) {
            cout << "No deliveries in route" << endl;
            return;
        }
        
        cout << "\n=== Delivery Route ===" << endl;
        DeliveryLocation* temp = head;
        int count = 1;
        
        while(temp != NULL) {
            if(temp == current) {
                cout << count++ << ". " << temp->address << " (" << temp->distance 
                     << "km) <- CURRENT" << endl;
            } else {
                cout << count++ << ". " << temp->address << " (" << temp->distance 
                     << "km)" << endl;
            }
            temp = temp->next;
        }
        
        cout << "Total Distance: " << calculateTotalDistance() << "km" << endl;
    }
};

int main() {
    cout << "welcome to the world of problem solving 2 with umar usmani sap: 60199\n" << endl;
    
    DeliveryRoute route;
    int choice;
    
    while(true) {
        cout << "\n=== Delivery Route Manager ===" << endl;
        cout << "1. Add Delivery Location" << endl;
        cout << "2. Remove Completed Delivery" << endl;
        cout << "3. Move Forward" << endl;
        cout << "4. Move Backward" << endl;
        cout << "5. Swap Consecutive Deliveries" << endl;
        cout << "6. Show Total Distance" << endl;
        cout << "7. Display Route" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        
        if(choice == 1) {
            string address;
            int distance;
            cout << "Enter address: ";
            getline(cin, address);
            cout << "Enter distance from previous (km): ";
            cin >> distance;
            route.addLocation(address, distance);
        }
        else if(choice == 2) {
            string address;
            cout << "Enter address to remove: ";
            getline(cin, address);
            route.removeCompleted(address);
        }
        else if(choice == 3) {
            route.moveForward();
        }
        else if(choice == 4) {
            route.moveBackward();
        }
        else if(choice == 5) {
            string address;
            cout << "Enter first address to swap: ";
            getline(cin, address);
            route.swapConsecutive(address);
        }
        else if(choice == 6) {
            cout << "Total Route Distance: " << route.calculateTotalDistance() << "km" << endl;
        }
        else if(choice == 7) {
            route.displayRoute();
        }
        else if(choice == 8) {
            cout << "Exiting..." << endl;
            break;
        }
        else {
            cout << "Invalid choice!" << endl;
        }
    }
    
    return 0;
}
