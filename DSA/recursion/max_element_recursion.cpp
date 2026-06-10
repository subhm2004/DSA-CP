/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : max_element_recursion.cpp
 * PROBLEM  : Max Element Recursion
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Base case + solve smaller subproblem recursively.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <limits.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// MAX ELEMENT (Recursion) — Array ka sabse bada element
// ────────────────────────────────────────────────────────────────────────────
// max reference pass — har step pe compare aur update
// Base: i>=size -> return
// INT_MIN se start — koi bhi element bada hoga
// ════════════════════════════════════════════════════════════════════════════

// ── maxelement: index i se maximum dhundho ──────────────────────────────────
//   1) i>=size -> base case
//   2) arr[i]>max -> max update
//   3) recursive call i+1 pe
void maxelement(int arr[], int size, int& max , int i) { 
    if(i>=size) {
        return;
    }
    
    if(arr[i]> max) {
        max = arr[i];  // naya maximum
    }
    maxelement(arr, size , max, i+1);
    
}

// ── main: maximum element print ─────────────────────────────────────────────
int main() {
    int arr[] = { 10,12,34,35,45,67};
    int size = 6;
    int i=0;
    int max = INT_MIN;

    maxelement(arr, size, max, i);
    cout<< "maximum element is "<< max << endl;
    return 0;
}
