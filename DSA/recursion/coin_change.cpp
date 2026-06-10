/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : coin_change.cpp
 * PROBLEM  : Coin Change
 * LEETCODE : 322 — Coin Change
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Try each coin recursively; return min coins (unbounded knapsack).
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <limits.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// COIN CHANGE (Recursion) — Minimum coins se target banavo
// ────────────────────────────────────────────────────────────────────────────
// Har coin try karo — target-arr[i] ke liye recurse
// Base: target==0 -> 0 coins; target<0 -> invalid (INT_MAX)
// Min over all coins + 1 — unbounded (same coin dobara use)
// ════════════════════════════════════════════════════════════════════════════

// ── minimumcoins: target banane ke minimum coins ──────────────────────────────
//   1) target==0 -> 0 coins chahiye
//   2) target<0 -> invalid, INT_MAX return
//   3) har coin pe recurse — mini = min(mini, 1 + mincoins(target-coin))
//   4) saare coins try karke minimum return
int minimumcoins(int *arr, int& size, int target){
    if(target==0){
        return 0;  // exact ban gaya — koi coin nahi chahiye
    }
    if(target<0){  //target mhi bn skta aur out of bound chla gya
        return INT_MAX;
    }
    int mini = INT_MAX;

    for(int i=0; i<size; i++){
        int ans= minimumcoins(arr,size,target-arr[i]);  // coin arr[i] use kiya
         cout<< "ans is:" << ans<< endl;
         if(ans!= INT_MAX){
         mini = min(mini, ans+1);  // +1 current coin ke liye
         cout<< "mini is:"<< mini<< endl;
    }
 }
    return mini;     
}

// ── main: coins {1,2,3}, target 5 ────────────────────────────────────────────
int main() {
    int arr[] = {1,2,3};
    int size= 3;
    int target =5;
    int f= minimumcoins(arr,size,target);
    cout<< f<< endl;
   
}
