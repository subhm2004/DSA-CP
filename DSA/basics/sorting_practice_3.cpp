/*
 * ============================================================================
 * TOPIC    : Basics
 * FILE     : sorting_practice_3.cpp
 * PROBLEM  : Sorting Practice 3
 * ABOUT    : Fundamental DSA — loops, sorting, strings, character operations
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;


/*
 * insertion()
 * Purpose : Standard DSA solution for this problem.
 * Params  : int arr[], int size
 * Returns : void
 */
void insertion(int arr[], int size) {
    // Iterate over all elements
    for(int i=1; i<size; i++) { // number of rounds
        int value = arr[i];
        int j= i-1;
        for(; j>=0; j--) {
            if(arr[j] > value) {
                arr[j+1] = arr[j];
            }
            else {
                break;
            }
            
           
        }
        arr[j+1]= value;
    }
}


/*
 * printarray()
 * Purpose : Standard DSA solution for this problem.
 * Params  : int arr[], int size
 * Returns : void
 */
void printarray(int arr[], int size) {
    // Iterate over all elements
    for(int i=0; i<size; i++) {
        cout<< arr[i]<< " ";
    }
}


/*
 * main()
 * Purpose : Entry point — demo/test for Sorting Practice 3
 */
int main() {
    int arr[] = {10,7,1,6,14,9};
    int size = 6;
    insertion(arr,size);
    printarray(arr,size);
}
