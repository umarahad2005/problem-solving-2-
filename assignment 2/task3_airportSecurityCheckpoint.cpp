#include<iostream>
#include<string>
using namespace std;

// Passenger types
enum PassengerType { REGULAR = 0, FASTTRACK = 1, EMERGENCY = 2 };

struct Passenger {
    int passengerId;
    string name;
    PassengerType type;
    int arrivalTime;     // In minutes
    int processingTime;  // When processed
    
    Passenger() : passengerId(0), name(""), type(REGULAR), arrivalTime(0), processingTime(0) {}
    Passenger(int id, string n, PassengerType t, int arr) 
        : passengerId(id), name(n), type(t), arrivalTime(arr), processingTime(0) {}
};

// Queue for regular passengers
class RegularQueue {
    Passenger queue[500];
    int front, rear, count;
    
public:
    RegularQueue() : front(0), rear(-1), count(0) {}
    
    bool isEmpty() { return count == 0; }
    int size() { return count; }
    
    void enqueue(Passenger p) {
        rear = (rear + 1) % 500;
        queue[rear] = p;
        count++;
    }
    
    Passenger dequeue() {
        if(isEmpty()) return Passenger();
        Passenger p = queue[front];
        front = (front + 1) % 500;
        count--;
        return p;
    }
    
    Passenger peek() {
        if(isEmpty()) return Passenger();
        return queue[front];
    }
    
    int getTotalWaitTime(int currentTime) {
        int total = 0;
        int idx = front;
        for(int i = 0; i < count; i++) {
            total += (currentTime - queue[idx].arrivalTime);
            idx = (idx + 1) % 500;
        }
        return total;
    }
};

// Priority queue for fast-track (sorted by arrival time) 
class FastTrackQueue {
    Passenger queue[200];
    int count;
    
public:
    FastTrackQueue() : count(0) {}
    
    bool isEmpty() { return count == 0; }
    int size() { return count; }
    
    void enqueue(Passenger p) {
        queue[count++] = p;
    }
    
    Passenger dequeue() {
        if(isEmpty()) return Passenger();
        
        // Find earliest arrival
        int minIdx = 0;
        for(int i = 1; i < count; i++) {
            if(queue[i].arrivalTime < queue[minIdx].arrivalTime)
                minIdx = i;
        }
        
        Passenger p = queue[minIdx];
        for(int i = minIdx; i < count - 1; i++)
            queue[i] = queue[i + 1];
        count--;
        return p;
    }
    
    Passenger peek() {
        if(isEmpty()) return Passenger();
        int minIdx = 0;
        for(int i = 1; i < count; i++) {
            if(queue[i].arrivalTime < queue[minIdx].arrivalTime)
                minIdx = i;
        }
        return queue[minIdx];
    }
    
    // Check if any passenger has waited > 5 minutes
    bool hasUrgent(int currentTime) {
        for(int i = 0; i < count; i++) {
            if(currentTime - queue[i].arrivalTime >= 5) return true;
        }
        return false;
    }
};

// Stack for emergency (LIFO - most recent emergency first)
class EmergencyStack {
    Passenger stack[50];
    int top;
    
public:
    EmergencyStack() : top(-1) {}
    
    bool isEmpty() { return top == -1; }
    int size() { return top + 1; }
    
    void push(Passenger p) {
        if(top < 49) stack[++top] = p;
    }
    
    Passenger pop() {
        if(isEmpty()) return Passenger();
        return stack[top--];
    }
};

// Airport Security Checkpoint
class SecurityCheckpoint {
    RegularQueue regularQueue;
    FastTrackQueue fastTrackQueue;
    EmergencyStack emergencyStack;
    
    int currentTime;
    int passengerCounter;
    int regularProcessed;  // Count regular passengers since last fast-track
    int totalProcessed;
    int totalWaitTime;
    
public:
    SecurityCheckpoint() : currentTime(0), passengerCounter(0), regularProcessed(0), 
                           totalProcessed(0), totalWaitTime(0) {}
    
    string typeToString(PassengerType t) {
        switch(t) {
            case EMERGENCY: return "Emergency";
            case FASTTRACK: return "Fast-Track";
            default: return "Regular";
        }
    }
    
    void passengerArrives(string name, int type) {
        PassengerType t = (PassengerType)(type > 2 ? 0 : type);
        Passenger p(++passengerCounter, name, t, currentTime);
        
        switch(t) {
            case EMERGENCY:
                emergencyStack.push(p);
                cout << "[EMERGENCY] " << name << " sent to front!" << endl;
                break;
            case FASTTRACK:
                fastTrackQueue.enqueue(p);
                cout << "[FAST-TRACK] " << name << " joined priority queue." << endl;
                break;
            default:
                regularQueue.enqueue(p);
                cout << "[REGULAR] " << name << " joined regular queue." << endl;
        }
    }
    
    void processNextPassenger() {
        Passenger p;
        string source;
        
        // Priority 1: Emergency (always first)
        if(!emergencyStack.isEmpty()) {
            p = emergencyStack.pop();
            source = "EMERGENCY";
        }
        // Priority 2: Check if fast-track waited > 5 min
        else if(fastTrackQueue.hasUrgent(currentTime) && !fastTrackQueue.isEmpty()) {
            p = fastTrackQueue.dequeue();
            source = "FAST-TRACK (URGENT)";
            regularProcessed = 0;
        }
        // Priority 3: After 3 regular, process 1 fast-track
        else if(regularProcessed >= 3 && !fastTrackQueue.isEmpty()) {
            p = fastTrackQueue.dequeue();
            source = "FAST-TRACK";
            regularProcessed = 0;
        }
        // Priority 4: Process regular if no fast-track or need to process more regular
        else if(!regularQueue.isEmpty()) {
            p = regularQueue.dequeue();
            source = "REGULAR";
            regularProcessed++;
        }
        // Priority 5: Process fast-track if no regular
        else if(!fastTrackQueue.isEmpty()) {
            p = fastTrackQueue.dequeue();
            source = "FAST-TRACK";
            regularProcessed = 0;
        }
        else {
            cout << "No passengers to process!" << endl;
            return;
        }
        
        p.processingTime = currentTime;
        int waitTime = currentTime - p.arrivalTime;
        totalWaitTime += waitTime;
        totalProcessed++;
        
        cout << "\n=== PROCESSING PASSENGER ===" << endl;
        cout << "ID: " << p.passengerId << " | Name: " << p.name << endl;
        cout << "Type: " << source << endl;
        cout << "Wait Time: " << waitTime << " minutes" << endl;
        
        // Check constraints
        if(p.type == FASTTRACK && waitTime > 5) {
            cout << "[WARNING] Fast-track waited > 5 min!" << endl;
        }
        if(p.type == REGULAR && waitTime > 15) {
            cout << "[WARNING] Regular waited > 15 min!" << endl;
        }
        
        // Each processing takes 2 minutes
        currentTime += 2;
        cout << "Time now: " << currentTime << " min" << endl;
    }
    
    void advanceTime(int minutes) {
        currentTime += minutes;
        cout << "Time advanced to " << currentTime << " min" << endl;
    }
    
    void displayQueues() {
        cout << "\n=== QUEUE STATUS (Time: " << currentTime << " min) ===" << endl;
        cout << "Emergency: " << emergencyStack.size() << " passengers" << endl;
        cout << "Fast-Track: " << fastTrackQueue.size() << " passengers" << endl;
        cout << "Regular: " << regularQueue.size() << " passengers" << endl;
        cout << "Regular processed since last fast-track: " << regularProcessed << "/3" << endl;
        
        if(fastTrackQueue.hasUrgent(currentTime)) {
            cout << "[ALERT] Fast-track passengers waiting > 5 min!" << endl;
        }
    }
    
    void showStatistics() {
        cout << "\n=== STATISTICS ===" << endl;
        cout << "Total processed: " << totalProcessed << endl;
        cout << "Current time: " << currentTime << " min" << endl;
        
        if(totalProcessed > 0) {
            cout << "Average wait time: " << (totalWaitTime / totalProcessed) << " min" << endl;
        }
        
        cout << "Still waiting: " << (emergencyStack.size() + fastTrackQueue.size() + regularQueue.size()) << endl;
    }
};

int main() {
    cout << "welcome to world of programming with umar usmani sap : 60199" << endl;
    cout << "Assignment 2 Task 3: Airport Security Checkpoint" << endl;
    cout << "=================================================" << endl;
    
    SecurityCheckpoint checkpoint;
    int choice;
    
    while(true) {
        cout << "\n1. Passenger Arrives" << endl;
        cout << "2. Process Next Passenger" << endl;
        cout << "3. Process Multiple (auto)" << endl;
        cout << "4. Display Queues" << endl;
        cout << "5. Show Statistics" << endl;
        cout << "6. Advance Time" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        
        if(choice == 1) {
            string name;
            int type;
            cout << "Passenger name: ";
            getline(cin, name);
            cout << "Type (0=Regular, 1=Fast-Track, 2=Emergency): ";
            cin >> type;
            checkpoint.passengerArrives(name, type);
        }
        else if(choice == 2) {
            checkpoint.processNextPassenger();
        }
        else if(choice == 3) {
            int count;
            cout << "How many to process: ";
            cin >> count;
            for(int i = 0; i < count; i++) {
                checkpoint.processNextPassenger();
            }
        }
        else if(choice == 4) {
            checkpoint.displayQueues();
        }
        else if(choice == 5) {
            checkpoint.showStatistics();
        }
        else if(choice == 6) {
            int mins;
            cout << "Advance by (minutes): ";
            cin >> mins;
            checkpoint.advanceTime(mins);
        }
        else if(choice == 7) {
            cout << "Exiting..." << endl;
            break;
        }
        else {
            cout << "Invalid choice!" << endl;
        }
    }
    
    return 0;
}
