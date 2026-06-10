/*
 * ============================================================================
 * TOPIC    : Binary Search
 * FILE     : peak_element.cpp
 * PROBLEM  : Peak Element
 * LEETCODE : 162 — Find Peak Element
 * ABOUT    : Binary search templates and classic interview problems
 * APPROACH : Binary search on sorted array or on answer.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;



// ════════════════════════════════════════════════════════════════════════════
// PEAK ELEMENT — arr[mid] > arr[mid+1] (Leetcode 162)
// ────────────────────────────────────────────────────────────────────────────
// Mountain array — peak dhundho BS se
// arr[mid]<arr[mid+1] -> peak right me; else left me
// s<e loop — peak index return
// ════════════════════════════════════════════════════════════════════════════


// ── peakelement: peak index BS ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
int peakelement(int *arr, int& size) {
    int s=0, e= size-1;
    int mid = s+(e-s)/2;
    int ans=-1;
    while(s<e) {
        if(arr[mid] < arr[mid+1]) {
            s= mid+1;
        }
        else if(arr[mid]> arr[mid+1]) {
            ans= mid;
            e= mid;
        }
        mid= s+(e-s)/2;    
    }
    return ans;
}



// ── main: demo ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
int main() {
    int arr[] = {5,10,15,11,9,8,7,6,5};
    int size= 9;
    int ans = peakelement(arr, size);
    cout<< ans<< endl;

}
