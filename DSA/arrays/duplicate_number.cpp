/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : duplicate_number.cpp
 * PROBLEM  : Duplicate Number
 * LEETCODE : 287 — Find the Duplicate Number
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Hash set or sorting to find duplicates.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <algorithm>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// FIND DUPLICATE — sort karke adjacent compare
// ────────────────────────────────────────────────────────────────────────────
// Funda: sort ke baad duplicate side-by-side aayega
// arr[i] == arr[i+1] ho to wahi duplicate hai
// duplicate2() — Floyd cycle detection (TODO stub)
// COMPLEX: Sort approach O(n log n)  |  Floyd O(n) O(1) space
// ════════════════════════════════════════════════════════════════════════════

// ── duplicate: sort + adjacent scan se duplicate dhundho ───────────────────
//   1) sort(arr, arr+size) — duplicates paas aa jayenge
//   2) i=0 se size-2 tak — arr[i]==arr[i+1] check
//   3) match mila to duplicate return, warna -1
int duplicate (int *arr, int& size) {
    sort(arr, arr+size);
    for(int i=0; i<size-1; i++) {
        if(arr[i]== arr[i+1] ) {
            return arr[i];
        }
    }
    return -1;
}


// ── duplicate2: Floyd cycle detection (abhi empty stub) ────────────────────
//   1) array ko linked list jaisa treat karo — arr[i] -> arr[arr[i]]
//   2) slow-fast pointer se cycle entry = duplicate
//   3) implementation pending
int duplicate2(int *arr, int& size) {
    
}


// ── main: duplicate() demo ─────────────────────────────────────────────────
//   1) sample array {1,2,4,4,3}
//   2) duplicate print karo
int main() {
    int arr[] = {1,2,4,4,3};
    int size = 5;
    int ans = duplicate(arr, size);
    cout<< ans<< endl;
}
