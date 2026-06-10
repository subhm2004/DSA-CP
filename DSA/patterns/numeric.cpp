/*
 * ============================================================================
 * TOPIC    : Patterns
 * FILE     : numeric.cpp
 * PROBLEM  : Numeric
 * ABOUT    : Pattern printing using nested loops
 * APPROACH : Nested for-loops: outer = rows, inner = columns/spaces.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// NUMERIC PATTERN — incomplete scaffold (spaces loop only)
// ────────────────────────────────────────────────────────────────────────────
// Funda: outer loop rows, inner loop leading spaces
// Abhi sirf structure hai — numbers print logic add karna baaki
// ════════════════════════════════════════════════════════════════════════════

// ── main: numeric pattern scaffold ───────────────────────────────────────────
//   1) n input lo
//   2) har row i: (n-i-1) spaces ka inner loop — abhi empty body
//   3) numbers print logic yahan add hoga
int main() {
    int n;
    cout<< "enter any number"<< endl;
    cin>> n;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n-i-1; j++) {
            // leading spaces — body abhi empty
        }
    }
}
