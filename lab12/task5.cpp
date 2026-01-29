#include<iostream>
#include<string>
#include<cmath>
using namespace std;

// Area structure for surge pricing
struct Area {
    string name;
    int availableDrivers;
    int rideRequests;      // Last 5 minutes
    int weatherCondition;  // 0=Clear, 1=Rainy, 2=Stormy
    double surgeMultiplier;
    
    Area() : name(""), availableDrivers(0), rideRequests(0), weatherCondition(0), surgeMultiplier(1.0) {}
    Area(string n, int d, int r, int w) : name(n), availableDrivers(d), rideRequests(r), weatherCondition(w) {
        calculateSurge();
    }
    
    void calculateSurge() {
        // Surge when drivers < requests * 2
        if(availableDrivers >= rideRequests * 2) {
            surgeMultiplier = 1.0;
            return;
        }
        
        // Base surge from demand
        double demandRatio = (double)rideRequests / max(1, availableDrivers);
        surgeMultiplier = 1.0 + (demandRatio - 0.5) * 0.5;
        
        // Weather modifier
        if(weatherCondition == 1) surgeMultiplier += 0.3;      // Rainy
        else if(weatherCondition == 2) surgeMultiplier += 0.8; // Stormy
        
        // Cap between 1.0 and 5.0
        surgeMultiplier = max(1.0, min(5.0, surgeMultiplier));
    }
    
    bool needsSurge() {
        return availableDrivers < rideRequests * 2;
    }
};

class SurgePricingHeap {
    Area heap[1000];
    int size;
    
    void heapifyUp(int index) {
        while(index > 0) {
            int parent = (index - 1) / 2;
            if(heap[index].surgeMultiplier > heap[parent].surgeMultiplier) {
                swap(heap[index], heap[parent]);
                index = parent;
            } else break;
        }
    }
    
    void heapifyDown(int index) {
        while(true) {
            int highest = index;
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            
            if(left < size && heap[left].surgeMultiplier > heap[highest].surgeMultiplier)
                highest = left;
            if(right < size && heap[right].surgeMultiplier > heap[highest].surgeMultiplier)
                highest = right;
            
            if(highest == index) break;
            swap(heap[index], heap[highest]);
            index = highest;
        }
    }
    
    int findArea(string name) {
        for(int i = 0; i < size; i++) {
            if(heap[i].name == name) return i;
        }
        return -1;
    }
    
    void rebuildHeap() {
        for(int i = size / 2 - 1; i >= 0; i--) {
            heapifyDown(i);
        }
    }
    
public:
    SurgePricingHeap() : size(0) {}
    
    string weatherToString(int w) {
        switch(w) {
            case 0: return "Clear";
            case 1: return "Rainy";
            case 2: return "Stormy";
            default: return "Unknown";
        }
    }
    
    void addArea(string name, int drivers, int requests, int weather) {
        int index = findArea(name);
        if(index != -1) {
            // Update existing area
            heap[index] = Area(name, drivers, requests, weather);
            rebuildHeap();
            cout << "Updated area: " << name << endl;
        } else {
            // Add new area
            heap[size] = Area(name, drivers, requests, weather);
            heapifyUp(size);
            size++;
            cout << "Added area: " << name << endl;
        }
    }
    
    void updateDrivers(string name, int change) {
        int index = findArea(name);
        if(index == -1) {
            cout << "Area not found!" << endl;
            return;
        }
        heap[index].availableDrivers += change;
        if(heap[index].availableDrivers < 0) heap[index].availableDrivers = 0;
        heap[index].calculateSurge();
        rebuildHeap();
        cout << name << " drivers: " << heap[index].availableDrivers << endl;
    }
    
    void updateRequests(string name, int change) {
        int index = findArea(name);
        if(index == -1) {
            cout << "Area not found!" << endl;
            return;
        }
        heap[index].rideRequests += change;
        if(heap[index].rideRequests < 0) heap[index].rideRequests = 0;
        heap[index].calculateSurge();
        rebuildHeap();
        cout << name << " requests: " << heap[index].rideRequests << endl;
    }
    
    void updateWeather(string name, int weather) {
        int index = findArea(name);
        if(index == -1) {
            cout << "Area not found!" << endl;
            return;
        }
        heap[index].weatherCondition = weather;
        heap[index].calculateSurge();
        rebuildHeap();
        cout << name << " weather: " << weatherToString(weather) << endl;
    }
    
    void displaySurgeAreas() {
        cout << "\n=== SURGE PRICING STATUS ===" << endl;
        cout << "Areas needing surge pricing:" << endl;
        
        bool anySurge = false;
        for(int i = 0; i < size; i++) {
            if(heap[i].needsSurge()) {
                anySurge = true;
                cout << "- " << heap[i].name 
                     << " | Surge: " << heap[i].surgeMultiplier << "x"
                     << " | Drivers: " << heap[i].availableDrivers
                     << " | Requests: " << heap[i].rideRequests
                     << " | Weather: " << weatherToString(heap[i].weatherCondition) << endl;
            }
        }
        
        if(!anySurge) cout << "No areas currently need surge pricing." << endl;
    }
    
    void displayAllAreas() {
        cout << "\n=== ALL AREAS (Sorted by Surge) ===" << endl;
        
        // Create sorted copy
        Area sorted[1000];
        for(int i = 0; i < size; i++) sorted[i] = heap[i];
        
        // Sort by surge multiplier descending
        for(int i = 0; i < size - 1; i++) {
            for(int j = i + 1; j < size; j++) {
                if(sorted[j].surgeMultiplier > sorted[i].surgeMultiplier) {
                    swap(sorted[i], sorted[j]);
                }
            }
        }
        
        for(int i = 0; i < size; i++) {
            Area& a = sorted[i];
            cout << (i+1) << ". " << a.name 
                 << " | " << a.surgeMultiplier << "x"
                 << " | D:" << a.availableDrivers 
                 << " R:" << a.rideRequests 
                 << " | " << weatherToString(a.weatherCondition) << endl;
        }
    }
    
    void normalizeNearbyPricing() {
        // Ensure nearby areas with similar conditions get similar pricing
        // Simple approach: average surge for areas with same weather
        for(int w = 0; w <= 2; w++) {
            double sum = 0;
            int count = 0;
            for(int i = 0; i < size; i++) {
                if(heap[i].weatherCondition == w) {
                    sum += heap[i].surgeMultiplier;
                    count++;
                }
            }
            if(count > 1) {
                double avg = sum / count;
                for(int i = 0; i < size; i++) {
                    if(heap[i].weatherCondition == w) {
                        // Move toward average (by 20%)
                        heap[i].surgeMultiplier = heap[i].surgeMultiplier * 0.8 + avg * 0.2;
                    }
                }
            }
        }
        rebuildHeap();
        cout << "Pricing normalized across similar areas." << endl;
    }
    
    int getSize() { return size; }
};

int main() {
    cout << "welcome to world of programming with umar usmani sap : 60199" << endl;
    cout << "Lab 12 Task 5: Uber Surge Pricing System" << endl;
    cout << "=========================================" << endl;
    
    SurgePricingHeap pricing;
    int choice;
    
    // Add some sample areas
    pricing.addArea("Downtown", 20, 50, 0);
    pricing.addArea("Airport", 15, 40, 1);
    pricing.addArea("Suburbs", 30, 20, 0);
    pricing.addArea("Mall", 10, 35, 1);
    
    while(true) {
        cout << "\n1. Add/Update Area" << endl;
        cout << "2. Update Drivers (+/-)" << endl;
        cout << "3. Update Requests (+/-)" << endl;
        cout << "4. Update Weather" << endl;
        cout << "5. Display Surge Areas" << endl;
        cout << "6. Display All Areas" << endl;
        cout << "7. Normalize Nearby Pricing" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        
        if(choice == 1) {
            string name;
            int drivers, requests, weather;
            cout << "Area name: ";
            getline(cin, name);
            cout << "Available drivers: ";
            cin >> drivers;
            cout << "Ride requests (last 5 min): ";
            cin >> requests;
            cout << "Weather (0=Clear, 1=Rainy, 2=Stormy): ";
            cin >> weather;
            pricing.addArea(name, drivers, requests, weather);
        }
        else if(choice == 2) {
            string name;
            int change;
            cout << "Area name: ";
            getline(cin, name);
            cout << "Driver change (+/-): ";
            cin >> change;
            pricing.updateDrivers(name, change);
        }
        else if(choice == 3) {
            string name;
            int change;
            cout << "Area name: ";
            getline(cin, name);
            cout << "Request change (+/-): ";
            cin >> change;
            pricing.updateRequests(name, change);
        }
        else if(choice == 4) {
            string name;
            int weather;
            cout << "Area name: ";
            getline(cin, name);
            cout << "Weather (0=Clear, 1=Rainy, 2=Stormy): ";
            cin >> weather;
            pricing.updateWeather(name, weather);
        }
        else if(choice == 5) {
            pricing.displaySurgeAreas();
        }
        else if(choice == 6) {
            pricing.displayAllAreas();
        }
        else if(choice == 7) {
            pricing.normalizeNearbyPricing();
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
