/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : pivot_index.cpp
 * PROBLEM  : Pivot Index
 * LEETCODE : 724 — Find Pivot Index
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Iterate with two pointers / sliding window / prefix sum.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;


/*
 * pivot()
 * Purpose : Iterate with two pointers / sliding window / prefix sum.
 * Params  : int arr[], int size
 * Returns : int
 */
int pivot(int arr[], int size) {
   int sum =0;
   int left =0;
   cout<< "left is "<< left<< endl;
   // Iterate over all elements
   for(int i=0; i< size; i++) {
      sum = sum + arr[i];
   }
   cout<< sum<< endl;

      // Iterate over all elements
      for(int i=0; i< size; i++) {
         sum = sum - arr[i];
         cout<< "updated sum is "<<sum<< endl;
         if(i>0) {
         left = left + arr[i-1];
         cout<< " updated leftsum is "<< left<< endl;
         }
      if(left == sum) {
         return i;
         break;
      }
   }
   return -1;
}


/*
 * main()
 * Purpose : Entry point — demo/test for Pivot Index
 */
int main() {
    int arr[] = {-1,-1,-1,-1,-1,0};
    int size = 6;
         int ans = pivot(arr, size);
         cout<< ans;
 }
