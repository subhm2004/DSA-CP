/*
 * ============================================================================
 * TOPIC    : Basics
 * FILE     : odd_occurrence.cpp
 * PROBLEM  : Odd Occurrence
 * ABOUT    : Fundamental DSA — loops, sorting, strings, character operations
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <vector>
using namespace std;



/*
 * solve()
 * Purpose : Standard DSA solution for this problem.
 * Params  : vector<int>arr
 * Returns : int
 */
int solve(vector<int>arr) {
    int s=0;
    int e= arr.size() - 1;
    int mid= s+ (e-s)/2;
    while(s<=e) {
        if(s==e) {
            return s;
        }
        if(mid %2==0) {
            if(arr[mid] == arr[mid +1]) {
                s = mid+2;
            }
            else {
                e=mid;
            }
        }
        else {
            if(arr[mid] == arr[mid-1]) {
                s= mid+1;
            }
            else {
                e= mid-1;
            }
        }
        mid = s+ (e-s)/2;
    }
    return -1;
}


/*
 * main()
 * Purpose : Entry point — demo/test for Odd Occurrence
 */
int main() {
    vector<int> arr= {1,1,2,2,3,3,4,4,3,6,6,4,4};
    int ans= solve(arr);
    cout<< "index of required element is "<< ans<< endl;
    cout<< "value of element is "<< arr[ans]<< endl;
    return 0;
}
