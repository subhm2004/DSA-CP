/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : reverse.cpp
 * PROBLEM  : Reverse
 * LEETCODE : 344 — Reverse String (array variant)
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Swap from both ends or reverse links iteratively.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// REVERSE ARRAY — two pointers se in-place reverse
// ────────────────────────────────────────────────────────────────────────────
// Funda: start aur end pointers — swap karo, andar badhao
// start > end ho gaya to reverse complete
// COMPLEX: Time O(n)  |  Space O(1)
// ════════════════════════════════════════════════════════════════════════════

// ── main: array reverse karke print karo ───────────────────────────────────
//   1) start=0, end=size-1 — two pointer swap
//   2) har step pe arr[start] <-> arr[end] swap
//   3) start++, end-- — reversed array print
int main() {
    int arr[] = {10, 20, 30, 40, 50, 60, 70};
    int size = 7;
    int start = 0; 
    int end = size -1;
    int temp;
    while(start <= end) {     
            temp= arr[start];
            arr[start]= arr[end];
            arr[end]= temp;
            
        start++;
        end--;
    }
    for(int i=0; i<size; i++) {
        cout<< arr[i] << " ";

    }
    return 0;

}
