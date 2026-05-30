/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : shift_one.cpp
 * PROBLEM  : Shift One
 * LEETCODE : 189 — Rotate Array
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Iterate with two pointers / sliding window / prefix sum.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;



/*
 * shiftone()
 * Purpose : Iterate with two pointers / sliding window / prefix sum.
 * Params  : int arr[], int size
 * Returns : void
 */
void shiftone(int arr[], int size) {
    int temp1 = arr[size-1];
    // Iterate over all elements
    for(int j= size-1; j>=0; j--) {
        arr[j] = arr[j-1];
    }
    arr[0] = temp1;
}


/*
 * shifttwo()
 * Purpose : Iterate with two pointers / sliding window / prefix sum.
 * Params  : int arr[], int size
 * Returns : void
 */
void shifttwo(int arr[], int size) {
    int a = arr[size-1];
    int b = arr[size-2];
    
}


/*
 * printarray()
 * Purpose : Iterate with two pointers / sliding window / prefix sum.
 * Params  : int arr[], int size
 * Returns : void
 */
void printarray(int arr[] ,int size) {
    // Iterate over all elements
    for(int i=0; i<size; i++) {
        cout<< arr[i]<< " ";
    }

}


/*
 * main()
 * Purpose : Entry point — demo/test for Shift One
 */
int main() {
    int arr[] = { 10,20,30,40,50,60};
    int size = 6;
    shiftone(arr, size);
    printarray(arr,size);
    return 0;
}
