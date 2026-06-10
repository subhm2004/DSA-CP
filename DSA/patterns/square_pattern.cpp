/*
 * ============================================================================
 * TOPIC    : Patterns
 * FILE     : square_pattern.cpp
 * PROBLEM  : Square Pattern
 * ABOUT    : Pattern printing using nested loops
 * APPROACH : Nested loops control rows/columns for shape.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// SOLID SQUARE — n×n grid of stars
// ────────────────────────────────────────────────────────────────────────────
// Funda: outer loop n rows, inner loop n stars per row
// Sabse basic pattern — square solid fill
// ════════════════════════════════════════════════════════════════════════════

// ── main: n×n solid square print ─────────────────────────────────────────────
//   1) n input — side length
//   2) n rows, har row me n stars
//   3) newline har row ke baad
int main() {
    int n;
    cout<< "enter any number"<< endl;
    cin>> n;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
           cout<< "*"; // har cell me star
        }
        cout<< "\n";
    }
}
