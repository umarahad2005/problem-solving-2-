#include<iostream>
using namespace std;

class Stack {
    static const int MAX_SIZE = 100;
    int top;
    int arr[MAX_SIZE];
public:
    Stack() {
        top = -1;
    }
    bool isFull() {
        return top == MAX_SIZE - 1;
    }
    bool isEmpty() {
        return top == -1;
    }
    void push(int val) {
        if (isFull()) {
            cout << "Stack Overflow\n";
        } else {
            arr[++top] = val;
            cout << "Pushed " << val << " onto stack\n";
        }
    }
    int pop() {
        if (isEmpty()) {
            cout << "Stack Underflow\n";
            return -1;
        } else {
            return arr[top--];
        }
    }
    void peek() {
        if (isEmpty()) {
            cout << "Stack is empty\n";
        } else {
            cout << "Top element is: " << arr[top] << endl;
        }
    }
    void display() {
        if (isEmpty()) {
            cout << "Stack is empty\n";
        } else {
            cout << "Stack elements are: ";
            for (int i = top; i >= 0; i--) {
                cout << arr[i] << " ";
            }
            cout << endl;
        }
    }
};
int main(){
    cout<<"welcome to the world of problem solving 2 with umar usmani sap: 60199\n"<<endl;
    Stack s;
    int n;
    
    while(true) {
        cout<<"\nKindly enter the number to perform stack operations:\n"<<endl;
        cout<<"1. Push a value\n2. Pop\n3. Peek\n4. Display\n5. Exit\n"<<endl;
        cout<<"Enter choice: ";
        cin>>n; 
        
        switch (n)
        {
        case 1:
            cout<<"Enter the value to be pushed: ";
            int m;
            cin>>m;
            s.push(m);
            break;
        
        case 2:
            {
                int popped = s.pop();
                if (popped != -1) {
                    cout << "Popped " << popped << " from stack\n";
                }
            }
            break;
        case 3:
            s.peek();
            break;
        case 4:
            s.display();
            break;
        case 5:
            cout << "Exiting...\n";
            return 0;
        default:
            cout << "Invalid choice\n";
            break;
        }
    }
    
    return 0;
}