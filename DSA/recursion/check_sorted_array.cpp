/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : check_sorted_array.cpp
 * PROBLEM  : Check Sorted Array
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Base case + solve smaller subproblem recursively.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;


/*
 * sortedarray()
 * Purpose : Base case + solve smaller subproblem recursively.
 * Params  : int arr[], int size, int i
 * Returns : bool
 */
bool sortedarray(int arr[], int size, int i) {
    if(i == size-1) {
        return true;
    }    
    if(arr[i]< arr[i+1]) {
        sortedarray(arr,size, i+1);    
    }
    else {
        return false;
    } 
}


/*
 * main()
 * Purpose : Entry point — demo/test for Check Sorted Array
 */
int main() {
    int arr[] = {12, 34,45,57,677,78};
    int size = 6;
    int i=0;
    int ans = sortedarray(arr, size, i);
    cout<< ans<< endl;
}
