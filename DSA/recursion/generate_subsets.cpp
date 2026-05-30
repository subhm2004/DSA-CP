/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : generate_subsets.cpp
 * PROBLEM  : Generate Subsets
 * LEETCODE : 78 — Subsets
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Include/exclude each element — recursive branching.
 * COMPLEX  : Time: O(2^n)  |  Space: O(n)
 * ============================================================================
 */

#include <iostream>
#include <vector>
using namespace std;



/*
 * printvecofvec()
 * Purpose : Base case + solve smaller subproblem recursively.
 * Params  : vector<vector<int>>&brr, vector<int>&ans
 * Returns : void
 */
void printvecofvec(vector<vector<int>>&brr, vector<int>&ans) {
    // Iterate over all elements
    for(int i=0; i<brr.size(); i++) {
        // Iterate over all elements
        for(int j=0; j<brr[i].size(); j++) {
            cout<< brr[i][j]<< " ";
        }
    }
 }


/*
 * subsets()
 * Purpose : Include/exclude each element — recursive branching.
 * Params  : int arr[], int& size, int i, vector<int>ans, vector<vector<int>> brr
 * Returns : void
 */
void subsets(int arr[], int& size, int i, vector<int>ans, vector<vector<int>> brr) {
    if(i>=size) {
        // Iterate over all elements
        for(int j=0; j<ans.size(); j++) {
            brr.push_back(ans);
        }
    }
    subsets(arr, size, i+1, ans, brr);
    ans.push_back(arr[i]);
    subsets(arr, size, i+1, ans, brr);

}


/*
 * main()
 * Purpose : Entry point — demo/test for Generate Subsets
 */
int main() {
    int arr[] = {1,2,3};
    vector<vector<int>> brr;
    vector<int>ans;
    int size=3;
    int i=0;
    subsets(arr, size, i, ans, brr);
     // Iterate over all elements
     for(int i=0; i<brr.size(); i++) {
        // Iterate over all elements
        for(int j=0; j<brr[i].size(); j++) {
            cout<< brr[i][j]<< " ";
        }
     }
      
}
