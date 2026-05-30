/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : sort_negatives.cpp
 * PROBLEM  : Sort Negatives
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Iterate with two pointers / sliding window / prefix sum.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;


/*
 * sortnegative()
 * Purpose : Iterate with two pointers / sliding window / prefix sum.
 * Params  : int arr[], int& size, int& i, int& j
 * Returns : void
 */
void sortnegative(int arr[], int& size,int& i, int& j) {
    while(i<size) {
        if(arr[i]>= 0) {
            i++;
        }
        else {
            swap(arr[i], arr[j]);
            i++;
            j++;
        }
    }

}


/*
 * main()
 * Purpose : Entry point — demo/test for Sort Negatives
 */
int main() {
    int arr[] = {23,-7, 12, -10, -11, 40, 60};
    int size = 7;
    int i=0, j=0;
    sortnegative(arr, size, i, j);

    // Iterate over all elements
    for(int i=0; i< size; i++) {
        cout<< arr[i] << "  ";
    }
}
