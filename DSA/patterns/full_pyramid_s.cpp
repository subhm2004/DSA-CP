/*
 * ============================================================================
 * TOPIC    : Patterns
 * FILE     : full_pyramid_s.cpp
 * PROBLEM  : Full Pyramid S
 * ABOUT    : Pattern printing using nested loops
 * APPROACH : Nested loops control rows/columns for shape.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// FULL PYRAMID — centered star pyramid (solid)
// ────────────────────────────────────────────────────────────────────────────
// Funda: row i pe (n-1-i) leading spaces, phir stars badhte hain
// Inner star loop n-i-1 se n-1 tak — right-aligned growing triangle
// ════════════════════════════════════════════════════════════════════════════

// ── main: centered full pyramid print ────────────────────────────────────────
//   1) n input — pyramid height
//   2) row i: (n-1-i) spaces, phir stars n-i se n tak
//   3) newline har row
int main() {
    int n;
    cout<< "enter any number"<< endl;
    cin>> n;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n-1-i; j++) {
            cout<< " "; // center ke liye leading spaces
        }
        for(int j=n-i-1; j<n; j++) {
            cout<< "* "; // stars badhte hain
        }
        cout<< "\n";
    }
}
