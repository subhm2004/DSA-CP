/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : rearrange_positive_negative.cpp
 * PROBLEM  : Rearrange Positive Negative
 * LEETCODE : 905 — Sort Array By Parity
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Iterate with two pointers / sliding window / prefix sum.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// REARRANGE POSITIVE-NEGATIVE — alternate positive at even indices
// ────────────────────────────────────────────────────────────────────────────
// Funda: even index pe positive chahiye — negative ho to aage se positive lao
// i = 0, 2, 4... pe check, inner loop se swap/find positive
// COMPLEX: Time O(n²) worst  |  Space O(1)
// ════════════════════════════════════════════════════════════════════════════

// ── rearrangearray: even indices pe positive place karo ────────────────────
//   1) i ko 0, 2, 4... pe badhao
//   2) arr[i] negative ho to j=i+1 se positive dhundho
//   3) positive mila to arr[i] me place karo
void rearrangearray(int arr[], int size, int i){
    for(i=0; i< size; i= i+2) {
        if(arr[i] < 0){
            for(int j= i+1; j<size; j++) {
                if(arr[j]> 0){
                    arr[i]= arr[j];
                    break;
                }
            }
        }       
    }
}


// ── main: mixed array rearrange demo ───────────────────────────────────────
//   1) negatives-positives mixed array
//   2) rearrangearray() call
int main() {
    int arr[] = {-5,-3,2,1,-1,0,9,-8};
    int size =8;
    int i=0;
    rearrangearray(arr, size, i);
}
