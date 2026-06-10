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

// ════════════════════════════════════════════════════════════════════════════
// MAXIMUM SUM SUBSET — Non-adjacent elements ka max sum
// ────────────────────────────────────────────────────────────────────────────
// Index i pe: include arr[i] (i+2) ya exclude (i+1)
// Har leaf pe maxi update — saare paths explore
// Similar to house robber pattern — adjacent nahi le sakte
// ════════════════════════════════════════════════════════════════════════════

// ── maximumsum: non-adjacent max sum explore ────────────────────────────────
//   1) i>=size -> maxi update with current sum, return
//   2) include — i+2 pe jao, sum+arr[i]
//   3) exclude — i+1 pe jao, sum same
void maximumsum(vector<int>&arr, int i, int& maxi, int sum) {
    if(i>= arr.size()) {
       maxi= max(maxi, sum);  // ek valid subset ka sum
       return;
    } 
       
    maximumsum(arr, i+2, maxi, sum+ arr[i]);  // include arr[i]
    maximumsum(arr, i+1, maxi, sum);          // exclude arr[i]
          
}

// ── main: maximum non-adjacent sum print ────────────────────────────────────
int main() {
    vector<int>arr = {2,1,4,9};
    int i=0, sum =0;
    int maxi= INT_MIN;
    maximumsum(arr, i, maxi, sum);
    cout<< "maximum sum is "<< maxi << endl;
}
