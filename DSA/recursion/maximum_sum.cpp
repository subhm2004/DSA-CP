/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : maximum_sum.cpp
 * PROBLEM  : Maximum Sum
 * LEETCODE : 53 — Maximum Subarray
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Base case + solve smaller subproblem recursively.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <climits>
using namespace std;


/*
 * maximumsum()
 * Purpose : Base case + solve smaller subproblem recursively.
 * Params  : vector<int>&arr, int i, int& maxi, int sum
 * Returns : void
 */
void maximumsum(vector<int>&arr, int i, int& maxi, int sum) {
    if(i>= arr.size()) {
       maxi= max(maxi, sum); 
       return;
    } 
       
    maximumsum(arr, i+2, maxi, sum+ arr[i]); 
    maximumsum(arr, i+1, maxi, sum);
          
}



/*
 * main()
 * Purpose : Entry point — demo/test for Maximum Sum
 */
int main() {
    vector<int>arr = {2,1,4,9};
    int i=0, sum =0;
    int maxi= INT_MIN;
    maximumsum(arr, i, maxi, sum);
    cout<< "maximum sum is "<< maxi << endl;
}
