/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : print_pairs.cpp
 * PROBLEM  : Print Pairs
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Iterate with two pointers / sliding window / prefix sum.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// PRINT ALL PAIRS — har (i,j) combination print karo
// ────────────────────────────────────────────────────────────────────────────
// Funda: nested loop — outer i, inner j — sab ordered pairs
// Total n*n pairs — brute force pair generation
// COMPLEX: Time O(n²)  |  Space O(1)
// ════════════════════════════════════════════════════════════════════════════

// ── main: array ke saare pairs print karo ─────────────────────────────────
//   1) outer loop i — har element as first of pair
//   2) inner loop j — har element as second of pair
//   3) arr[i], arr[j] comma-separated print
int main() {
    int arr[] = {10,20,30};
    int size =3;
    cout<< "pairs of the array are"<< endl;
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            cout<< arr[i]<< ","<< arr[j]<< endl;
        }
    }
}
