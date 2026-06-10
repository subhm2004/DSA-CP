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

// ════════════════════════════════════════════════════════════════════════════
// PIVOT INDEX — left sum == right sum wala index
// ────────────────────────────────────────────────────────────────────────────
// Funda: total sum nikalo, har index pe right = total - left - arr[i]
// left == right ho to wahi pivot index
// COMPLEX: Time O(n)  |  Space O(1)
// ════════════════════════════════════════════════════════════════════════════

// ── pivot: index jahan left sum == right sum ───────────────────────────────
//   1) pehle poora sum calculate karo
//   2) har i pe: right = sum - arr[i], left accumulate karo
//   3) left == right ho to i return — pivot mil gaya
//   4) koi nahi mila to -1
int pivot(int arr[], int size) {
   int sum =0;
   int left =0;
   cout<< "left is "<< left<< endl;
   for(int i=0; i< size; i++) {
      sum = sum + arr[i];
   }
   cout<< sum<< endl;

      for(int i=0; i< size; i++) {
         sum = sum - arr[i];  // right side ka sum (current element ke baad)
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


// ── main: pivot index demo ─────────────────────────────────────────────────
//   1) sample array with pivot at index 5
//   2) pivot() call — index print
int main() {
    int arr[] = {-1,-1,-1,-1,-1,0};
    int size = 6;
         int ans = pivot(arr, size);
         cout<< ans;
 }
