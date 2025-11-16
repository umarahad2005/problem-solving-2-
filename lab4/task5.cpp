#include <iostream>
#include <string>
using namespace std;

// Print Job structure
struct PrintJob {
    int jobId;
    string userName;
    int priority;  // 1 = High, 2 = Medium, 3 = Low
    int arrivalTime;
    PrintJob* next;
};

class PrintQueue
{
    PrintJob* front;
    PrintJob* rear;
    int jobCount;
    int timeCounter;
    
    public:
    PrintQueue(){
        front = NULL;
        rear = NULL;
        jobCount = 0;
        timeCounter = 0;
    }
    
    bool isEmp(){
        if (front == NULL)
            return true;
        else 
            return false;
    }
    
    void enqueue(int jobId, string userName, int priority){
        PrintJob* newJob = new PrintJob;
        newJob->jobId = jobId;
        newJob->userName = userName;
        newJob->priority = priority;
        newJob->arrivalTime = timeCounter++;
        newJob->next = NULL;
        
        // Insert based on priority (and FIFO for same priority)
        if (isEmp() || front->priority > priority || 
            (front->priority == priority && front->arrivalTime > newJob->arrivalTime)){
            newJob->next = front;
            front = newJob;
            if (rear == NULL){
                rear = newJob;
            }
        }
        else {
            PrintJob* current = front;
            while (current->next != NULL && 
                   (current->next->priority < priority || 
                    (current->next->priority == priority && current->next->arrivalTime <= newJob->arrivalTime))){
                current = current->next;
            }
            newJob->next = current->next;
            current->next = newJob;
            if (newJob->next == NULL){
                rear = newJob;
            }
        }
        
        jobCount++;
        string priorityStr = (priority == 1) ? "High" : (priority == 2) ? "Medium" : "Low";
        cout << "Print Job " << jobId << " from " << userName << " added with " << priorityStr << " priority\n";
    }
    
    void dequeue(){
        if (isEmp()){
            cout << "The print queue is empty, no jobs to process!" << endl;
        }
        else {
            PrintJob* temp = front;
            string priorityStr = (temp->priority == 1) ? "High" : (temp->priority == 2) ? "Medium" : "Low";
            
            cout << "\n--- Processing Print Job ---\n";
            cout << "Job ID: " << temp->jobId << endl;
            cout << "User: " << temp->userName << endl;
            cout << "Priority: " << priorityStr << endl;
            cout << "Arrival Time: " << temp->arrivalTime << endl;
            
            front = front->next;
            if (front == NULL){
                rear = NULL;
            }
            delete temp;
            jobCount--;
            cout << "Print job processed successfully!\n";
        }
    }
    
    void display(){
        if (isEmp()){
            cout << "The print queue is empty" << endl;
        }
        else {
            cout << "\n--- Print Jobs in Queue (Priority Order) ---\n";
            PrintJob* temp = front;
            int position = 1;
            while (temp != NULL){
                string priorityStr = (temp->priority == 1) ? "High" : (temp->priority == 2) ? "Medium" : "Low";
                cout << position << ". Job ID: " << temp->jobId << ", User: " << temp->userName 
                     << ", Priority: " << priorityStr << ", Arrival: " << temp->arrivalTime << endl;
                temp = temp->next;
                position++;
            }
            cout << "Total jobs in queue: " << jobCount << endl;
        }
    }
    
    int getCount(){
        return jobCount;
    }
    
    ~PrintQueue(){
        while (!isEmp()){
            PrintJob* temp = front;
            front = front->next;
            delete temp;
        }
    }
};

int main(){
    cout << "Welcome to the world of problem solving 2 with umar usmani sap: 60199\n";
    cout << "Task 5: Print Server Queue Management System\n\n";
    
    PrintQueue pq;
    int choice, jobId, priority;
    string userName;
    
    do {
        cout << "\n--- Print Server Menu ---\n";
        cout << "1. Add print job\n";
        cout << "2. Process next job (Dequeue)\n";
        cout << "3. Display all jobs\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch(choice){
            case 1:
                cout << "Enter job ID: ";
                cin >> jobId;
                cin.ignore();
                cout << "Enter user name: ";
                getline(cin, userName);
                cout << "Enter priority (1=High, 2=Medium, 3=Low): ";
                cin >> priority;
                if (priority < 1 || priority > 3){
                    cout << "Invalid priority! Setting to Low (3)\n";
                    priority = 3;
                }
                pq.enqueue(jobId, userName, priority);
                break;
            case 2:
                pq.dequeue();
                break;
            case 3:
                pq.display();
                break;
            case 4:
                cout << "Exiting Print Server System. Thank you!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while(choice != 4);
    
    return 0;
}
