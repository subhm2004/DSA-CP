/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : print_extremes.cpp
 * PROBLEM  : Print Extremes
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Iterate with two pointers / sliding window / prefix sum.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// PRINT EXTREMES — start aur end se alternate print
// ────────────────────────────────────────────────────────────────────────────
// Funda: two pointers i (start) aur j (end) — dono taraf se print
// i++ aur j-- har step pe — middle pe sirf ek element
// COMPLEX: Time O(n)  |  Space O(1)
// ════════════════════════════════════════════════════════════════════════════

// ── main: extremes se alternate print karo ─────────────────────────────────
//   1) i=0, j=size-1 — two pointer window
//   2) i==j ho to middle element, warna arr[i] aur arr[j] dono
//   3) i++, j-- — pointers andar aate hain
int main() {
    int arr[] = {10, 20 ,30, 40, 50, 60, 70, 80};
    int size = 8;
    int i = 0, j = size -1;
    while(i <= j) {
        if( i == j) {
            cout<< arr[i]<< " ";
        }
        else {
        cout<< arr[i]<< " ";
        cout<< arr[j]<< " ";
        }
        i++;
        j--;
        
    }
    return 0;
}
