/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : shift_one.cpp
 * PROBLEM  : Shift One
 * LEETCODE : 189 — Rotate Array
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Iterate with two pointers / sliding window / prefix sum.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// SHIFT ARRAY RIGHT BY 1 — last element front pe aata hai
// ────────────────────────────────────────────────────────────────────────────
// Funda: last element save karo, right se left shift karo, arr[0] = saved
// shifttwo() — 2 steps shift (TODO stub)
// COMPLEX: Time O(n)  |  Space O(1)
// ════════════════════════════════════════════════════════════════════════════

// ── shiftone: ek step right circular shift ─────────────────────────────────
//   1) temp1 = arr[size-1] save karo
//   2) j = size-1 se 0 tak — arr[j] = arr[j-1] shift
//   3) arr[0] = temp1 — last element front pe
void shiftone(int arr[], int size) {
    int temp1 = arr[size-1];
    for(int j= size-1; j>=0; j--) {
        arr[j] = arr[j-1];
    }
    arr[0] = temp1;
}


// ── shifttwo: do step right shift (abhi stub) ──────────────────────────────
//   1) last two elements save karo
//   2) poori array 2 positions shift
//   3) front pe dono place karo
void shifttwo(int arr[], int size) {
    int a = arr[size-1];
    int b = arr[size-2];
    
}


// ── printarray: array print karo ───────────────────────────────────────────
//   1) i=0 se size tak elements print
void printarray(int arr[] ,int size) {
    for(int i=0; i<size; i++) {
        cout<< arr[i]<< " ";
    }

}


// ── main: shiftone demo ────────────────────────────────────────────────────
//   1) array declare, shiftone call
//   2) shifted array print
int main() {
    int arr[] = { 10,20,30,40,50,60};
    int size = 6;
    shiftone(arr, size);
    printarray(arr,size);
    return 0;
}
