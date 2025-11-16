#include<iostream>
using namespace std;

class TwoStacks {
    static const int MAX_SIZE = 100;
    int arr[MAX_SIZE];
    int top1, top2;
    
public:
    TwoStacks() {
        top1 = -1;
        top2 = MAX_SIZE;
    }
    
    void push1(int val) {
        if(top1 < top2 - 1) {
            arr[++top1] = val;
            cout << "Pushed " << val << " to Stack 1" << endl;
        } else {
            cout << "Stack Overflow! Cannot push to Stack 1" << endl;
        }
    }
    
    void push2(int val) {
        if(top1 < top2 - 1) {
            arr[--top2] = val;
            cout << "Pushed " << val << " to Stack 2" << endl;
        } else {
            cout << "Stack Overflow! Cannot push to Stack 2" << endl;
        }
    }
    
    int pop1() {
        if(top1 >= 0) {
            int val = arr[top1--];
            return val;
        } else {
            cout << "Stack 1 Underflow!" << endl;
            return -1;
        }
    }
    
    int pop2() {
        if(top2 < MAX_SIZE) {
            int val = arr[top2++];
            return val;
        } else {
            cout << "Stack 2 Underflow!" << endl;
            return -1;
        }
    }
    
    void display1() {
        if(top1 == -1) {
            cout << "Stack 1 is empty" << endl;
            return;
        }
        cout << "Stack 1 elements: ";
        for(int i = top1; i >= 0; i--) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    
    void display2() {
        if(top2 == MAX_SIZE) {
            cout << "Stack 2 is empty" << endl;
            return;
        }
        cout << "Stack 2 elements: ";
        for(int i = top2; i < MAX_SIZE; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    cout << "welcome to the world of problem solving 2 with umar usmani sap: 60199\n" << endl;
    
    TwoStacks ts;
    
    cout << "Two Stacks in Single Array Implementation\n" << endl;
    cout << "1. Push to Stack 1\n2. Push to Stack 2\n3. Pop from Stack 1" << endl;
    cout << "4. Pop from Stack 2\n5. Display Stack 1\n6. Display Stack 2\n7. Exit" << endl;
    
    int choice, value;
    
    while(true) {
        cout << "\nEnter your choice: ";
        cin >> choice;
        
        switch(choice) {
            case 1:
                cout << "Enter value to push to Stack 1: ";
                cin >> value;
                ts.push1(value);
                break;
            case 2:
                cout << "Enter value to push to Stack 2: ";
                cin >> value;
                ts.push2(value);
                break;
            case 3:
                {
                    int popped = ts.pop1();
                    if(popped != -1) {
                        cout << "Popped " << popped << " from Stack 1" << endl;
                    }
                }
                break;
            case 4:
                {
                    int popped = ts.pop2();
                    if(popped != -1) {
                        cout << "Popped " << popped << " from Stack 2" << endl;
                    }
                }
                break;
            case 5:
                ts.display1();
                break;
            case 6:
                ts.display2();
                break;
            case 7:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice" << endl;
        }
    }
    
    return 0;
}
