/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : binary_search_recursion.cpp
 * PROBLEM  : Binary Search Recursion
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Binary search — eliminate half the search space each step.
 * COMPLEX  : Time: O(log n)  |  Space: O(1)
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// BINARY SEARCH (Recursion) — Sorted array me target
// ────────────────────────────────────────────────────────────────────────────
// Range [i, j] — mid nikalo, half eliminate karo
// arr[mid] > target -> left half; arr[mid] < target -> right half
// Base: i>j -> -1 (not found)
// ════════════════════════════════════════════════════════════════════════════

// ── binarysearch: recursive BS on sorted array ──────────────────────────────
//   1) i>j -> target nahi mila, return -1
//   2) mid = i + (j-i)/2 — overflow safe
//   3) arr[mid]==target -> return mid+1 (1-indexed answer)
//   4) arr[mid]>target -> left half; arr[mid]<target -> right half
int binarysearch(int arr[], int& size, int i, int j, int& target) {
    if(i>j) {
        return -1;  // search space khatam
    }
    int mid = i + (j-i)/2;
    if(arr[mid] == target) {
        return mid+1;
    }
    if(arr[mid] > target) {
        return binarysearch(arr , size, i, mid-1,target );  // left half
    }
    if(arr[mid] < target) {
        return binarysearch(arr, size, mid+1, j, target);  // right half
    }
}

// ── main: sorted array pe BS demo ───────────────────────────────────────────
int main() {
    int arr[] = {12,23,34,45,56,57} ;
    int size = 6;
    int i=0, j= size-1;
    int target = 56 ;
    int ans = binarysearch(arr, size, i, j, target);
    cout<< "element is present at "<< ans << endl;
    return 0;
}
