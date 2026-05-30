/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : array_basics_4.cpp
 * PROBLEM  : Array Basics 4
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Iterate with two pointers / sliding window / prefix sum.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;


/*
 * main()
 * Purpose : Entry point — demo/test for Array Basics 4
 */
int main() {
    int arr[] = { 1,3,3,4,4,5,5,6};
    int sizearr = 8;
    int brr[] = {3, 3,5,5,8, 9};
    int sizebrr = 4;
    // Iterate over all elements
    for(int i=0; i< sizearr; i++) {
        // Iterate over all elements
        for(int j=0; j< sizebrr; j++) {
            if(arr[i] == brr[j]) {
                cout<< arr[i] << " ";
            }
        }
    }
}
