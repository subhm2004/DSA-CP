/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : array_basics_1.cpp
 * PROBLEM  : Array Basics 1
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Iterate with two pointers / sliding window / prefix sum.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// ARRAY BASICS 1 — Pass-by-value vs pass-by-reference demo
// ────────────────────────────────────────────────────────────────────────────
// Funda: array function me pass karo to pointer copy hota hai, original nahi badhta
// inc() me arr[] actually pointer hai — arr[0] change ho sakta hai lekin size info nahi
// Yeh file basic array declaration aur function call practice ke liye hai
// COMPLEX: Time O(1) per call  |  Space O(1)
// ════════════════════════════════════════════════════════════════════════════

// ── inc: array ke pehle element me 10 add karo ─────────────────────────────
//   1) arr pointer se pehla element arr[0] access karo
//   2) usme 10 add karke update karo
//   3) arr pointer address print karo (debug ke liye)
void inc(int arr[] ) {
    arr[0] = arr[0] + 10;
    cout<< arr;
}


// ── main: array declare karke inc() call karo ───────────────────────────────
//   1) fixed-size array {1,2} banao
//   2) function call — pass-by-value pointer behavior observe karo
int main() {
    
   


    


   
    int arr[] = {1,2};


}
