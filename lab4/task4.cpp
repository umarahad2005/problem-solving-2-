#include <iostream>
#include <string>
using namespace std;

// Customer structure
struct Customer {
    int id;
    string name;
    string transactionType;
    Customer* next;
};

class BankQueue
{
    Customer* front;
    Customer* rear;
    int customerCount;
    
    public:
    BankQueue(){
        front = NULL;
        rear = NULL;
        customerCount = 0;
    }
    
    bool isEmp(){
        if (front == NULL)
            return true;
        else 
            return false;
    }
    
    void enqueue(int id, string name, string transactionType){
        Customer* newCustomer = new Customer;
        newCustomer->id = id;
        newCustomer->name = name;
        newCustomer->transactionType = transactionType;
        newCustomer->next = NULL;
        
        if (isEmp()){
            front = rear = newCustomer;
        }
        else {
            rear->next = newCustomer;
            rear = newCustomer;
        }
        customerCount++;
        cout << "Customer " << name << " (ID: " << id << ") added to the queue for " << transactionType << endl;
    }
    
    void dequeue(){
        if (isEmp()){
            cout << "The queue is empty, no customers to serve!" << endl;
        }
        else {
            Customer* temp = front;
            cout << "Serving Customer: " << temp->name << " (ID: " << temp->id << ")" << endl;
            cout << "Transaction Type: " << temp->transactionType << endl;
            
            front = front->next;
            if (front == NULL){
                rear = NULL;
            }
            delete temp;
            customerCount--;
            cout << "Customer served successfully!\n";
        }
    }
    
    void display(){
        if (isEmp()){
            cout << "The queue is empty, no customers waiting" << endl;
        }
        else {
            cout << "\n--- Customers Waiting in Queue ---\n";
            Customer* temp = front;
            int position = 1;
            while (temp != NULL){
                cout << position << ". ID: " << temp->id << ", Name: " << temp->name 
                     << ", Transaction: " << temp->transactionType << endl;
                temp = temp->next;
                position++;
            }
            cout << "Total customers waiting: " << customerCount << endl;
        }
    }
    
    int getCount(){
        return customerCount;
    }
    
    ~BankQueue(){
        while (!isEmp()){
            Customer* temp = front;
            front = front->next;
            delete temp;
        }
    }
};

int main(){
    cout << "Welcome to the world of problem solving 2 with umar usmani sap: 60199\n";
    cout << "Task 4: Bank Queue Management System (Linked List Implementation)\n\n";
    
    BankQueue bq;
    int choice, id;
    string name, transactionType;
    
    do {
        cout << "\n--- Bank Queue Management Menu ---\n";
        cout << "1. Add customer to queue\n";
        cout << "2. Serve customer (Dequeue)\n";
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
                cout << "Enter transaction type (Deposit/Withdrawal/Inquiry): ";
                getline(cin, transactionType);
                bq.enqueue(id, name, transactionType);
                break;
            case 2:
                bq.dequeue();
                break;
            case 3:
                bq.display();
                break;
            case 4:
                cout << "Exiting Bank Queue Management System. Thank you!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while(choice != 4);
    
    return 0;
}
