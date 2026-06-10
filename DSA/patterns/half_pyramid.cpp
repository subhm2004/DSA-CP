/*
 * ============================================================================
 * TOPIC    : Patterns
 * FILE     : half_pyramid.cpp
 * PROBLEM  : Half Pyramid
 * ABOUT    : Pattern printing using nested loops
 * APPROACH : Nested loops control rows/columns for shape.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// HALF PYRAMID — har row me stars badhte hain (left aligned)
// ────────────────────────────────────────────────────────────────────────────
// Funda: row i me (i+1) stars — simple nested loop
// Outer = rows, inner = stars count
// ════════════════════════════════════════════════════════════════════════════

// ── main: left-aligned half pyramid print ────────────────────────────────────
//   1) n input — total rows
//   2) row i pe (i+1) stars print karo
//   3) har row ke baad newline
int main() {
    int n;
    cout<< "enter any number"<< endl;
    cin>>n;
    for(int i=0; i<n; i++) {
        for(int j=0; j<i+1; j++) {
            cout<< "*"; // row i me i+1 stars
        }
        cout<< "\n";
    }
}
