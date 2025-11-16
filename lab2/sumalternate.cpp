#include <iostream>
using namespace std;


void sumcheck(int array[5] , int sum1 )
{
    int sum = 0 ;
    for ( int i =0 ; i<5 ; i++)
    {
        sum = array[i] + array[i+1] ;
     if ( sum1 == sum )
    {
        cout << " the alter  number which made sum is  "<< array[i] << "  and "<< array[i+1]<< endl; 
    }
    cout<< " their is no alter number that made the sum "<< endl;
   
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
    cout << " enter the number that you want to check for sum :";
    int sum2 ;
    cin>>sum2;


    sumcheck (arr , sum2 );
    return 0;
}