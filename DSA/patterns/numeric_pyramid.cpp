/*
 * ============================================================================
 * TOPIC    : Patterns
 * FILE     : numeric_pyramid.cpp
 * PROBLEM  : Numeric Pyramid
 * ABOUT    : Pattern printing using nested loops
 * APPROACH : Nested loops control rows/columns for shape.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// NUMERIC PYRAMID — har row me 1 se (i+1) tak numbers
// ────────────────────────────────────────────────────────────────────────────
// Funda: row i me j=0..i — print j+1 (1-based counting)
// Left-aligned numeric half pyramid
// ════════════════════════════════════════════════════════════════════════════

// ── main: numeric half pyramid print ─────────────────────────────────────────
//   1) n rows input
//   2) row i: j=0 se i tak j+1 print
//   3) newline har row ke baad
int main() {
    int n;
    cout<< "enter any number"<< endl;
    cin>> n;
    for(int i=0; i<n; i++) {
        for(int j=0; j<i+1; j++) {
            cout<< j+1; // 1, 12, 123, ... pattern
        }
        cout<< "\n";
    }
}
