/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : linear_search.cpp
 * PROBLEM  : Linear Search
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Iterate with two pointers / sliding window / prefix sum.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;


/*
 * main()
 * Purpose : Entry point — demo/test for Linear Search
 */
int main() {
    int n;
    cout<< "enter number of elements in array"<< endl;
    cin>> n;
    int arr[n];
    cout<< "enter the elements of array"<< endl;
    for(int i=0; i<n; i++) {
        cin>> arr[i];
    }
    int search;
    cout<< "enter the element to search"<< endl;
    cin>> search;
    
   int flag=0;
    for(int i=0; i<n; i++) {
        if(arr[i]== search) {
            flag =1;
            cout<< "element is found at position"<< i<< endl;
            break;
        }

    }
    if(flag ==0) {
        cout<< "element not found"<< endl;

    }
    
}
