#include<iostream>
#include<stack>
using namespace std;

void sortStack(stack<int>& st) {
    stack<int> tempStack;
    
    while(!st.empty()) {
        int temp = st.top();
        st.pop();
        
        // Move elements from tempStack to st that are greater than temp
        while(!tempStack.empty() && tempStack.top() > temp) {
            st.push(tempStack.top());
            tempStack.pop();
        }
        
        // Push temp to tempStack
        tempStack.push(temp);
    }
    
    // Copy sorted elements back to original stack
    while(!tempStack.empty()) {
        st.push(tempStack.top());
        tempStack.pop();
    }
}

void displayStack(stack<int> st) {
    if(st.empty()) {
        cout << "Stack is empty" << endl;
        return;
    }
    
    cout << "Stack elements (top to bottom): ";
    while(!st.empty()) {
        cout << st.top() << " ";
        st.pop();
    }
    cout << endl;
}

int main() {
    cout << "welcome to the world of problem solving 2 with umar usmani sap: 60199\n" << endl;
    
    stack<int> st;
    
    cout << "Enter the number of elements to push: ";
    int n;
    cin >> n;
    
    cout << "Enter " << n << " elements:" << endl;
    for(int i = 0; i < n; i++) {
        int val;
        cin >> val;
        st.push(val);
    }
    
    cout << "\nOriginal stack:" << endl;
    displayStack(st);
    
    // Sort the stack
    sortStack(st);
    
    cout << "\nSorted stack (ascending order):" << endl;
    displayStack(st);
    
    return 0;
}
