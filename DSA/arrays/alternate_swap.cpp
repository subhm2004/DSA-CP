/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : alternate_swap.cpp
 * PROBLEM  : Alternate Swap
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Iterate with two pointers / sliding window / prefix sum.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;


/*
 * printarray()
 * Purpose : Iterate with two pointers / sliding window / prefix sum.
 * Params  : int arr[], int size
 * Returns : void
 */
void printarray(int arr[], int size) {
    // Iterate over all elements
    for(int i=0; i<size; i++) {
        cout<< arr[i] << " ";
    }

}



/*
 * alterswap()
 * Purpose : Iterate with two pointers / sliding window / prefix sum.
 * Params  : int arr[], int size
 * Returns : void
 */
void alterswap(int arr[], int size) {
    // Iterate over all elements
    for(int i=0; i<=size-1; i=i+2) {
        if(arr[i] == arr[size-1]) {
                cout<< arr[i]<< " ";
            }
        else {
            int j= i+1; 
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            cout<< arr[i] << " "<< arr[j] << " "; 
        }         
        }
    }


/*
 * main()
 * Purpose : Entry point — demo/test for Alternate Swap
 */
int main() {
    int arr[] = {1,2,3,5,6,7,8 ,9};
    int size = 8;
    cout<< "elements of array are"<< endl;
    printarray(arr, size);
    cout<< endl;
    cout<< "array after swapping are"<< endl;
    alterswap(arr, size);
    cout<< endl;
    return 0;
}
