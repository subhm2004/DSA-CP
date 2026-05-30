/*
 * ============================================================================
 * TOPIC    : Vectors
 * FILE     : vector_practice_1.cpp
 * PROBLEM  : Vector Practice 1
 * ABOUT    : STL vector usage and applications
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;


/*
 * find()
 * Purpose : Standard DSA solution for this problem.
 * Params  : vector<int> arr
 * Returns : int
 */
int find(vector<int> arr) {
    int ans=0;
    // Iterate over all elements
    for(int i=0; i< arr.size(); i++) {
        ans = ans^ arr[i];
    }
    return ans;
}


/*
 * main()
 * Purpose : Entry point — demo/test for Vector Practice 1
 */
int main() {
    
   

    vector<int> crr{1,2,3,3,4,4};
    int sizecrr = 4;
    vector<int> drr{6,3,3,1,1,9,0};
    int sizedrr = 5;
    vector<int> ans;
    // Iterate over all elements
    for(int i=0; i< crr.size(); i++) {
        // Iterate over all elements
        for(int j=0; j< drr.size(); j++) {
            if(crr[i]== drr[j]) {
                
                ans.push_back(crr[i]); 
                crr[i] = INT_MIN;               
            }
        }
    }
    cout<< "intersection array is"<< endl;
    // Iterate over all elements
    for(int i=0; i<ans.size(); i++) {
        cout<< ans[i]<< " ";

    }





}
