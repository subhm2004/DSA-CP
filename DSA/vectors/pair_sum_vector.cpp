/*
 * ============================================================================
 * TOPIC    : Vectors
 * FILE     : pair_sum_vector.cpp
 * PROBLEM  : Pair Sum Vector
 * ABOUT    : STL vector usage and applications
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <vector>
using namespace std;


/*
 * main()
 * Purpose : Entry point — demo/test for Pair Sum Vector
 */
int main() {
    int n;
    cout<< "enter size of array"<< endl;
    cin>> n;
    vector<int> arr(n);
    cout<< "enter the elements of dynamic array"<< endl;
    // Iterate over all elements
    for(int i=0; i< arr.size(); i++) {
        cin>> arr[i];
    }
    int sum =9;
    for(int i=0; i<n-1; i++) {
        for(int j= i+1; j<n; j++) {
            if(arr[i] + arr[j] == sum) {
                cout<< "pair with sum 9 is " << arr[i]<< " "<< arr[j]<< endl;
            }

        }
    }
   
}
