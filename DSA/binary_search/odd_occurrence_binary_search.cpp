/*
 * ============================================================================
 * TOPIC    : Binary Search
 * FILE     : odd_occurrence_binary_search.cpp
 * PROBLEM  : Odd Occurrence Binary Search
 * LEETCODE : 540 — Single Element in a Sorted Array
 * ABOUT    : Binary search templates and classic interview problems
 * APPROACH : Binary search — eliminate half the search space each step.
 * COMPLEX  : Time: O(log n)  |  Space: O(1)
 * ============================================================================
 */

#include <iostream>
#include <vector>
using namespace std;



// ════════════════════════════════════════════════════════════════════════════
// SINGLE ELEMENT — Odd occurrence in sorted pairs (Leetcode 540)
// ────────────────────────────────────────────────────────────────────────────
// Pairs me same element — single wala alag
// mid even/odd se decide kaunsa half me single hai
// BS on index — O(log n)
// ════════════════════════════════════════════════════════════════════════════


// ── oddoccurence: single element BS ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
int oddoccurence(vector<int>& arr) {
    int s=0, e= arr.size()-1;
    int mid= s+(e-s)/2;
    while(s<=e) {
        if(s==e){
            return s;
        }
        if(mid&1){ //fast method to check odd/even number
            if(mid-1>0 && arr[mid]== arr[mid-1]){
                s= mid+1;
            }
            else {
                e= mid-1;
            }
        }
        else {
            if(mid+1< arr.size() && arr[mid]== arr[mid+1]){
                s= mid+2;
            }
            else{
                e= mid;
            }
        }
        mid= s+(e-s)/2;
    }
}



// ── main: demo ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
int main(){
    vector<int>arr= {10,10,5,5,2,2,5,5,20,20,10,10,11,11,1};
    int ans= oddoccurence(arr);
    cout<< ans<< endl;
}
