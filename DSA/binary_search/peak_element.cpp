/*
 * ============================================================================
 * TOPIC    : Binary Search
 * FILE     : peak_element.cpp
 * PROBLEM  : Peak Element
 * LEETCODE : 162 — Find Peak Element
 * ABOUT    : Binary search templates and classic interview problems
 * APPROACH : Binary search on sorted array or on answer.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;


/*
 * peakelement()
 * Purpose : Binary search on sorted array or on answer.
 * Params  : int *arr, int& size
 * Returns : int
 */
int peakelement(int *arr, int& size) {
    int s=0, e= size-1;
    int mid = s+(e-s)/2;
    int ans=-1;
    while(s<e) {
        if(arr[mid] < arr[mid+1]) {
            s= mid+1;
        }
        else if(arr[mid]> arr[mid+1]) {
            ans= mid;
            e= mid;
        }
        mid= s+(e-s)/2;    
    }
    return ans;
}


/*
 * main()
 * Purpose : Entry point — demo/test for Peak Element
 */
int main() {
    int arr[] = {5,10,15,11,9,8,7,6,5};
    int size= 9;
    int ans = peakelement(arr, size);
    cout<< ans<< endl;

}
