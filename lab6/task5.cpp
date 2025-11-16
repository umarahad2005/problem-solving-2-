#include<iostream>
#include<stack>
using namespace std;

// Function to check operator precedence
int precedence(char op) {
    if(op == '^') return 3;
    if(op == '*' || op == '/') return 2;
    if(op == '+' || op == '-') return 1;
    return 0;
}

// Function to convert infix to postfix
string infixToPostfix(string infix) {
    stack<char> st;
    string postfix = "";
    
    for(int i = 0; i < infix.length(); i++) {
        char ch = infix[i];
        
        // If operand, add to output
        if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) {
            postfix += ch;
        }
        // If '(', push to stack
        else if(ch == '(') {
            st.push(ch);
        }
        // If ')', pop until '('
        else if(ch == ')') {
            while(!st.empty() && st.top() != '(') {
                postfix += st.top();
                st.pop();
            }
            if(!st.empty()) {
                st.pop(); // Remove '('
            }
        }
        // If operator
        else {
            while(!st.empty() && precedence(st.top()) >= precedence(ch)) {
                postfix += st.top();
                st.pop();
            }
            st.push(ch);
        }
    }
    
    // Pop remaining operators
    while(!st.empty()) {
        postfix += st.top();
        st.pop();
    }
    
    return postfix;
}

int main() {
    cout << "welcome to the world of problem solving 2 with umar usmani sap: 60199\n" << endl;
    
    // Example: (4*2)+6/5*4
    string infix = "(4*2)+6/5*4";
    
    cout << "Infix Expression: " << infix << endl;
    cout << "Postfix Expression: " << infixToPostfix(infix) << endl;
    
    cout << "\nEnter your own infix expression: ";
    string userInfix;
    cin >> userInfix;
    
    cout << "Infix Expression: " << userInfix << endl;
    cout << "Postfix Expression: " << infixToPostfix(userInfix) << endl;
    
    return 0;
}
