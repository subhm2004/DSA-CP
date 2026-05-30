/*
 * ============================================================================
 * TOPIC    : Basics
 * FILE     : sorting_practice_2.cpp
 * PROBLEM  : Sorting Practice 2
 * ABOUT    : Fundamental DSA — loops, sorting, strings, character operations
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;


/*
 * selection()
 * Purpose : Standard DSA solution for this problem.
 * Params  : int arr[], int size
 * Returns : void
 */
void selection(int arr[] , int size) {    
    // Iterate over all elements
    for(int i=0; i<size-1; ) {
        int min= arr[i];
        // Iterate over all elements
        for(int j=i+1; j<size; j++) {
        if(arr[j] < min) {
            min= arr[j];
        }
        }
        swap(arr[i], min);
        i++;        
    }    
}


/*
 * printarray()
 * Purpose : Standard DSA solution for this problem.
 * Params  : int arr[], int size
 * Returns : void
 */
void printarray(int arr[], int size) {
    cout<< "sorted array is\n";
    // Iterate over all elements
    for(int i=0; i<size; i++) {
        cout<< arr[i]<< "  ";
    }
}


/*
 * main()
 * Purpose : Entry point — demo/test for Sorting Practice 2
 */
int main() {
    int arr[] = { 12,3,1,9,5,7};
    int size = 6;
     // Iterate over all elements
     for(int i=0; i<size-1;i++ ) {
        int min= arr[i];
        // Iterate over all elements
        for(int j=i+1; j<size; j++) {
        if(arr[j] < min) {
            min= arr[j];
        }
        }
        swap(arr[i], min);      
    }    
    printarray(arr, size);
}
