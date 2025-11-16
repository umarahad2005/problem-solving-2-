#include <iostream>
using namespace std ;

class Queue
{
    static const int MAX_SIZE = 100;
    int size;
    int item[MAX_SIZE];
    int rear, front;
    public:
    Queue(){
        size = MAX_SIZE;
        front = -1;
        rear = -1;
    }
    bool isFull(){
        if (front == 0&& rear == size-1)
        return true ;
    else 
    return false;

    }

    bool isEmp(){
        if (front == -1)
            return true;
        else 
            return false;
    }
    void enqueue (int val){
        if (isFull()){
            cout << "The queue is already full\n";
        }
        else
        {
            if (front == -1)
                front = 0;
            rear++;
            item[rear] = val;
            cout << "The value " << val << " is inserted in the queue" << endl;
        }
    }
    void dequeue(){
        if (isEmp()){
            cout << "The queue is empty" << endl;
        }
        else {
            cout << "The value " << item[front] << " is deleted successfully!" << endl;
            front++;
            if (front > rear) {
                front = -1;
                rear = -1;
            }
        }
    }
    void display(){
        if (isEmp()){
            cout << "The queue is empty" << endl;
        }
        else{
            cout << "The front index is " << front << endl;
            cout << "Items in the queue are: ";
            for (int i = front; i <= rear; i++){
                cout << item[i] << " ";
            }
            cout << endl << "Rear index of the queue is: " << rear << endl;
        }
    }
    
    int getSize(){
        return size;
    }


};
int main(){
    cout << "Welcome to the world of problem solving 2 with umar usmani sap: 60199\n";
    cout << "Task 1: Simple Queue Operations \n\n";

    
    
    Queue q;
    int choice, value;
    
    do {
        cout << "\n--- Queue Operations Menu ---\n";
        cout << "1. Enqueue (Add element)\n";
        cout << "2. Dequeue (Remove element)\n";
        cout << "3. Display queue\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch(choice){
            case 1:
                cout << "Enter value to enqueue: ";
                cin >> value;
                q.enqueue(value);
                break;
            case 2:
                q.dequeue();
                break;
            case 3:
                q.display();
                break;
           
            case 4:
                cout << "Exiting program. Thank you!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while(choice != 4);
    
    return 0;
}