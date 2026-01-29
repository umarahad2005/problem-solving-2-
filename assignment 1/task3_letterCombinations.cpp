#include<iostream>
#include<vector>
#include<string>
using namespace std;

// Phone keypad mapping (2-9)
string phoneMap[] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

// Backtracking function to generate all letter combinations
void backtrack(string& digits, int index, string& current, vector<string>& result) {
    // If we've processed all digits, add current combination to result
    if(index == digits.length()) {
        if(!current.empty()) {
            result.push_back(current);
        }
        return;
    }
    
    // Get the letters for current digit
    int digit = digits[index] - '0';
    string letters = phoneMap[digit];
    
    // Try each letter for this digit
    for(int i = 0; i < letters.length(); i++) {
        current.push_back(letters[i]);
        backtrack(digits, index + 1, current, result);
        current.pop_back(); // backtrack
    }
}

// Function to get letter combinations
vector<string> letterCombinations(string digits) {
    vector<string> result;
    string current = "";
    
    if(digits.empty()) {
        return result;
    }
    
    backtrack(digits, 0, current, result);
    return result;
}

// Function to validate digit string
bool isValidDigits(string s) {
    for(int i = 0; i < s.length(); i++) {
        if(s[i] < '2' || s[i] > '9') {
            return false;
        }
    }
    return true;
}

// Function to print result
void printResult(vector<string>& combinations) {
    cout << "[";
    for(int i = 0; i < combinations.size(); i++) {
        cout << "\"" << combinations[i] << "\"";
        if(i < combinations.size() - 1) cout << ",";
    }
    cout << "]" << endl;
}

int main() {
    cout << "welcome to the world of problem solving 2 with umar usmani sap: 60199\n" << endl;
    cout << "=== Phone Keypad Letter Combinations ===" << endl;
    
    cout << "\nPhone Keypad Mapping:" << endl;
    cout << "2 -> abc" << endl;
    cout << "3 -> def" << endl;
    cout << "4 -> ghi" << endl;
    cout << "5 -> jkl" << endl;
    cout << "6 -> mno" << endl;
    cout << "7 -> pqrs" << endl;
    cout << "8 -> tuv" << endl;
    cout << "9 -> wxyz" << endl;
    
    string digits;
    char choice;
    
    do {
        cout << "\nEnter digits (2-9): ";
        cin >> digits;
        
        if(!isValidDigits(digits)) {
            cout << "Invalid input! Please enter only digits from 2 to 9" << endl;
        } else {
            vector<string> result = letterCombinations(digits);
            
            cout << "\nInput: digits = \"" << digits << "\"" << endl;
            cout << "Output: ";
            printResult(result);
            cout << "Total combinations: " << result.size() << endl;
        }
        
        cout << "\nDo you want to try another? (y/n): ";
        cin >> choice;
        
    } while(choice == 'y' || choice == 'Y');
    
    cout << "Exiting..." << endl;
    return 0;
}
