#include<iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    
    Node(int val) {
        data = val;
        next = NULL;
    }
};

class Stack {
    Node* top;
    
public:
    Stack() {
        top = NULL;
    }
    
    void push(int val) {
        Node* newNode = new Node(val);
        newNode->next = top;
        top = newNode;
        cout << "Pushed " << val << " onto stack" << endl;
    }
    
    int pop() {
        if(isEmpty()) {
            cout << "Stack Underflow" << endl;
            return -1;
        }
        Node* temp = top;
        int popped = top->data;
        top = top->next;
        delete temp;
        return popped;
    }
    
    int peek() {
        if(isEmpty()) {
            cout << "Stack is empty" << endl;
            return -1;
        }
        return top->data;
    }
    
    bool isEmpty() {
        return top == NULL;
    }
    
    void display() {
        if(isEmpty()) {
            cout << "Stack is empty" << endl;
            return;
        }
        
        cout << "Stack elements are: ";
        Node* temp = top;
        while(temp != NULL) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() {
    cout << "welcome to the world of problem solving 2 with umar usmani sap: 60199\n" << endl;
    
    Stack s;
    
    cout << "Stack operations using Linked List:\n" << endl;
    cout << "1. Push\n2. Pop\n3. Peek\n4. Display\n5. Exit" << endl;
    
    int choice, value;
    
    while(true) {
        cout << "\nEnter your choice: ";
        cin >> choice;
        
        switch(choice) {
            case 1:
                cout << "Enter value to push: ";
                cin >> value;
                s.push(value);
                break;
            case 2:
                {
                    int popped = s.pop();
                    if(popped != -1) {
                        cout << "Popped " << popped << " from stack" << endl;
                    }
                }
                break;
            case 3:
                {
                    int topVal = s.peek();
                    if(topVal != -1) {
                        cout << "Top element is: " << topVal << endl;
                    }
                }
                break;
            case 4:
                s.display();
                break;
            case 5:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice" << endl;
        }
    }
    
    return 0;
}
