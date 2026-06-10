/*
 * ============================================================================
 * TOPIC    : Patterns
 * FILE     : numeric_hollow.cpp
 * PROBLEM  : Numeric Hollow
 * ABOUT    : Pattern printing using nested loops
 * APPROACH : Nested for-loops: outer = rows, inner = columns/spaces.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// NUMERIC HOLLOW PYRAMID — boundary pe numbers, andar spaces
// ────────────────────────────────────────────────────────────────────────────
// Funda: hollow pyramid jaisa — sirf corners pe numbers
// Last row me 1 se n tak continuous numbers
// ════════════════════════════════════════════════════════════════════════════

// ── main: hollow numeric pyramid + base row ──────────────────────────────────
//   1) n input — pyramid height
//   2) rows 0..n-2: spaces + hollow numbers (1 left, i+1 right)
//   3) last loop: 1 se n tak base row print
int main() {
    int n;
    cout<< "enter any number"<< endl;
    cin>> n;
    for(int i=0; i<n-1; i++) {
        for(int j=0; j<n-i-1; j++) {
            cout<< " "; // leading spaces
        }
        for(int j=0; j< 2*i+1; j++) {
            if(j==0) {
                cout<< j+1; // left boundary number
            }
            else if(j== 2*i) {
                cout<< i+1; // right boundary number
            }
            else {
                cout<< " "; // hollow middle
            }
        }
        cout<< "\n";
    }
    for(int m=1; m<=n; m++) {
        cout<< m<< " "; // bottom row — 1 to n
    }

}
