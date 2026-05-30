/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : duplicate_number.cpp
 * PROBLEM  : Duplicate Number
 * LEETCODE : 287 — Find the Duplicate Number
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Hash set or sorting to find duplicates.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <algorithm>
using namespace std;


/*
 * duplicate()
 * Purpose : Hash set or sorting to find duplicates.
 * Params  : int *arr, int& size
 * Returns : int
 */
int duplicate (int *arr, int& size) {
    sort(arr, arr+size); // this sln takes timecomplexity nlogn
    // Iterate over all elements
    for(int i=0; i<size-1; i++) {
        if(arr[i]== arr[i+1] ) {
            return arr[i];
        }
    }
    return -1;
}


/*
 * duplicate2()
 * Purpose : Hash set or sorting to find duplicates.
 * Params  : int *arr, int& size
 * Returns : int
 */
int duplicate2(int *arr, int& size) {
    
}


/*
 * main()
 * Purpose : Entry point — demo/test for Duplicate Number
 */
int main() {
    int arr[] = {1,2,4,4,3};
    int size = 5;
    int ans = duplicate(arr, size);
    cout<< ans<< endl;
}
