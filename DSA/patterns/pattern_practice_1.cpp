/*
 * ============================================================================
 * TOPIC    : Patterns
 * FILE     : pattern_practice_1.cpp
 * PROBLEM  : Pattern Practice 1
 * ABOUT    : Pattern printing using nested loops
 * APPROACH : Nested loops control rows/columns for shape.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// PALINDROMIC NUMBER PYRAMID — har row ascending then descending numbers
// ────────────────────────────────────────────────────────────────────────────
// Funda: leading spaces + ascending numbers + descending mirror
// start = i+1 se count badhao, phir reverse count ghatao
// ════════════════════════════════════════════════════════════════════════════

// ── main: palindromic numeric pyramid print ──────────────────────────────────
//   1) n input — rows count
//   2) row i: (n-i-1) spaces
//   3) ascending loop: start se n tak numbers print, start++
//   4) descending loop: start-2 se reverse print
//   5) newline
int main() {
    int n;
    cout<< "enter any number"<< endl;
    cin>> n;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n-i-1; j++) {
            cout<< " "; // center alignment
        }
        int start= i+1;
        for(int j=n-i-1; j<n; j++) {
           
            cout<< start; // ascending part
            start++;
        }
        for(int j=0; j<i; j++) {
            cout<< start-2; // descending mirror
            start--;
        }
        cout<< "\n";
    }
}
