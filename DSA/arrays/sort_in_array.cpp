/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : sort_in_array.cpp
 * PROBLEM  : Sort In Array
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Iterate with two pointers / sliding window / prefix sum.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <vector>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// SORT 0s AND 1s — count karke naya sorted array banao
// ────────────────────────────────────────────────────────────────────────────
// Funda: pehle 0 aur 1 count karo, phir brr me pehle 1s phir 0s push
// Counting sort jaisa approach — sirf do values
// COMPLEX: Time O(n)  |  Space O(n) for brr
// ════════════════════════════════════════════════════════════════════════════

// ── main: 0-1 array count karke sort karo ──────────────────────────────────
//   1) arr scan — zero aur one count
//   2) brr me pehle 'one' count times 1 push
//   3) phir 'zero' count times 0 push — sorted output
int main() {
    vector<int>arr{1,0,1,1,0,1,1,0,0,0,1,0};
    int zero= 0, one =0;
    for(int i=0; i<arr.size(); i++) {
        if(arr[i] == 0) {
            zero++;
        }
        else {
            one++;
        }
    }
    cout<< zero<< endl;
    cout<< one<< endl;

    vector<int>brr;

    for(int i=0; i< one; i++) {
        brr.push_back(1);
    }
    cout<< endl;
    for(int i = 0; i < one; i++) {
        cout<< brr[i] << " ";
    }
    cout<< endl;
    for(int i=0; i<zero; i++) {
        brr.push_back(0);
    }
    cout<< "elements of final array are "<<endl;
    for(int i=0; i< brr.size(); i++) {
        cout<< brr[i] << " ";
    }

}
