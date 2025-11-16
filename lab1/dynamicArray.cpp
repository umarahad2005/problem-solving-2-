#include <iostream>
using namespace std;
int main(){
    int size;
    cout << "Welcome to the world of problem solving 2 by Umar Usmani SAP: 60199" << endl;
    cout << "Enter the size of the dynamic array: ";
    cin >> size;

    int* dynamicArray = new int[size]; 
    cout << "Enter " << size << " elements for the dynamic array:" << endl;
    for (int i = 0; i < size; i++) {
        cout << "Element " << (i + 1) << ": ";
        cin >> dynamicArray[i];
    }
    cout<<"\n====================================="<<endl;
    cout << "\nThe dynamic array is: ";
    for (int i = 0; i < size; i++) {
        cout << dynamicArray[i] << " ";
    }
    
    delete[] dynamicArray; 
    return 0;
}