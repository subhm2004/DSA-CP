/*
 * ============================================================================
 * TOPIC    : Patterns
 * FILE     : pattern_practice_2.cpp
 * PROBLEM  : Pattern Practice 2
 * ABOUT    : Pattern printing using nested loops
 * APPROACH : Nested loops control rows/columns for shape.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// HOLLOW DIAMOND — upar hollow pyramid + neeche inverted hollow pyramid
// ────────────────────────────────────────────────────────────────────────────
// Funda: pehla loop growing hollow triangle, doosra shrinking
// Sirf corners pe '*' — beech spaces, diamond shape
// ════════════════════════════════════════════════════════════════════════════

// ── main: hollow diamond pattern print ───────────────────────────────────────
//   1) n input — half height
//   2) upper half: spaces + hollow stars (2*i+1 width)
//   3) lower half: spaces + inverted hollow (2*n-2*i-2 width)
//   4) har segment ke baad newline
int main() {
    int n;
    cout<< "enter any number"<< endl;
    cin>> n;
    for(int i=0; i<n; i++) {
        for(int j=0; j< n-i-1; j++) {
            cout<< " "; // upper leading spaces
        }
        for(int j=0; j< 2*i+1; j++) {
            if(j==0 || j== 2*i) {
                cout<< "*"; // upper hollow boundary
            }
            else {
                cout<< " ";
            }
        }
        cout<< "\n";
    }
        for(int i=0; i<n; i++) {
        for(int j=0; j<i; j++) {
            cout<< " "; // lower leading spaces
        }
        for(int j=0; j< 2*n-2*i-2;j++ ) {
            if(j==0 || j== 2*n-2*i-2) {
                cout<< "*"; // lower hollow boundary
            }
            else {
                cout<< " ";
            }
        }
        cout<< "\n";
    }
}
