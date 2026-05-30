/*
 * ============================================================================
 * TOPIC    : Binary Search
 * FILE     : missing_element.cpp
 * PROBLEM  : Missing Element
 * LEETCODE : 268 — Missing Number
 * ABOUT    : Binary search templates and classic interview problems
 * APPROACH : Binary search on sorted array or on answer.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;


/*
 * missingelement()
 * Purpose : Binary search on sorted array or on answer.
 * Params  : int *arr, int& size
 * Returns : int
 */
int missingelement(int *arr, int& size){
    int s=0, e= size-1;
    int mid= s+(e-s)/2;
    while(s<=e){
        if(arr[mid]== mid+1){
            if(s==e){
                return arr[mid]+1 ;
            }
            s= mid+1;
        }
        else {
            if(s==e){
                return arr[mid]-1 ;
            }
            e= mid-1;
        }
        mid= s/2 + e/2;
    }
}



/*
 * main()
 * Purpose : Entry point — demo/test for Missing Element
 */
int main() {
    int arr[] = {1,2,3,4,5,6,7,9};
    int size = 8;
    int ans= missingelement(arr, size);
    cout<< ans<< endl;
}
