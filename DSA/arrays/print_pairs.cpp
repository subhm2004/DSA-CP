/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : print_pairs.cpp
 * PROBLEM  : Print Pairs
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Iterate with two pointers / sliding window / prefix sum.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;



/*
 * main()
 * Purpose : Entry point — demo/test for Print Pairs
 */
int main() {
    int arr[] = {10,20,30};
    int size =3;
    cout<< "pairs of the array are"<< endl;
    // Iterate over all elements
    for(int i=0; i<size; i++) {
        // Iterate over all elements
        for(int j=0; j<size; j++) {
            cout<< arr[i]<< ","<< arr[j]<< endl;
        }
    }
}
