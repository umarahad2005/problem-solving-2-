#include<iostream>
#include<stack>
#include<algorithm>
using namespace std;

// Function to check operator precedence
int precedence(char op) {
    if(op == '^') return 3;
    if(op == '*' || op == '/') return 2;
    if(op == '+' || op == '-') return 1;
    return 0;
}

// Function to convert infix to prefix
string infixToPrefix(string infix) {
    // Reverse the infix expression
    reverse(infix.begin(), infix.end());
    
    // Replace ( with ) and vice versa
    for(int i = 0; i < infix.length(); i++) {
        if(infix[i] == '(') {
            infix[i] = ')';
        }
        else if(infix[i] == ')') {
            infix[i] = '(';
        }
    }
    
    stack<char> st;
    string prefix = "";
    
    for(int i = 0; i < infix.length(); i++) {
        char ch = infix[i];
        
        // If operand, add to output
        if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) {
            prefix += ch;
        }
        // If '(', push to stack
        else if(ch == '(') {
            st.push(ch);
        }
        // If ')', pop until '('
        else if(ch == ')') {
            while(!st.empty() && st.top() != '(') {
                prefix += st.top();
                st.pop();
            }
            if(!st.empty()) {
                st.pop(); // Remove '('
            }
        }
        // If operator
        else {
            if(ch == '^') {
                while(!st.empty() && precedence(st.top()) >= precedence(ch)) {
                    prefix += st.top();
                    st.pop();
                }
            }
            else {
                while(!st.empty() && precedence(st.top()) > precedence(ch)) {
                    prefix += st.top();
                    st.pop();
                }
            }
            st.push(ch);
        }
    }
    
    // Pop remaining operators
    while(!st.empty()) {
        prefix += st.top();
        st.pop();
    }
    
    // Reverse the result to get prefix
    reverse(prefix.begin(), prefix.end());
    
    return prefix;
}

int main() {
    cout << "welcome to the world of problem solving 2 with umar usmani sap: 60199\n" << endl;
    
    // Example: 5/2+9/(4*2/6)
    string infix = "5/2+9/(4*2/6)";
    
    cout << "Infix Expression: " << infix << endl;
    cout << "Prefix Expression: " << infixToPrefix(infix) << endl;
    
    cout << "\nEnter your own infix expression: ";
    string userInfix;
    cin >> userInfix;
    
    cout << "Infix Expression: " << userInfix << endl;
    cout << "Prefix Expression: " << infixToPrefix(userInfix) << endl;
    
    return 0;
}
