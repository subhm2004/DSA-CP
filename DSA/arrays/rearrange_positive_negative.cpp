/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : rearrange_positive_negative.cpp
 * PROBLEM  : Rearrange Positive Negative
 * LEETCODE : 905 — Sort Array By Parity
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Iterate with two pointers / sliding window / prefix sum.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;


/*
 * rearrangearray()
 * Purpose : Iterate with two pointers / sliding window / prefix sum.
 * Params  : int arr[], int size, int i
 * Returns : void
 */
void rearrangearray(int arr[], int size, int i){
    // Iterate over all elements
    for(i=0; i< size; i= i+2) {
        if(arr[i] < 0){
            // Iterate over all elements
            for(int j= i+1; j<size; j++) {
                if(arr[j]> 0){
                    arr[i]= arr[j];
                    break;
                }
            }
        }       
    }
}


/*
 * main()
 * Purpose : Entry point — demo/test for Rearrange Positive Negative
 */
int main() {
    int arr[] = {-5,-3,2,1,-1,0,9,-8};
    int size =8;
    int i=0;
    rearrangearray(arr, size, i);
}
