/*
 * ============================================================================
 * TOPIC    : Patterns
 * FILE     : inverted_half_pyramid.cpp
 * PROBLEM  : Inverted Half Pyramid
 * ABOUT    : Pattern printing using nested loops
 * APPROACH : Nested loops control rows/columns for shape.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// INVERTED HALF PYRAMID — pehli row sabse zyada stars
// ────────────────────────────────────────────────────────────────────────────
// Funda: row i me (n-i) stars — har row ek kam
// Left-aligned inverted triangle
// ════════════════════════════════════════════════════════════════════════════

// ── main: inverted half pyramid print ────────────────────────────────────────
//   1) n input
//   2) row i: (n-i) stars print
//   3) newline
int main() {
    int n;
    cout<< "enter any number"<< endl;
    cin>> n;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n-i; j++) {
            cout<< "*"; // stars ghate hain har row me
        }
        cout<< "\n";
    }
}
