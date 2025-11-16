#include <iostream>
using namespace std;

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
        if (front == 0 && rear == size-1)
            return true;
        else 
            return false;
    }

    bool isEmp(){
        if (front == -1)
            return true;
        else 
            return false;
    }
    
    void enqueue(int val){
        if (isFull()){
            cout << "The queue is already full\n";
        }
        else
        {
            if (front == -1)
                front = 0;
            rear++;
            item[rear] = val;
        }
    }
    
    int dequeue(){
        int val = -1;
        if (isEmp()){
            cout << "The queue is empty" << endl;
        }
        else {
            val = item[front];
            front++;
            if (front > rear) {
                front = -1;
                rear = -1;
            }
        }
        return val;
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
    
    int getCount(){
        if (isEmp())
            return 0;
        return rear - front + 1;
    }
    
    void interleave(){
        if (isEmp()){
            cout << "Queue is empty, cannot interleave\n";
            return;
        }
        
        int count = getCount();
        if (count % 2 != 0){
            cout << "Queue must contain even number of elements to interleave\n";
            return;
        }
        
        int halfSize = count / 2;
        int temp[MAX_SIZE];
        
        for (int i = 0; i < halfSize; i++){
            temp[i] = dequeue();
        }
        
        int result[MAX_SIZE];
        int idx = 0;
        for (int i = 0; i < halfSize; i++){
            result[idx++] = temp[i];
            result[idx++] = dequeue();
        }
        
        for (int i = 0; i < count; i++){
            enqueue(result[i]);
        }
        
        cout << "Queue interleaved successfully!\n";
    }
};

int main(){
    cout << "Welcome to the world of problem solving 2 with umar usmani sap: 60199\n";
    cout << "Task 3: Interleave Queue Elements\n\n";
    
    Queue q;
    int choice, value;
    
    do {
        cout << "\n--- Queue Operations Menu ---\n";
        cout << "1. Enqueue (Add element)\n";
        cout << "2. Dequeue (Remove element)\n";
        cout << "3. Display queue\n";
        cout << "4. Interleave queue\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch(choice){
            case 1:
                cout << "Enter value to enqueue: ";
                cin >> value;
                q.enqueue(value);
                cout << "Value " << value << " inserted successfully\n";
                break;
            case 2:
                value = q.dequeue();
                if (value != -1)
                    cout << "Dequeued value: " << value << endl;
                break;
            case 3:
                q.display();
                break;
            case 4:
                q.interleave();
                break;
            case 5:
                cout << "Exiting program. Thank you!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while(choice != 5);
    
    return 0;
}
