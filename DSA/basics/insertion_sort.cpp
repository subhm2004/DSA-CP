/*
 * ============================================================================
 * TOPIC    : Basics
 * FILE     : insertion_sort.cpp
 * PROBLEM  : Insertion Sort
 * ABOUT    : Fundamental DSA — loops, sorting, strings, character operations
 * APPROACH : Insert each element into sorted prefix.
 * COMPLEX  : Time: O(n²)  |  Space: O(1)
 * ============================================================================
 */

#include <iostream>
using namespace std;


/*
 * insertionsort()
 * Purpose : Standard DSA solution for this problem.
 * Params  : int arr[], int size
 * Returns : void
 */
void insertionsort(int arr[], int size) {
    // Iterate over all elements
    for(int i=1; i<size; i++) { 
        int value=i;  // loop for fetching number of elements
       int j= i-1;
       for(; j>=0; j--) {
        if(arr[value]< arr[j]) {
           arr[j+1]= arr[j];
        }
       }
       arr[j+1]= arr[value];
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
 * Purpose : Entry point — demo/test for Insertion Sort
 */
int main() {
    int arr[] = {10,7,1,6,14,9};
    int size = 6;
    insertionsort(arr,size);
    printarray(arr,size);


}
