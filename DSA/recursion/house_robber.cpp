/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : house_robber.cpp
 * PROBLEM  : House Robber
 * LEETCODE : 198 — House Robber
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : DP: max(rob+dp[i-2], skip+dp[i-1]).
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// HOUSE ROBBER (Recursion) — Adjacent houses rob nahi kar sakte
// ────────────────────────────────────────────────────────────────────────────
// Index i pe: skip (i+1) ya rob arr[i] + recurse(i+2)
// Max of dono branches — classic DP recurrence
// Base: index>=size -> 0 (koi house nahi)
// ════════════════════════════════════════════════════════════════════════════

// ── rob: index se maximum loot ──────────────────────────────────────────────
//   1) index>=size -> 0 return
//   2) skip branch — 0 + rob(index+1)
//   3) rob branch — arr[index] + rob(index+2)
//   4) max(skip, rob) return
int rob(int arr[], int& size, int index){
    if(index >= size){
        return 0;  // koi house baaki nahi
    }
   int ans= 0+ rob(arr,size,index+1);  // skip current house

   int ans2= arr[index] + rob(arr,size,index+2);  // rob current, skip next
   return max(ans,ans2);
}

// ── main: maximum robbery amount ────────────────────────────────────────────
int main(){
    int arr[]= {1,2,3,1};
    int size= 4;
    int index=0;
    cout<< "maximum amount is: "<< rob(arr,size,index)<< endl; 

}
