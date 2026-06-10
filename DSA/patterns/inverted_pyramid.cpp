/*
 * ============================================================================
 * TOPIC    : Patterns
 * FILE     : inverted_pyramid.cpp
 * PROBLEM  : Inverted Pyramid
 * ABOUT    : Pattern printing using nested loops
 * APPROACH : Nested loops control rows/columns for shape.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// INVERTED PYRAMID — upar se neeche stars kam hote hain
// ────────────────────────────────────────────────────────────────────────────
// Funda: row i pe i spaces, phir (n-i) stars with gap
// Outer loop rows, inner loops spaces aur stars control karte hain
// ════════════════════════════════════════════════════════════════════════════

// ── main: inverted star pyramid print ────────────────────────────────────────
//   1) n input lo — kitni rows
//   2) har row i: pehle i spaces print
//   3) phir (n-i) baar "* " print
//   4) newline — agli row
int main() {
    int n;
    cout<< "enter any number"<< endl;
    cin>> n;
    for(int i=0; i<n; i++) {
        for(int j=0; j<i; j++) {
            cout<< " "; // leading spaces badhte hain
        }
        for(int j=0; j<n-i; j++) {
            cout<< "* "; // stars ghate hain har row me
        }
        cout<< "\n";
    }
}
