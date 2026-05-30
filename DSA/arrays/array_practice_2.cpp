/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : array_practice_2.cpp
 * PROBLEM  : Array Practice 2
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Iterate with two pointers / sliding window / prefix sum.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <vector>
using namespace std;


/*
 * unique()
 * Purpose : Iterate with two pointers / sliding window / prefix sum.
 * Params  : vector<int>arr
 * Returns : int
 */
int unique(vector<int>arr) {
    int ans=0;
    // Iterate over all elements
    for(int i=0; i< arr.size(); i++) {
        ans = ans^arr[i];

    }
    return ans;
}



/*
 * main()
 * Purpose : Entry point — demo/test for Array Practice 2
 */
int main() {
   
    
    
    int arr[]  = {1,2,3,4,5};
    int sizearr = 5;
    int brr[] = { 2,5,6,7};
    int sizebrr = 4;
    
    // Iterate over all elements
    for(int i=0; i< sizearr ; i++) {
        // Iterate over all elements
        for(int j=0; j< sizebrr; j++) {
            if(arr[i]== brr[j]) {
                cout<< arr[i] << " ";

            }
        }
    }

}
