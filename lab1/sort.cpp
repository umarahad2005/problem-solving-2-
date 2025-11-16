#include <iostream>
using namespace std;


void sortarr(int array[5]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4 - i; j++) 
        {
            if (array[j] > array[j + 1]) 
            {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

int main() {
    int arr[5];
        cout << "welcome to the world of problem solving 2 by umar usmani sap : 60199 "<< endl;


    cout << "kindly enter the element in the array " << endl;
    for (int i = 0; i < 5; i++) 
    {
        cout << "Element " << (i + 1) << ": ";
        cin >> arr[i];
    }

    cout << "\nArray you entered: ";
    for (int i = 0; i < 5; i++) {
        cout << arr[i]<<" ";

    }

    sortarr(arr); 

    cout <<  "\nSorted array in asecding order is : " << endl;
    for (int i = 0; i < 5; i++) {
        cout << arr[i]<<" ";

    }

    return 0;
}