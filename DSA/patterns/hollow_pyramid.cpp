/*
 * ============================================================================
 * TOPIC    : Patterns
 * FILE     : hollow_pyramid.cpp
 * PROBLEM  : Hollow Pyramid
 * ABOUT    : Pattern printing using nested loops
 * APPROACH : Nested loops control rows/columns for shape.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// HOLLOW PYRAMID — sirf boundary pe stars, andar spaces
// ────────────────────────────────────────────────────────────────────────────
// Funda: row i pe (n-1-i) spaces, phir (2*i+1) chars
// Sirf first aur last position pe '*' — beech me space
// ════════════════════════════════════════════════════════════════════════════

// ── main: hollow star pyramid print ──────────────────────────────────────────
//   1) n input lo
//   2) har row: leading spaces (n-1-i)
//   3) inner loop 2*i+1 — j==0 ya j==2*i pe star, warna space
//   4) newline, next row
int main() {
    int n;
    cout<< "enter any number"<< endl;
    cin>> n;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n-1-i; j++) {
            cout<< " "; // center align ke liye spaces
        }
        for(int j=0; j< 2*i+1; j++) {
            if(j==0 || j== 2*i) {
                cout<< "*"; // boundary stars
            }
            else {
                cout<< " "; // hollow interior
            }

        }
        cout<< "\n";
    }
}
