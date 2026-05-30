/*
 * ============================================================================
 * TOPIC    : Vectors
 * FILE     : unique_elements_vector.cpp
 * PROBLEM  : Unique Elements Vector
 * ABOUT    : STL vector usage and applications
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <vector>
using namespace std;


/*
 * find()
 * Purpose : Standard DSA solution for this problem.
 * Params  : vector<int>arr
 * Returns : int
 */
int find(vector<int>arr) {
    int ans=0;
    // Iterate over all elements
    for(int i=0; i< arr.size(); i++) {
    ans= ans^arr[i];
    }
    return ans;
}


/*
 * main()
 * Purpose : Entry point — demo/test for Unique Elements Vector
 */
int main() {
    
    int n;
    cout<< "enter number of elements"<< endl;
    cin>> n;
    vector<int> arr(n);
    cout<< "enter the elements in array"<< endl;
    // Iterate over all elements
    for(int i=0; i<arr.size(); i++) {
        cin>> arr[i];

    }
    int unique= find(arr);
    cout<< "unique element is "<< unique<< endl;
    return 0;

}
