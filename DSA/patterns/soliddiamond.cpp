/*
 * ============================================================================
 * TOPIC    : Patterns
 * FILE     : soliddiamond.cpp
 * PROBLEM  : Soliddiamond
 * ABOUT    : Pattern printing using nested loops
 * APPROACH : Nested for-loops: outer = rows, inner = columns/spaces.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// SOLID DIAMOND — upar growing pyramid + neeche inverted pyramid
// ────────────────────────────────────────────────────────────────────────────
// Funda: pehla loop stars badhata hai, doosra ghataata hai
// Dono centered — spaces se align, solid stars
// ════════════════════════════════════════════════════════════════════════════

// ── main: solid diamond pattern print ────────────────────────────────────────
//   1) n input — half height
//   2) upper: (n-1-i) spaces + stars (n-i se n)
//   3) lower: i spaces + stars (i se n)
//   4) newline har row
int main() {
    int n;
    cout<< "enter any number"<< endl;
    cin>> n;
    for(int i=0; i<n; i++) {
        for(int j=0; j< n-1-i; j++) {
            cout<< " "; // upper spaces
        }
        for(int j=n-i-1; j< n; j++) {
            cout<< "* "; // growing stars
        }
        cout<< "\n";
    }
    for(int i=0; i<n; i++) {
        for(int j=0; j<i; j++) {
            cout<< " "; // lower spaces
        }
        for(int j=i; j<n; j++) {
            cout<< "* "; // shrinking stars
        }
        cout<< "\n";
    }
}
