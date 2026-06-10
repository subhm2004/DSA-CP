/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : check_sorted_array.cpp
 * PROBLEM  : Check Sorted Array
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Base case + solve smaller subproblem recursively.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// CHECK SORTED ARRAY — Adjacent pairs compare karo
// ────────────────────────────────────────────────────────────────────────────
// arr[i] < arr[i+1] -> aage check karo (i+1)
// arr[i] >= arr[i+1] -> sorted nahi, false
// Base: i==size-1 -> true (last element tak sab theek)
// ════════════════════════════════════════════════════════════════════════════

// ── sortedarray: array ascending sorted hai? ──────────────────────────────────
//   1) i==size-1 -> base case, return true
//   2) arr[i]<arr[i+1] -> next pair check karo
//   3) warna return false — order break hua
bool sortedarray(int arr[], int size, int i) {
    if(i == size-1) {
        return true;  // last index — sab theek
    }    
    if(arr[i]< arr[i+1]) {
        sortedarray(arr,size, i+1);  // agla pair check    
    }
    else {
        return false;  // descending ya equal — sorted nahi
    } 
}

// ── main: sorted check demo ─────────────────────────────────────────────────
int main() {
    int arr[] = {12, 34,45,57,677,78};
    int size = 6;
    int i=0;
    int ans = sortedarray(arr, size, i);
    cout<< ans<< endl;
}
