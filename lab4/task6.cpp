#include <iostream>
#include <string>
using namespace std;

// Customer structure
struct Customer {
    int id;
    string name;
    int arrivalTime;
    Customer* next;
};

class ServiceQueue
{
    Customer* front;
    Customer* rear;
    int customerCount;
    int currentTime;
    int serviceTime;  // Time to serve one customer
    
    public:
    ServiceQueue(){
        front = NULL;
        rear = NULL;
        customerCount = 0;
        currentTime = 0;
        serviceTime = 5;  // Default 5 minutes per customer
    }
    
    bool isEmp(){
        if (front == NULL)
            return true;
        else 
            return false;
    }
    
    void joinLine(int id, string name){
        Customer* newCustomer = new Customer;
        newCustomer->id = id;
        newCustomer->name = name;
        newCustomer->arrivalTime = currentTime;
        newCustomer->next = NULL;
        
        if (isEmp()){
            front = rear = newCustomer;
        }
        else {
            rear->next = newCustomer;
            rear = newCustomer;
        }
        customerCount++;
        currentTime++;
        cout << "Customer " << name << " (ID: " << id << ") joined the line at time " << newCustomer->arrivalTime << endl;
    }
    
    void serveCustomer(){
        if (isEmp()){
            cout << "No customers in line to serve!" << endl;
        }
        else {
            Customer* temp = front;
            int waitTime = currentTime - temp->arrivalTime;
            
            cout << "\n--- Serving Customer ---\n";
            cout << "Customer ID: " << temp->id << endl;
            cout << "Customer Name: " << temp->name << endl;
            cout << "Arrival Time: " << temp->arrivalTime << endl;
            cout << "Current Time: " << currentTime << endl;
            cout << "Wait Time: " << waitTime << " minutes" << endl;
            
            front = front->next;
            if (front == NULL){
                rear = NULL;
            }
            delete temp;
            customerCount--;
            currentTime += serviceTime;
            cout << "Customer served successfully! Service completed at time " << currentTime << endl;
        }
    }
    
    void display(){
        if (isEmp()){
            cout << "No customers waiting in line" << endl;
        }
        else {
            cout << "\n--- Customers Waiting in Line ---\n";
            Customer* temp = front;
            int position = 1;
            while (temp != NULL){
                int waitTime = currentTime - temp->arrivalTime;
                cout << position << ". ID: " << temp->id << ", Name: " << temp->name 
                     << ", Arrival: " << temp->arrivalTime << ", Wait Time: " << waitTime << " min" << endl;
                temp = temp->next;
                position++;
            }
            cout << "Total customers waiting: " << customerCount << endl;
        }
    }
    
    void checkWaitTime(){
        if (isEmp()){
            cout << "No wait! You can be served immediately.\n";
        }
        else {
            int estimatedWait = customerCount * serviceTime;
            cout << "Estimated wait time for new customer: " << estimatedWait << " minutes" << endl;
            cout << "Current queue length: " << customerCount << " customers" << endl;
        }
    }
    
    int getCount(){
        return customerCount;
    }
    
    void setServiceTime(int time){
        serviceTime = time;
        cout << "Service time updated to " << serviceTime << " minutes per customer\n";
    }
    
    ~ServiceQueue(){
        while (!isEmp()){
            Customer* temp = front;
            front = front->next;
            delete temp;
        }
    }
};

int main(){
    cout << "Welcome to the world of problem solving 2 with umar usmani sap: 60199\n";
    cout << "Task 6: Customer Service Center Queue Simulation\n\n";
    
    ServiceQueue sq;
    int choice, id;
    string name;
    
    do {
        cout << "\n--- Customer Service Center Menu ---\n";
        cout << "1. Customer joins the line\n";
        cout << "2. Agent serves next customer\n";
        cout << "3. Display waiting customers\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch(choice){
            case 1:
                cout << "Enter customer ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter customer name: ";
                getline(cin, name);
                sq.joinLine(id, name);
                break;
            case 2:
                sq.serveCustomer();
                break;
            case 3:
                sq.display();
                break;
            case 4:
                cout << "Exiting Customer Service Center System. Thank you!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while(choice != 4);
    
    return 0;
}
