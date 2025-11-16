#include<iostream>
#include<string>
using namespace std;

enum Priority {
    CRITICAL = 1,
    SERIOUS = 2,
    STABLE = 3
};

class Patient {
public:
    string name;
    int age;
    Priority priority;
    bool ambulance;
    Patient* next;
    
    Patient(string n, int a, Priority p, bool amb) {
        name = n;
        age = a;
        priority = p;
        ambulance = amb;
        next = NULL;
    }
};

class EmergencyRoom {
    Patient* head;
    int criticalCount;
    int seriousCount;
    int stableCount;
    
public:
    EmergencyRoom() {
        head = NULL;
        criticalCount = 0;
        seriousCount = 0;
        stableCount = 0;
    }
    
    // Enqueue patient with priority
    void enqueuePatient(string name, int age, Priority priority, bool ambulance) {
        Patient* newPatient = new Patient(name, age, priority, ambulance);
        
        // Update counts
        if(priority == CRITICAL) criticalCount++;
        else if(priority == SERIOUS) seriousCount++;
        else stableCount++;
        
        if(head == NULL) {
            head = newPatient;
            cout << "Added patient: " << name << " [" << getPriorityString(priority) << "]" << endl;
            return;
        }
        
        // Insert based on priority
        if(newPatient->priority < head->priority) {
            newPatient->next = head;
            head = newPatient;
            cout << "Added patient: " << name << " [" << getPriorityString(priority) << "]" << endl;
            return;
        }
        
        Patient* temp = head;
        while(temp->next != NULL && temp->next->priority <= newPatient->priority) {
            temp = temp->next;
        }
        
        newPatient->next = temp->next;
        temp->next = newPatient;
        cout << "Added patient: " << name << " [" << getPriorityString(priority) << "]" << endl;
    }
    
    // Treat highest priority patient
    void treatPatient() {
        if(head == NULL) {
            cout << "No patients waiting" << endl;
            return;
        }
        
        Patient* treated = head;
        head = head->next;
        
        cout << "Treating patient: " << treated->name << " [" 
             << getPriorityString(treated->priority) << "]" << endl;
        
        if(treated->priority == CRITICAL) criticalCount--;
        else if(treated->priority == SERIOUS) seriousCount--;
        else stableCount--;
        
        delete treated;
    }
    
    // Upgrade priority
    void upgradePriority(string name) {
        if(head == NULL) {
            cout << "No patients waiting" << endl;
            return;
        }
        
        Patient* temp = head;
        Patient* prev = NULL;
        
        while(temp != NULL && temp->name != name) {
            prev = temp;
            temp = temp->next;
        }
        
        if(temp == NULL) {
            cout << "Patient not found" << endl;
            return;
        }
        
        if(temp->priority == CRITICAL) {
            cout << "Already at highest priority" << endl;
            return;
        }
        
        // Update counts
        if(temp->priority == SERIOUS) {
            seriousCount--;
            criticalCount++;
        } else {
            stableCount--;
            seriousCount++;
        }
        
        // Remove from current position
        if(prev == NULL) {
            head = temp->next;
        } else {
            prev->next = temp->next;
        }
        
        // Upgrade priority
        temp->priority = (Priority)(temp->priority - 1);
        temp->next = NULL;
        
        // Reinsert at new position
        if(head == NULL || temp->priority < head->priority) {
            temp->next = head;
            head = temp;
        } else {
            Patient* current = head;
            while(current->next != NULL && current->next->priority <= temp->priority) {
                current = current->next;
            }
            temp->next = current->next;
            current->next = temp;
        }
        
        cout << "Upgraded " << name << " to " << getPriorityString(temp->priority) << endl;
    }
    
    // Get estimated wait time
    void getWaitTime(Priority priority) {
        int position = 0;
        Patient* temp = head;
        
        while(temp != NULL && temp->priority < priority) {
            position++;
            temp = temp->next;
        }
        
        int waitMinutes = position * 15; // Assume 15 min per patient
        
        cout << "Estimated wait for " << getPriorityString(priority) 
             << ": ~" << waitMinutes << " minutes" << endl;
    }
    
    // Display queue
    void displayQueue() {
        if(head == NULL) {
            cout << "No patients waiting" << endl;
            return;
        }
        
        cout << "\n=== ER Triage Queue ===" << endl;
        cout << "Critical: " << criticalCount << " | Serious: " 
             << seriousCount << " | Stable: " << stableCount << endl;
        cout << "------------------------" << endl;
        
        Patient* temp = head;
        int position = 1;
        
        while(temp != NULL) {
            cout << position++ << ". " << temp->name << " (Age: " << temp->age 
                 << ") [" << getPriorityString(temp->priority) << "]";
            if(temp->ambulance) cout << " *AMBULANCE*";
            cout << endl;
            temp = temp->next;
        }
    }
    
private:
    string getPriorityString(Priority p) {
        if(p == CRITICAL) return "CRITICAL";
        if(p == SERIOUS) return "SERIOUS";
        return "STABLE";
    }
};

int main() {
    cout << "welcome to the world of problem solving 2 with umar usmani sap: 60199\n" << endl;
    
    EmergencyRoom er;
    int choice;
    
    while(true) {
        cout << "\n=== Hospital ER Triage System ===" << endl;
        cout << "1. Add Patient" << endl;
        cout << "2. Treat Next Patient" << endl;
        cout << "3. Upgrade Patient Priority" << endl;
        cout << "4. Check Wait Time" << endl;
        cout << "5. Display Queue" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        
        if(choice == 1) {
            string name;
            int age, priorityNum;
            char amb;
            
            cout << "Enter patient name: ";
            getline(cin, name);
            cout << "Enter age: ";
            cin >> age;
            cout << "Enter priority (1=Critical, 2=Serious, 3=Stable): ";
            cin >> priorityNum;
            cout << "Ambulance arrival? (y/n): ";
            cin >> amb;
            
            Priority p = (Priority)priorityNum;
            bool ambulance = (amb == 'y' || amb == 'Y');
            
            er.enqueuePatient(name, age, p, ambulance);
        }
        else if(choice == 2) {
            er.treatPatient();
        }
        else if(choice == 3) {
            string name;
            cin.ignore();
            cout << "Enter patient name: ";
            getline(cin, name);
            er.upgradePriority(name);
        }
        else if(choice == 4) {
            int priorityNum;
            cout << "Enter priority (1=Critical, 2=Serious, 3=Stable): ";
            cin >> priorityNum;
            er.getWaitTime((Priority)priorityNum);
        }
        else if(choice == 5) {
            er.displayQueue();
        }
        else if(choice == 6) {
            cout << "Exiting..." << endl;
            break;
        }
        else {
            cout << "Invalid choice!" << endl;
        }
    }
    
    return 0;
}
