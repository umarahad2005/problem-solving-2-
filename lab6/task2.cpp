#include<iostream>
#include<stack>
using namespace std;

bool isBalanced(string expr) {
    stack<char> st;
    
    for(int i = 0; i < expr.length(); i++) {
        char ch = expr[i];
        
        // Push opening brackets
        if(ch == '(' || ch == '{' || ch == '[') {
            st.push(ch);
        }
        // Check closing brackets
        else if(ch == ')' || ch == '}' || ch == ']') {
            if(st.empty()) {
                return false;
            }
            
            char top = st.top();
            st.pop();
            
            if((ch == ')' && top != '(') || 
               (ch == '}' && top != '{') || 
               (ch == ']' && top != '[')) {
                return false;
            }
        }
    }
    
    return st.empty();
}

int main() {
    cout << "welcome to the world of problem solving 2 with umar usmani sap: 60199\n" << endl;
    
    cout << "Enter an expression to check if parentheses are balanced: " << endl;
    string expression;
    getline(cin, expression);
    
    if(isBalanced(expression)) {
        cout << "The parentheses are balanced." << endl;
    } else {
        cout << "The parentheses are NOT balanced." << endl;
    }
    
    return 0;
}
