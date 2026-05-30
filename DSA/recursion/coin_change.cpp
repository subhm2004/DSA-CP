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


/*
 * minimumcoins()
 * Purpose : Base case + solve smaller subproblem recursively.
 * Params  : int *arr, int& size, int target
 * Returns : int
 */
int minimumcoins(int *arr, int& size, int target){
    // Base case: target reached — 0 coins needed
    if(target==0){
        return 0;
    }
    // Invalid: target went negative — return INF
    if(target<0){  //target mhi bn skta aur out of bound chla gya
        return INT_MAX;
    }
    int mini = INT_MAX;

    // Iterate over all elements
    for(int i=0; i<size; i++){
        // Recurse: use coin arr[i], solve for (target - arr[i])
        int ans= minimumcoins(arr,size,target-arr[i]);
         cout<< "ans is:" << ans<< endl;
         if(ans!= INT_MAX){
         mini = min(mini, ans+1);
         cout<< "mini is:"<< mini<< endl;
    }
 }
    return mini;     
}


/*
 * main()
 * Purpose : Entry point — demo/test for Coin Change
 */
int main() {
    int arr[] = {1,2,3};
    int size= 3;
    int target =5;
    int f= minimumcoins(arr,size,target);
    cout<< f<< endl;
   
}
