#include <iostream>
using namespace std;
int BubbleSort(int arr[], int size) {
    int count = 0;
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
        count++;
    
    }
    return count;
}
int main() {
    int size;
    cout << "Welcome to the world of problem solving 2 by Umar Usmani SAP: 60199" << endl;
    cout << "Enter the size of the sorted array: ";
    cin >> size;

    int* array = new int[size];
    cout << "Enter " << size << " elements for the sorted array in ascending order:" << endl;
    for (int i = 0; i < size; i++) {
        cout << "Element " << (i + 1) << ": ";
        cin >> array[i];
    }
    BubbleSort(array, size); 
    cout << "=====================================" << endl;
    cout << "The sorted array is: ";
    for (int i = 0; i < size; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
    cout<<"the number of passes taken to sort the array using Bubble Sort is: "<<BubbleSort(array, size)<<endl;

    delete[] array;
    return 0;
}
