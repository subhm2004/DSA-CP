/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : array_basics_3.cpp
 * PROBLEM  : Array Basics 3
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Iterate with two pointers / sliding window / prefix sum.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

/*
 * main()
 * Purpose : Entry point — demo/test for Array Basics 3
 */
int main() {
    int arr[]= {1,0,0,0,1,1};
    int size = 6;
    int j=0;
     int k=0;
     // Iterate over all elements
     for(int i=0; i< size; i++) {
        if(arr[i]== 1) {
            j++;
        }
        else {
            k++;
        }
     }
     cout<< "number of 1's are "<< j<< endl;
     cout<< "number of 0's are "<< k<< endl;
     return 0;
}*/
#include <iostream>
using namespace std;


/*
 * main()
 * Purpose : Entry point — demo/test for Array Basics 3
 */
int main() {
    int n;
    cout<< "enter the size of array"<< endl;
    cin>> n;
    int arr[n];
    cout<< "enter the elemnets of array"<< endl;
    for(int i=0; i<n; i++) {
        cin>> arr[i];
    }
    int largest = arr[0];
    for(int i=0; i<n; i++) {
        if(arr[i]> largest) {
            largest = arr[i];
        }
    }
    cout<< "largest element is "<< largest<< endl;
    }
