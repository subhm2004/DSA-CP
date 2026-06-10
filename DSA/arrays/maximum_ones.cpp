/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : maximum_ones.cpp
 * PROBLEM  : Maximum Ones
 * LEETCODE : 485 — Max Consecutive Ones
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Iterate with two pointers / sliding window / prefix sum.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <limits.h>
#include <vector>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// MAX ONES IN A ROW — 2D matrix me sabse zyada 1 wali row
// ────────────────────────────────────────────────────────────────────────────
// Funda: har row me 1 count karo, max count aur row index track karo
// ans vector me [count, row_index] push karo
// COMPLEX: Time O(m*n)  |  Space O(1) extra
// ════════════════════════════════════════════════════════════════════════════

// ── maximumones: row with max 1s dhundho ───────────────────────────────────
//   1) har row i pe inner loop se 1 count karo
//   2) count > onecount ho to row aur onecount update
//   3) ans me {onecount, row} push_back
void maximumones(int arr[][3], int&m , int& n, vector<int>&ans) {
    int onecount = INT_MIN;
    int row = -1;
    for(int i=0; i<m; i++) {
        int count = 0;
        for(int j=0; j<n; j++) {
            if(arr[i][j] ==1){
                count++;
            }
        }
        if(onecount< count) {
            row = i;
        }
        if(onecount < count){
            onecount = count;
        }    
    }
    ans.push_back(onecount);
    ans.push_back(row);
}


// ── main: 2D matrix me max-ones row print karo ─────────────────────────────
//   1) 4x3 matrix declare
//   2) maximumones() call
//   3) count aur row index print
int main() {
    int arr[][3] = {{1,0,0},{0,0,0}, {1,1,1}, {0,1,1}};
    int m= 4, n=3;
    vector<int>ans;
    
    maximumones(arr , m,n,ans);
    for(int i=0; i< ans.size(); i++) {
        cout<< ans[i]<< " ";
    }
}
