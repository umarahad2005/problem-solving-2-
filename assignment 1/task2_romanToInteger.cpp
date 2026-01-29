#include<iostream>
#include<string>
#include<map>
using namespace std;

// Function to get the integer value of a Roman numeral character
int getValue(char c) {
    switch(c) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default: return 0;
    }
}

// Function to convert Roman numeral to Integer
int romanToInt(string s) {
    int result = 0;
    int n = s.length();
    
    for(int i = 0; i < n; i++) {
        // If current value is less than next value, subtract it (subtractive notation)
        if(i + 1 < n && getValue(s[i]) < getValue(s[i + 1])) {
            result -= getValue(s[i]);
        } else {
            result += getValue(s[i]);
        }
    }
    
    return result;
}

// Function to validate Roman numeral string
bool isValidRoman(string s) {
    for(int i = 0; i < s.length(); i++) {
        char c = s[i];
        if(c != 'I' && c != 'V' && c != 'X' && c != 'L' && 
           c != 'C' && c != 'D' && c != 'M') {
            return false;
        }
    }
    return true;
}

int main() {
    cout << "welcome to the world of problem solving 2 with umar usmani sap: 60199\n" << endl;
    cout << "=== Roman Numeral to Integer Converter ===" << endl;
    
    cout << "\nRoman Numeral Values:" << endl;
    cout << "Symbol\tValue" << endl;
    cout << "I\t1" << endl;
    cout << "V\t5" << endl;
    cout << "X\t10" << endl;
    cout << "L\t50" << endl;
    cout << "C\t100" << endl;
    cout << "D\t500" << endl;
    cout << "M\t1000" << endl;
    
    string roman;
    char choice;
    
    do {
        cout << "\nEnter a Roman numeral: ";
        cin >> roman;
        
        // Convert to uppercase for consistency
        for(int i = 0; i < roman.length(); i++) {
            if(roman[i] >= 'a' && roman[i] <= 'z') {
                roman[i] = roman[i] - 32;
            }
        }
        
        if(!isValidRoman(roman)) {
            cout << "Invalid Roman numeral! Please use only I, V, X, L, C, D, M" << endl;
        } else {
            int result = romanToInt(roman);
            cout << "\nInput: s = \"" << roman << "\"" << endl;
            cout << "Output: " << result << endl;
            
            // Show explanation
            cout << "Explanation: ";
            for(int i = 0; i < roman.length(); i++) {
                if(i + 1 < roman.length() && getValue(roman[i]) < getValue(roman[i + 1])) {
                    cout << roman[i] << roman[i + 1] << " = " << (getValue(roman[i + 1]) - getValue(roman[i]));
                    i++; // Skip next character as it's part of subtractive pair
                } else {
                    cout << roman[i] << " = " << getValue(roman[i]);
                }
                if(i < roman.length() - 1) cout << ", ";
            }
            cout << endl;
        }
        
        cout << "\nDo you want to convert another? (y/n): ";
        cin >> choice;
        
    } while(choice == 'y' || choice == 'Y');
    
    cout << "Exiting..." << endl;
    return 0;
}
