#include<iostream>
#include<string>
using namespace std;

// Patient structure with severity and VIP status
struct Patient {
    string name;
    int severity;    // 1-10 (10 is most critical)
    bool isVIP;
    int arrivalTime; // For tiebreaking
    
    Patient() : name(""), severity(0), isVIP(false), arrivalTime(0) {}
    Patient(string n, int s, bool v, int t) : name(n), severity(s), isVIP(v), arrivalTime(t) {}
    
    // Compare priority: Higher severity first, then VIP status, then earlier arrival
    bool hasPriorityOver(Patient& other) {
        if(severity != other.severity) 
            return severity > other.severity;
        if(isVIP != other.isVIP) 
            return isVIP;
        return arrivalTime < other.arrivalTime;
    }
};

class PatientTriageHeap {
    Patient heap[1000];
    int size;
    
    void heapifyUp(int index) {
        while(index > 0) {
            int parent = (index - 1) / 2;
            if(heap[index].hasPriorityOver(heap[parent])) {
                swap(heap[index], heap[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }
    
    void heapifyDown(int index) {
        while(true) {
            int highest = index;
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            
            if(left < size && heap[left].hasPriorityOver(heap[highest]))
                highest = left;
            if(right < size && heap[right].hasPriorityOver(heap[highest]))
                highest = right;
            
            if(highest == index) break;
            
            swap(heap[index], heap[highest]);
            index = highest;
        }
    }
    
public:
    PatientTriageHeap() : size(0) {}
    
    bool isEmpty() { return size == 0; }
    int getSize() { return size; }
    
    // Admit a new patient
    void admitPatient(string name, int severity, bool isVIP, int arrivalTime) {
        heap[size] = Patient(name, severity, isVIP, arrivalTime);
        heapifyUp(size);
        size++;
        cout << "Admitted: " << name << " (Severity: " << severity 
             << ", VIP: " << (isVIP ? "Yes" : "No") << ")" << endl;
    }
    
    // Dispatch next patient for treatment
    Patient dispatchPatient() {
        if(isEmpty()) {
            cout << "No patients in queue!" << endl;
            return Patient();
        }
        
        Patient next = heap[0];
        heap[0] = heap[--size];
        heapifyDown(0);
        
        cout << "Dispatching: " << next.name << " (Severity: " << next.severity 
             << ", VIP: " << (next.isVIP ? "Yes" : "No") << ")" << endl;
        return next;
    }
    
    // View next patient without removing
    void peekNext() {
        if(isEmpty()) {
            cout << "No patients in queue!" << endl;
            return;
        }
        cout << "Next patient: " << heap[0].name << " (Severity: " << heap[0].severity 
             << ", VIP: " << (heap[0].isVIP ? "Yes" : "No") << ")" << endl;
    }
    
    // Display all patients in queue
    void displayQueue() {
        if(isEmpty()) {
            cout << "Queue is empty!" << endl;
            return;
        }
        cout << "\n=== Current Patient Queue ===" << endl;
        for(int i = 0; i < size; i++) {
            cout << (i+1) << ". " << heap[i].name 
                 << " | Severity: " << heap[i].severity 
                 << " | VIP: " << (heap[i].isVIP ? "Yes" : "No") << endl;
        }
    }
};

int main() {
    cout << "welcome to world of programming with umar usmani sap : 60199" << endl;
    cout << "Lab 12 Task 1: Hospital Emergency Room Triage System" << endl;
    cout << "=====================================================" << endl;
    
    PatientTriageHeap triage;
    int choice, arrivalCounter = 0;
    
    while(true) {
        cout << "\n1. Admit Patient" << endl;
        cout << "2. Dispatch Next Patient" << endl;
        cout << "3. View Next Patient" << endl;
        cout << "4. Display Queue" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        
        if(choice == 1) {
            string name;
            int severity;
            char vip;
            cout << "Enter patient name: ";
            getline(cin, name);
            cout << "Enter severity (1-10): ";
            cin >> severity;
            cout << "Is VIP? (y/n): ";
            cin >> vip;
            triage.admitPatient(name, severity, (vip == 'y' || vip == 'Y'), ++arrivalCounter);
        }
        else if(choice == 2) {
            triage.dispatchPatient();
        }
        else if(choice == 3) {
            triage.peekNext();
        }
        else if(choice == 4) {
            triage.displayQueue();
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