/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : array_practice_1.cpp
 * PROBLEM  : Array Practice 1
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Iterate with two pointers / sliding window / prefix sum.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>

using namespace std;


/*
 * main()
 * Purpose : Entry point — demo/test for Array Practice 1
 */
int main(){
    int arr[] = { 1,2,4,5,6,7,8,9,10};
    int size = 9;
    int largest = arr[0];
    
    // Iterate over all elements
    for(int i=0; i<size; i++) {
        if(arr[i] > largest ) {
            largest = arr[i];
        }

    }
    cout<< "largest element of array is  "<< largest<< endl;
    
    return 0;
}
