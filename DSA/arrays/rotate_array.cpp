/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : rotate_array.cpp
 * PROBLEM  : Rotate Array
 * LEETCODE : 189 — Rotate Array
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Rotate/transpose matrix in-place or with extra space.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <vector>
using namespace std;


/*
 * rotatearray()
 * Purpose : Rotate/transpose matrix in-place or with extra space.
 * Params  : int arr[], int& size, int& k, vector<int>&ans
 * Returns : void
 */
void rotatearray(int arr[], int& size, int& k, vector<int>&ans ) {
    // Iterate over all elements
    for(int i=0; i<size; i++) {
      ans[(i+k)%size] = arr[i];  
    }
}


/*
 * printarray()
 * Purpose : Iterate with two pointers / sliding window / prefix sum.
 * Params  : vector<int>& ans
 * Returns : void
 */
void printarray(vector<int>& ans) {
    // Iterate over all elements
    for(int i=0; i<ans.size(); i++) {
        cout<< ans[i]<< " ";
    }
}


/*
 * main()
 * Purpose : Entry point — demo/test for Rotate Array
 */
int main() {
    int arr[] = {10,20,30,40,50,60,70,80};
    int k, size = 8;
    cout<< " enter number of times to rotate "<< endl;
    cin >> k;
    vector<int>ans(size);
    rotatearray(arr, size, k, ans);
    printarray(ans);

}
