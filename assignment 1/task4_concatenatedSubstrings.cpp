#include<iostream>
#include<vector>
#include<string>
#include<map>
using namespace std;

// Function to find all starting indices of concatenated substrings
vector<int> findSubstring(string s, vector<string>& words) {
    vector<int> result;
    
    if(s.empty() || words.empty()) {
        return result;
    }
    
    int wordLen = words[0].length();
    int wordCount = words.size();
    int totalLen = wordLen * wordCount;
    
    // If total length is greater than string length, no solution
    if(totalLen > s.length()) {
        return result;
    }
    
    // Create frequency map of words
    map<string, int> wordFreq;
    for(int i = 0; i < words.size(); i++) {
        wordFreq[words[i]]++;
    }
    
    // Check each possible starting position
    for(int i = 0; i <= s.length() - totalLen; i++) {
        map<string, int> seen;
        int j;
        
        // Check each word in the window
        for(j = 0; j < wordCount; j++) {
            int wordStart = i + j * wordLen;
            string word = s.substr(wordStart, wordLen);
            
            // If word is not in our word list, break
            if(wordFreq.find(word) == wordFreq.end()) {
                break;
            }
            
            seen[word]++;
            
            // If we've seen this word more times than it appears, break
            if(seen[word] > wordFreq[word]) {
                break;
            }
        }
        
        // If we matched all words, add starting index
        if(j == wordCount) {
            result.push_back(i);
        }
    }
    
    return result;
}

// Function to print result
void printResult(vector<int>& indices) {
    cout << "[";
    for(int i = 0; i < indices.size(); i++) {
        cout << indices[i];
        if(i < indices.size() - 1) cout << ",";
    }
    cout << "]" << endl;
}

int main() {
    cout << "welcome to the world of problem solving 2 with umar usmani sap: 60199\n" << endl;
    cout << "=== Concatenated Substring Finder ===" << endl;
    
    string s;
    int n;
    char choice;
    
    do {
        cout << "\nEnter the main string: ";
        cin >> s;
        
        cout << "Enter the number of words: ";
        cin >> n;
        
        vector<string> words(n);
        cout << "Enter " << n << " words (all must be same length):" << endl;
        for(int i = 0; i < n; i++) {
            cout << "Word " << (i + 1) << ": ";
            cin >> words[i];
        }
        
        // Validate all words have same length
        bool valid = true;
        if(n > 0) {
            int len = words[0].length();
            for(int i = 1; i < n; i++) {
                if(words[i].length() != len) {
                    valid = false;
                    break;
                }
            }
        }
        
        if(!valid) {
            cout << "Error: All words must have the same length!" << endl;
        } else {
            vector<int> result = findSubstring(s, words);
            
            cout << "\nInput: s = \"" << s << "\", words = [";
            for(int i = 0; i < words.size(); i++) {
                cout << "\"" << words[i] << "\"";
                if(i < words.size() - 1) cout << ",";
            }
            cout << "]" << endl;
            
            cout << "Output: ";
            printResult(result);
            
            if(result.empty()) {
                cout << "Explanation: There is no concatenated substring." << endl;
            } else {
                cout << "Explanation:" << endl;
                int wordLen = words[0].length();
                int totalLen = wordLen * words.size();
                for(int i = 0; i < result.size(); i++) {
                    cout << "The substring starting at " << result[i] << " is \"" 
                         << s.substr(result[i], totalLen) << "\"." << endl;
                }
            }
        }
        
        cout << "\nDo you want to try another? (y/n): ";
        cin >> choice;
        
    } while(choice == 'y' || choice == 'Y');
    
    cout << "Exiting..." << endl;
    return 0;
}
