#include <iostream>
using namespace std;
int selectionsort(int arr[], int size) {
    int count = 0;
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
        count++;
    }
    return count;
}
int main(){
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

    selectionsort(array, size);
    cout << "=====================================" << endl;
    cout << "The sorted array is: ";
    for (int i = 0; i < size; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
    cout<<"the number of passes taken to sort the array using Selection Sort is: "<<selectionsort(array, size)<<endl;

    delete[] array;
    return 0;

}