/*
 * ============================================================================
 * TOPIC    : Basics
 * FILE     : selection_sort.cpp
 * PROBLEM  : Selection Sort
 * ABOUT    : Fundamental DSA — loops, sorting, strings, character operations
 * APPROACH : Select minimum from unsorted suffix each pass.
 * COMPLEX  : Time: O(n²)  |  Space: O(1)
 * ============================================================================
 */

#include <iostream>
using namespace std;



/*
 * printarray()
 * Purpose : Standard DSA solution for this problem.
 * Params  : int arr[], int size
 * Returns : void
 */
void printarray(int arr[], int size) {
    cout<< "array is \n";
    // Iterate over all elements
    for(int i=0; i<size; i++) {
        cout<< arr[i]<< " ";
    }
}


/*
 * selection()
 * Purpose : Standard DSA solution for this problem.
 * Params  : int arr[], int size
 * Returns : void
 */
void selection(int arr[],int size ) {
   
    // Iterate over all elements
    for(int i=0; i< size-1; i++) {
        int smallest = arr[i];
        // Iterate over all elements
        for(int j = i; j< size; j++) {
        if(arr[j] < smallest) {
            smallest = arr[j];
        }
      }
      swap(arr[i], smallest);
    } 
    cout<< "sorted array is\n"<< endl;
    // Iterate over all elements
    for(int i=0; i<size; i++) {
        cout<< arr[i]<< " ";
    }
}


/*
 * main()
 * Purpose : Entry point — demo/test for Selection Sort
 */
int main() {
    int arr[] = { 12,4,7,11,56,34,2};
    int size = 7;
    selection(arr,size);
    

}
