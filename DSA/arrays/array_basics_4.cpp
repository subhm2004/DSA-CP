/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : array_basics_4.cpp
 * PROBLEM  : Array Basics 4
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Iterate with two pointers / sliding window / prefix sum.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// INTERSECTION OF TWO ARRAYS — brute force nested loop
// ────────────────────────────────────────────────────────────────────────────
// Funda: har arr[i] ko har brr[j] se match karo
// Equal ho to print — common elements nikalne ka basic approach
// COMPLEX: Time O(n*m)  |  Space O(1)
// ════════════════════════════════════════════════════════════════════════════

// ── main: do arrays ka intersection print karo ─────────────────────────────
//   1) arr aur brr fixed arrays declare karo
//   2) nested loop — i har arr element, j har brr element
//   3) arr[i] == brr[j] ho to common element print karo
int main() {
    int arr[] = { 1,3,3,4,4,5,5,6};
    int sizearr = 8;
    int brr[] = {3, 3,5,5,8, 9};
    int sizebrr = 4;
    for(int i=0; i< sizearr; i++) {
        for(int j=0; j< sizebrr; j++) {
            if(arr[i] == brr[j]) {
                cout<< arr[i] << " ";
            }
        }
    }
}
