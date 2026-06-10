/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : min_element_recursion.cpp
 * PROBLEM  : Min Element Recursion
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Base case + solve smaller subproblem recursively.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <limits.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// MIN ELEMENT (Recursion) — Array ka sabse chhota element
// ────────────────────────────────────────────────────────────────────────────
// min reference se pass — har index pe compare karke update
// Base: i>=size -> return (min already set)
// INT_MAX se start — koi bhi element chhota hoga
// ════════════════════════════════════════════════════════════════════════════

// ── minelement: index i se minimum dhundho ──────────────────────────────────
//   1) i>=size -> base case, return
//   2) arr[i] < min -> min update karo
//   3) minelement(arr, size, i+1, min) — baaki array
void minelement(int arr[], int size, int i, int& min) {
    if(i>= size) {
        return;  // poora array scan ho gaya
    }
    if(arr[i] < min) {
        min = arr[i];  // naya minimum mila
    }
    minelement(arr, size, i+1, min);

}

// ── main: minimum element print ─────────────────────────────────────────────
int main() {
    int arr[] = { 23, 34, 45, 56, 12, 67};
    int i=0, size = 6;
    int min = INT_MAX;
    minelement(arr, size, i, min);
    cout<< "minimum element is "<< min << endl;

}
