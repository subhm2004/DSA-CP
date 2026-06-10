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

// ════════════════════════════════════════════════════════════════════════════
// GENERATE SUBSETS — Har element include/exclude karo
// ────────────────────────────────────────────────────────────────────────────
// Index i pe: exclude (i+1, same ans) ya include (ans me push, i+1)
// 2^n subsets — recursive tree with two branches
// Base: i>=size -> subset store/print
// ════════════════════════════════════════════════════════════════════════════

// ── printvecofvec: 2D vector print helper ─────────────────────────────────────
//   1) outer loop — har subset
//   2) inner loop — subset ke elements
void printvecofvec(vector<vector<int>>&brr, vector<int>&ans) {
    for(int i=0; i<brr.size(); i++) {
        for(int j=0; j<brr[i].size(); j++) {
            cout<< brr[i][j]<< " ";
        }
    }
 }

// ── subsets: recursive subset generation ──────────────────────────────────────
//   1) i>=size -> base, ans ko brr me push
//   2) exclude branch — element mat lo, i+1
//   3) include branch — arr[i] ans me, i+1
//   4) 2^n total subsets
void subsets(int arr[], int& size, int i, vector<int>ans, vector<vector<int>> brr) {
    if(i>=size) {
        for(int j=0; j<ans.size(); j++) {
            brr.push_back(ans);  // current subset store
        }
    }
    subsets(arr, size, i+1, ans, brr);  // exclude arr[i]
    ans.push_back(arr[i]);
    subsets(arr, size, i+1, ans, brr);  // include arr[i]

}

// ── main: subset generation demo ────────────────────────────────────────────
int main() {
    int arr[] = {1,2,3};
    vector<vector<int>> brr;
    vector<int>ans;
    int size=3;
    int i=0;
    subsets(arr, size, i, ans, brr);
     for(int i=0; i<brr.size(); i++) {
        for(int j=0; j<brr[i].size(); j++) {
            cout<< brr[i][j]<< " ";
        }
     }
      
}
