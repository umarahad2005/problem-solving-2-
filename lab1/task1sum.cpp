#include <iostream>
using namespace std;


void sumarray(int array[5]) {
   int sum = 0;
   for (int i=0 ; i<5 ; i++)
   {
    sum += array[i];
   }
   cout << " \n sum of the array is : "<< sum << endl;

}
int main() {
    int arr[5];
    cout << "welcome to the world of problem solving 2 by umar usmani sap : 60199 "<< endl;


    cout << "kindly enter the  5 element in the array " << endl;
    for (int i = 0; i < 5; i++) 
    {
        cout << "Element " << (i + 1) << ": ";
        cin >> arr[i];
    }

    cout << "\nArray you entered: ";
    for (int i = 0; i < 5; i++) {
        cout << arr[i]<<" ";

    }

    sumarray(arr);
    return 0;
}