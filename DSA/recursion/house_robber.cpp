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


/*
 * rob()
 * Purpose : DP: max(rob+dp[i-2], skip+dp[i-1]).
 * Params  : int arr[], int& size, int index
 * Returns : int
 */
int rob(int arr[], int& size, int index){
    if(index >= size){
        return 0;
    }
   int ans= 0+ rob(arr,size,index+1);

   int ans2= arr[index] + rob(arr,size,index+2);
   return max(ans,ans2);
}


/*
 * main()
 * Purpose : Entry point — demo/test for House Robber
 */
int main(){
    int arr[]= {1,2,3,1};
    int size= 4;
    int index=0;
    cout<< "maximum amount is: "<< rob(arr,size,index)<< endl; 

}
