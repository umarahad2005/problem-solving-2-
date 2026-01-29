#include<iostream>
#include<string>
using namespace std;

// Ticket tiers with priority levels
enum Tier { FREE = 0, PRO = 1, ENTERPRISE = 2 };

struct SupportTicket {
    int ticketId;
    string customerName;
    string issue;
    Tier tier;
    int creationTime;    // In minutes from start
    int maxWaitTime;     // Free=30, Pro=15, Enterprise=5
    bool escalated;
    
    SupportTicket() : ticketId(0), customerName(""), issue(""), tier(FREE), 
                      creationTime(0), maxWaitTime(30), escalated(false) {}
    
    SupportTicket(int id, string name, string iss, Tier t, int time) 
        : ticketId(id), customerName(name), issue(iss), tier(t), creationTime(time), escalated(false) {
        switch(t) {
            case ENTERPRISE: maxWaitTime = 5; break;
            case PRO: maxWaitTime = 15; break;
            default: maxWaitTime = 30; break;
        }
    }
    
    int getRemainingTime(int currentTime) {
        return maxWaitTime - (currentTime - creationTime);
    }
    
    // Priority: Escalated first, then by tier, then by remaining time
    int getPriority(int currentTime) {
        if(escalated) return 1000;
        int remaining = getRemainingTime(currentTime);
        if(remaining <= 2) return 999; // Near deadline
        return (int)tier * 100 - remaining;
    }
};

class SupportQueueHeap {
    SupportTicket heap[10001];
    int size;
    int currentTime;
    int ticketCounter;
    
    void heapifyUp(int index) {
        while(index > 0) {
            int parent = (index - 1) / 2;
            if(heap[index].getPriority(currentTime) > heap[parent].getPriority(currentTime)) {
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
            
            if(left < size && heap[left].getPriority(currentTime) > heap[highest].getPriority(currentTime))
                highest = left;
            if(right < size && heap[right].getPriority(currentTime) > heap[highest].getPriority(currentTime))
                highest = right;
            
            if(highest == index) break;
            swap(heap[index], heap[highest]);
            index = highest;
        }
    }
    
    void rebuildHeap() {
        for(int i = size / 2 - 1; i >= 0; i--) {
            heapifyDown(i);
        }
    }
    
public:
    SupportQueueHeap() : size(0), currentTime(0), ticketCounter(0) {}
    
    string tierToString(Tier t) {
        switch(t) {
            case ENTERPRISE: return "Enterprise";
            case PRO: return "Pro";
            default: return "Free";
        }
    }
    
    void advanceTime(int minutes) {
        currentTime += minutes;
        cout << "Time advanced to minute " << currentTime << endl;
        
        // Check for escalations
        for(int i = 0; i < size; i++) {
            int remaining = heap[i].getRemainingTime(currentTime);
            if(remaining <= 2 && !heap[i].escalated) {
                heap[i].escalated = true;
                cout << "[ESCALATED] Ticket #" << heap[i].ticketId 
                     << " (" << tierToString(heap[i].tier) << ") - " 
                     << remaining << " min remaining!" << endl;
            }
        }
        rebuildHeap();
    }
    
    void createTicket(string name, string issue, int tierNum) {
        Tier t = (Tier)(tierNum > 2 ? 2 : (tierNum < 0 ? 0 : tierNum));
        heap[size] = SupportTicket(++ticketCounter, name, issue, t, currentTime);
        cout << "Ticket #" << ticketCounter << " created for " << name 
             << " (" << tierToString(t) << ") - Max wait: " 
             << heap[size].maxWaitTime << " min" << endl;
        heapifyUp(size);
        size++;
    }
    
    void processNextTicket() {
        if(size == 0) {
            cout << "No tickets in queue!" << endl;
            return;
        }
        
        SupportTicket next = heap[0];
        heap[0] = heap[--size];
        heapifyDown(0);
        
        cout << "\n=== PROCESSING TICKET #" << next.ticketId << " ===" << endl;
        cout << "Customer: " << next.customerName << endl;
        cout << "Tier: " << tierToString(next.tier) << endl;
        cout << "Issue: " << next.issue << endl;
        cout << "Wait Time: " << (currentTime - next.creationTime) << " min" << endl;
        cout << "Escalated: " << (next.escalated ? "Yes" : "No") << endl;
    }
    
    void displayQueue() {
        cout << "\n=== SUPPORT QUEUE (" << size << " tickets) ===" << endl;
        cout << "Current Time: " << currentTime << " min" << endl;
        
        for(int i = 0; i < min(10, size); i++) {
            SupportTicket& t = heap[i];
            int remaining = t.getRemainingTime(currentTime);
            cout << "Ticket #" << t.ticketId << " | " << tierToString(t.tier) 
                 << " | " << t.customerName << " | Remaining: " << remaining 
                 << " min" << (t.escalated ? " [ESCALATED]" : "") << endl;
        }
        if(size > 10) cout << "... and " << (size - 10) << " more" << endl;
    }
    
    int getSize() { return size; }
};

int main() {
    cout << "welcome to world of programming with umar usmani sap : 60199" << endl;
    cout << "Lab 12 Task 4: Tiered Support Queue with Auto-Escalation" << endl;
    cout << "==========================================================" << endl;
    
    SupportQueueHeap queue;
    int choice;
    
    while(true) {
        cout << "\n1. Create Ticket" << endl;
        cout << "2. Process Next Ticket" << endl;
        cout << "3. Display Queue" << endl;
        cout << "4. Advance Time (minutes)" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        
        if(choice == 1) {
            string name, issue;
            int tier;
            cout << "Customer name: ";
            getline(cin, name);
            cout << "Issue description: ";
            getline(cin, issue);
            cout << "Tier (0=Free, 1=Pro, 2=Enterprise): ";
            cin >> tier;
            queue.createTicket(name, issue, tier);
        }
        else if(choice == 2) {
            queue.processNextTicket();
        }
        else if(choice == 3) {
            queue.displayQueue();
        }
        else if(choice == 4) {
            int minutes;
            cout << "Advance by (minutes): ";
            cin >> minutes;
            queue.advanceTime(minutes);
        }
        else if(choice == 5) {
            cout << "Exiting..." << endl;
            break;
        }
        else {
            cout << "Invalid choice!" << endl;
        }
    }
    
    return 0;
}
