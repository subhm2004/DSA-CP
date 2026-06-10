/*
 * ============================================================================
 * TOPIC    : Patterns
 * FILE     : pattern_practice_3.cpp
 * PROBLEM  : Pattern Practice 3
 * ABOUT    : Pattern printing using nested loops
 * APPROACH : Nested loops control rows/columns for shape.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// FLOYD'S TRIANGLE VARIANT — har row me sequential numbers
// ────────────────────────────────────────────────────────────────────────────
// Funda: row i, col j pe number = i+j+1 print karo
// Har row me (i+1) numbers — continuous counting feel
// ════════════════════════════════════════════════════════════════════════════

// ── main: i+j+1 numeric pattern print ────────────────────────────────────────
//   1) n rows input
//   2) row i, col j: cout i+j+1
//   3) newline — agli row
int main() {
    int n;
    cout<< "enter any number"<< endl;
    cin>> n;
    for(int i=0; i<n; i++) {
        for(int j=0; j<i+1; j++) {
            cout<< i+j+1; // row-dependent sequential number
        }
        cout<< "\n";
    }

}
