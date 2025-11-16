#include<iostream>
#include<stack>
using namespace std;

void reverseString(string s) {
    stack<char> st;
    
    // Push all characters onto the stack
    for(int i = 0; i < s.length(); i++) {
        st.push(s[i]);
    }
    
    // Pop all characters and print
    cout << "Reversed string: ";
    while(!st.empty()) {
        cout << st.top();
        st.pop();
    }
    cout << endl;
}

int main() {
    cout << "welcome to the world of problem solving 2 with umar usmani sap: 60199\n" << endl;
    
    cout << "Enter a string to reverse: " << endl;
    string str;
    getline(cin, str);
    
    reverseString(str);
    
    return 0;
}
