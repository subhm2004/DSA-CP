/*
 * ============================================================================
 * TOPIC    : Math
 * FILE     : math_practice.cpp
 * PROBLEM  : Math Practice
 * ABOUT    : Number theory — GCD, primes, sieve, fast exponentiation
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;


/*
 * sortarray()
 * Purpose : Standard DSA solution for this problem.
 * Params  : int *arr, int size
 * Returns : void
 */
void sortarray(int *arr, int size) {
    int j=0;
    // Iterate over all elements
    for(int i=0; i<size; i++) {
        if(arr[i] < 0) {
            swap(arr[i],arr[j] );
            j++;
        }
    }
}


/*
 * sortcolor()
 * Purpose : Standard DSA solution for this problem.
 * Params  : int arr[], int size
 * Returns : void
 */
void sortcolor(int arr[], int size) {
    int j=0, k= size-1;
    int i=0;
    while(i <= k) {
        if(arr[i] == 0) {
            swap(arr[i], arr[j]);
            j++;
            i++;
        }
        else if(arr[i] == 2) {
            swap(arr[i], arr[k]);
            k--;
        }
        else {
            i++;
        }
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
 * Purpose : Entry point — demo/test for Math Practice
 */
int main() {
    int arr[] = {1,0,2,2,1,0,1,0,2};
    int size = 9;
    sortcolor(arr,size);
    printarray(arr,size);
}
