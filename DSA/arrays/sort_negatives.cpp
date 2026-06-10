/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : sort_negatives.cpp
 * PROBLEM  : Sort Negatives
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Iterate with two pointers / sliding window / prefix sum.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// MOVE NEGATIVES TO LEFT — two pointer partition
// ────────────────────────────────────────────────────────────────────────────
// Funda: i scanner, j negative region ka end — negative mila to swap
// Positives right me, negatives left me shift ho jate hain
// COMPLEX: Time O(n)  |  Space O(1)
// ════════════════════════════════════════════════════════════════════════════

// ── sortnegative: negatives left side me lao ─────────────────────────────────
//   1) i=0 se scan — arr[i] >= 0 ho to i++ (positive skip)
//   2) negative mila to swap(arr[i], arr[j]), dono pointers aage
//   3) i < size tak chalao — sab negatives left me
void sortnegative(int arr[], int& size,int& i, int& j) {
    while(i<size) {
        if(arr[i]>= 0) {
            i++;
        }
        else {
            swap(arr[i], arr[j]);
            i++;
            j++;
        }
    }

}


// ── main: mixed array me negatives left sort ───────────────────────────────
//   1) mixed positive-negative array
//   2) sortnegative() call
//   3) rearranged array print
int main() {
    int arr[] = {23,-7, 12, -10, -11, 40, 60};
    int size = 7;
    int i=0, j=0;
    sortnegative(arr, size, i, j);

    for(int i=0; i< size; i++) {
        cout<< arr[i] << "  ";
    }
}
