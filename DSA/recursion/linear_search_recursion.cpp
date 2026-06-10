/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : linear_search_recursion.cpp
 * PROBLEM  : Linear Search Recursion
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Base case + solve smaller subproblem recursively.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// LINEAR SEARCH (Recursion) — Array me target dhundho
// ────────────────────────────────────────────────────────────────────────────
// Index i se start karo, har step pe i+1 pe jao
// Base: arr[i]==target mil gaya -> print index
// Worst case O(n) — poora array traverse
// ════════════════════════════════════════════════════════════════════════════

// ── linearsearch: index i se target search ────────────────────────────────
//   1) arr[i] == target -> index print, return
//   2) warna i+1 pe recursive call — aage badho
//   3) implicitly end pe kuch nahi (target nahi mila)
void linearsearch(int arr[], int& size,int i, int& target) {
    if(arr[i] == target) {
        cout<< "target found at index "<< i<< endl;
        return;
    }
    linearsearch(arr, size, i+1, target);  // agla element check karo
}

// ── main: fixed array pe linear search demo ─────────────────────────────────
int main() {
    int arr[] = {1,34,23,21,45,43};
    int size= 6;
    int target = 21;
    int i=0;
    linearsearch(arr,size,i,target);
}
