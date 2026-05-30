/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : array_basics_2.cpp
 * PROBLEM  : Array Basics 2
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Iterate with two pointers / sliding window / prefix sum.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;


/*
 * search()
 * Purpose : Iterate with two pointers / sliding window / prefix sum.
 * Params  : int arr[], int size, int key
 * Returns : bool
 */
bool search(int arr[], int size,int key) {
    // Iterate over all elements
    for(int i=0; i<size; i++) {
        if(arr[i]== key) {
            return true;
        }

    }
    return false;

}


/*
 * main()
 * Purpose : Entry point — demo/test for Array Basics 2
 */
int main() {
    int arr[] = {2,0,5,1,7} ;
    int size = 5;
    int key;
    cout<< "enter the element to find"<< endl;
    cin>> key;
    bool ans = search(arr, size, key);
    if(ans == true) {
        cout<< "element found"<< endl;
    }
    else {
        cout<< "not found"<< endl;
    }
    return 0;


}
