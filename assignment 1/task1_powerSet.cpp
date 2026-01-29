#include<iostream>
#include<vector>
using namespace std;

// Function to generate all subsets using backtracking
void generateSubsets(vector<int>& nums, int index, vector<int>& current, vector<vector<int>>& result) {
    // Add current subset to result
    result.push_back(current);
    
    // Generate subsets by including elements from index onwards
    for(int i = index; i < nums.size(); i++) {
        current.push_back(nums[i]);
        generateSubsets(nums, i + 1, current, result);
        current.pop_back(); // backtrack
    }
}

// Function to print all subsets
void printSubsets(vector<vector<int>>& subsets) {
    cout << "[";
    for(int i = 0; i < subsets.size(); i++) {
        cout << "[";
        for(int j = 0; j < subsets[i].size(); j++) {
            cout << subsets[i][j];
            if(j < subsets[i].size() - 1) cout << ",";
        }
        cout << "]";
        if(i < subsets.size() - 1) cout << ",";
    }
    cout << "]" << endl;
}

int main() {
    cout << "welcome to the world of problem solving 2 with umar usmani sap: 60199\n" << endl;
    cout << "=== Power Set Generator ===" << endl;
    
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;
    
    vector<int> nums(n);
    cout << "Enter " << n << " unique elements:" << endl;
    for(int i = 0; i < n; i++) {
        cout << "Element " << (i + 1) << ": ";
        cin >> nums[i];
    }
    
    vector<vector<int>> result;
    vector<int> current;
    
    generateSubsets(nums, 0, current, result);
    
    cout << "\nInput: nums = [";
    for(int i = 0; i < nums.size(); i++) {
        cout << nums[i];
        if(i < nums.size() - 1) cout << ",";
    }
    cout << "]" << endl;
    
    cout << "Output: ";
    printSubsets(result);
    
    cout << "\nTotal subsets (Power Set): " << result.size() << endl;
    
    return 0;
}
