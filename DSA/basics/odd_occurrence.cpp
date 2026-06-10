/*
 * ============================================================================
 * TOPIC    : Basics
 * FILE     : odd_occurrence.cpp
 * PROBLEM  : Odd Occurrence
 * ABOUT    : Fundamental DSA — loops, sorting, strings, character operations
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <vector>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// ODD OCCURRENCE — sorted array me odd-frequency element ka index
// ────────────────────────────────────────────────────────────────────────────
// Funda: sorted array me pairs adjacent hain — BS se odd wala dhundho
// mid even/odd index pe alag logic — pair ke left/right me jao
// COMPLEX: Time O(log n)  |  Space O(1)
// ════════════════════════════════════════════════════════════════════════════

// ── solve: BS se odd-occurrence element ka index ───────────────────────────
//   1) s,e window me binary search
//   2) s==e ho to single element — return index
//   3) mid even: pair arr[mid]==arr[mid+1] -> right half, warna left
//   4) mid odd: pair arr[mid]==arr[mid-1] -> right, warna left
int solve(vector<int>arr) {
    int s=0;
    int e= arr.size() - 1;
    int mid= s+ (e-s)/2;
    while(s<=e) {
        if(s==e) {
            return s;
        }
        if(mid %2==0) {
            if(arr[mid] == arr[mid +1]) {
                s = mid+2;  // pair right me — odd element right half me
            }
            else {
                e=mid;
            }
        }
        else {
            if(arr[mid] == arr[mid-1]) {
                s= mid+1;
            }
            else {
                e= mid-1;
            }
        }
        mid = s+ (e-s)/2;
    }
    return -1;
}


// ── main: odd occurrence element dhundho ───────────────────────────────────
//   1) sorted array with pairs + one odd element
//   2) solve() se index, value print
int main() {
    vector<int> arr= {1,1,2,2,3,3,4,4,3,6,6,4,4};
    int ans= solve(arr);
    cout<< "index of required element is "<< ans<< endl;
    cout<< "value of element is "<< arr[ans]<< endl;
    return 0;
}
