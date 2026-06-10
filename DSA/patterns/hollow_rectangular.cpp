/*
 * ============================================================================
 * TOPIC    : Patterns
 * FILE     : hollow_rectangular.cpp
 * PROBLEM  : Hollow Rectangular
 * ABOUT    : Pattern printing using nested loops
 * APPROACH : Nested for-loops: outer = rows, inner = columns/spaces.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// HOLLOW RECTANGLE — sirf border pe stars, andar khali
// ────────────────────────────────────────────────────────────────────────────
// Funda: pehli/last row full stars; beech ki rows me sirf corners
// m rows, n columns — border print, interior spaces
// ════════════════════════════════════════════════════════════════════════════

// ── main: m×n hollow rectangle print ─────────────────────────────────────────
//   1) m (rows), n (cols) input
//   2) row 0 ya m-1? poori row stars
//   3) beech ki row: star + (n-2) spaces + star
//   4) har row ke baad newline
int main() {
    int m,n;
    cout<< "enter row and column number"<< endl;
    cin>>m>> n;
    for(int i=0; i<m; i++) {
        if(i==0 || i==m-1) {
            for(int j=0; j<n; j++ ) {
                cout<< "* "; // top/bottom border — full row
            }
        }
        else { cout<< "* ";
            for(int j=1; j<=n-2; j++) {
                cout<< "  "; // interior hollow — double space
            }
            cout<< "* "; // right border star
        }
        cout<< "\n";

    }
}
