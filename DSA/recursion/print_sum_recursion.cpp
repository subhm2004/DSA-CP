/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : print_sum_recursion.cpp
 * PROBLEM  : Print Sum Recursion
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Base case + solve smaller subproblem recursively.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// ARRAY SUM (Recursion) — Saare elements ka total
// ────────────────────────────────────────────────────────────────────────────
// Index i se start — har step pe arr[i] sum me add
// Base: i>=size -> sum return karo
// Tail recursion jaisa pattern — pehle add, phir aage jao
// ════════════════════════════════════════════════════════════════════════════

// ── sumarray: index i se array ka sum ───────────────────────────────────────
//   1) i>=size -> base case, current sum return
//   2) sum += arr[i] — current element add
//   3) sumarray(arr, size, i+1, sum) — baaki elements
int sumarray(int arr[], int& size, int i, int& sum) {
    if(i>= size) {
        return sum;  // saare elements process ho gaye
    }
    sum = sum + arr[i];
    sumarray(arr, size, i+1, sum);
}

// ── main: array sum print ───────────────────────────────────────────────────
int main() {
    int arr[] = {1,2,3,4,5,6} ;
    int size= 6;
    int i=0;
    int sum =0;
    int ans = sumarray(arr, size, i, sum);
    cout<< "sum of array elements are "<< ans<< endl;
}
