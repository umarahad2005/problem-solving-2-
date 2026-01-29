#include<iostream>
#include<string>
#include<ctime>
using namespace std;

// Emergency call structure
struct EmergencyCall {
    int callId;
    string callerName;
    string description;
    int priority;        // 1=Life-threatening, 2=Serious, 3=Minor
    int arrivalTime;     // Minutes from start
    bool isOverride;     // Critical override call
    
    EmergencyCall() : callId(0), callerName(""), description(""), priority(3), arrivalTime(0), isOverride(false) {}
    EmergencyCall(int id, string name, string desc, int p, int time, bool over = false) 
        : callId(id), callerName(name), description(desc), priority(p), arrivalTime(time), isOverride(over) {}
};

// Priority Queue using array-based heap
class EmergencyCallQueue {
    EmergencyCall queue[1000];
    int size;
    int currentTime;
    int callCounter;
    
    // Compare priority: Override > Priority level > Arrival time
    bool hasPriority(EmergencyCall& a, EmergencyCall& b) {
        if(a.isOverride != b.isOverride) return a.isOverride;
        if(a.priority != b.priority) return a.priority < b.priority; // Lower number = higher priority
        return a.arrivalTime < b.arrivalTime;
    }
    
    void heapifyUp(int index) {
        while(index > 0) {
            int parent = (index - 1) / 2;
            if(hasPriority(queue[index], queue[parent])) {
                swap(queue[index], queue[parent]);
                index = parent;
            } else break;
        }
    }
    
    void heapifyDown(int index) {
        while(true) {
            int highest = index;
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            
            if(left < size && hasPriority(queue[left], queue[highest])) highest = left;
            if(right < size && hasPriority(queue[right], queue[highest])) highest = right;
            
            if(highest == index) break;
            swap(queue[index], queue[highest]);
            index = highest;
        }
    }
    
public:
    EmergencyCallQueue() : size(0), currentTime(0), callCounter(0) {}
    
    string priorityToString(int p) {
        switch(p) {
            case 1: return "PRIORITY 1 - Life-threatening";
            case 2: return "PRIORITY 2 - Serious";
            case 3: return "PRIORITY 3 - Minor";
            default: return "Unknown";
        }
    }
    
    void advanceTime(int minutes) {
        currentTime += minutes;
        cout << "Time advanced to minute " << currentTime << endl;
    }
    
    // Regular call intake
    void receiveCall(string name, string desc, int priority) {
        EmergencyCall call(++callCounter, name, desc, priority, currentTime);
        queue[size] = call;
        heapifyUp(size++);
        cout << "Call #" << call.callId << " received from " << name << endl;
        cout << "  " << priorityToString(priority) << endl;
        cout << "  Description: " << desc << endl;
    }
    
    // Override: Insert critical call at front
    void overrideCall(string name, string desc) {
        EmergencyCall call(++callCounter, name, desc, 1, currentTime, true);
        queue[size] = call;
        heapifyUp(size++);
        cout << "*** OVERRIDE CALL #" << call.callId << " from " << name << " ***" << endl;
        cout << "  Critical emergency inserted at front!" << endl;
    }
    
    // Dispatcher gets next call
    EmergencyCall dispatchCall() {
        if(size == 0) {
            cout << "No calls in queue!" << endl;
            return EmergencyCall();
        }
        
        EmergencyCall next = queue[0];
        queue[0] = queue[--size];
        heapifyDown(0);
        
        int waitTime = currentTime - next.arrivalTime;
        
        cout << "\n=== DISPATCHING CALL #" << next.callId << " ===" << endl;
        cout << "Caller: " << next.callerName << endl;
        cout << "Priority: " << priorityToString(next.priority);
        if(next.isOverride) cout << " [OVERRIDE]";
        cout << endl;
        cout << "Description: " << next.description << endl;
        cout << "Wait Time: " << waitTime << " minutes" << endl;
        
        return next;
    }
    
    // Display queue with wait times
    void displayQueue() {
        cout << "\n=== 911 CALL QUEUE (" << size << " calls) ===" << endl;
        cout << "Current Time: " << currentTime << " min" << endl;
        
        if(size == 0) {
            cout << "Queue is empty." << endl;
            return;
        }
        
        // Create sorted copy for display
        EmergencyCall sorted[1000];
        for(int i = 0; i < size; i++) sorted[i] = queue[i];
        
        // Sort by priority
        for(int i = 0; i < size - 1; i++) {
            for(int j = i + 1; j < size; j++) {
                if(hasPriority(sorted[j], sorted[i])) {
                    swap(sorted[i], sorted[j]);
                }
            }
        }
        
        for(int i = 0; i < size; i++) {
            EmergencyCall& c = sorted[i];
            int wait = currentTime - c.arrivalTime;
            cout << (i+1) << ". Call #" << c.callId << " | P" << c.priority 
                 << " | " << c.callerName << " | Wait: " << wait << " min";
            if(c.isOverride) cout << " [OVERRIDE]";
            cout << endl;
        }
    }
    
    // Statistics
    void showStats() {
        cout << "\n=== QUEUE STATISTICS ===" << endl;
        cout << "Total calls in queue: " << size << endl;
        
        int p1 = 0, p2 = 0, p3 = 0;
        int totalWait = 0;
        
        for(int i = 0; i < size; i++) {
            if(queue[i].priority == 1) p1++;
            else if(queue[i].priority == 2) p2++;
            else p3++;
            totalWait += (currentTime - queue[i].arrivalTime);
        }
        
        cout << "Priority 1 calls: " << p1 << endl;
        cout << "Priority 2 calls: " << p2 << endl;
        cout << "Priority 3 calls: " << p3 << endl;
        if(size > 0) cout << "Average wait time: " << (totalWait / size) << " min" << endl;
    }
    
    bool isEmpty() { return size == 0; }
};

int main() {
    cout << "welcome to world of programming with umar usmani sap : 60199" << endl;
    cout << "Assignment 2 Task 1: 911 Emergency Call Center System" << endl;
    cout << "======================================================" << endl;
    
    EmergencyCallQueue center;
    int choice;
    
    while(true) {
        cout << "\n1. Receive Emergency Call" << endl;
        cout << "2. Override (Critical Call)" << endl;
        cout << "3. Dispatch Next Call" << endl;
        cout << "4. Display Queue" << endl;
        cout << "5. Show Statistics" << endl;
        cout << "6. Advance Time" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        
        if(choice == 1) {
            string name, desc;
            int priority;
            cout << "Caller name: ";
            getline(cin, name);
            cout << "Emergency description: ";
            getline(cin, desc);
            cout << "Priority (1=Life-threatening, 2=Serious, 3=Minor): ";
            cin >> priority;
            center.receiveCall(name, desc, priority);
        }
        else if(choice == 2) {
            string name, desc;
            cout << "Caller name: ";
            getline(cin, name);
            cout << "Critical emergency description: ";
            getline(cin, desc);
            center.overrideCall(name, desc);
        }
        else if(choice == 3) {
            center.dispatchCall();
        }
        else if(choice == 4) {
            center.displayQueue();
        }
        else if(choice == 5) {
            center.showStats();
        }
        else if(choice == 6) {
            int mins;
            cout << "Advance time by (minutes): ";
            cin >> mins;
            center.advanceTime(mins);
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
