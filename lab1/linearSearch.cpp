#include <iostream>
using namespace std;
void linearSearch(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            cout << "Element " << target << " found at index " << i << "." << endl;
            return;
        }
    }
    cout << "Element " << target << " not found in the array." << endl;
}
int main() {
    int size;
    cout << "Welcome to the world of problem solving 2 by Umar Usmani SAP: 60199" << endl;
    cout << "Enter the size of the array: ";
    cin >> size;

    int* array = new int[size];
    cout << "Enter " << size << " elements for the array:" << endl;
    for (int i = 0; i < size; i++) {
        cout << "Element " << (i + 1) << ": ";
        cin >> array[i];
    }

    int target;
    cout << "Enter the element to search for: ";
    cin >> target;

    linearSearch(array, size, target);

    delete[] array;
    return 0;
}