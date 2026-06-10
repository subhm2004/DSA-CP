/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : rotate_array.cpp
 * PROBLEM  : Rotate Array
 * LEETCODE : 189 — Rotate Array
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Rotate/transpose matrix in-place or with extra space.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <vector>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// ROTATE ARRAY — k steps right rotate using extra array
// ────────────────────────────────────────────────────────────────────────────
// Funda: naya index = (i + k) % size — cyclic shift formula
// Extra ans vector me place karke rotate achieve karo
// COMPLEX: Time O(n)  |  Space O(n)
// ════════════════════════════════════════════════════════════════════════════

// ── rotatearray: k steps right rotate karo ─────────────────────────────────
//   1) har i ke liye new index = (i+k) % size
//   2) ans[new_index] = arr[i] — element shift
//   3) extra vector me result store
void rotatearray(int arr[], int& size, int& k, vector<int>&ans ) {
    for(int i=0; i<size; i++) {
      ans[(i+k)%size] = arr[i];  
    }
}


// ── printarray: vector elements print karo ─────────────────────────────────
//   1) ans.size() tak loop
//   2) har element space-separated print
void printarray(vector<int>& ans) {
    for(int i=0; i<ans.size(); i++) {
        cout<< ans[i]<< " ";
    }
}


// ── main: user se k lo, rotate karke print ─────────────────────────────────
//   1) array aur k input
//   2) rotatearray() se cyclic shift
//   3) result print
int main() {
    int arr[] = {10,20,30,40,50,60,70,80};
    int k, size = 8;
    cout<< " enter number of times to rotate "<< endl;
    cin >> k;
    vector<int>ans(size);
    rotatearray(arr, size, k, ans);
    printarray(ans);

}
