/*
 * ============================================================================
 * TOPIC    : Binary Search
 * FILE     : unbounded_binary_search.cpp
 * PROBLEM  : Unbounded Binary Search
 * LEETCODE : 704 — Binary Search (unbounded range)
 * ABOUT    : Binary search templates and classic interview problems
 * APPROACH : Binary search — eliminate half the search space each step.
 * COMPLEX  : Time: O(log n)  |  Space: O(1)
 * ============================================================================
 */

#include <iostream>
using namespace std;



// ════════════════════════════════════════════════════════════════════════════
// UNBOUNDED BINARY SEARCH — Infinite sorted array
// ────────────────────────────────────────────────────────────────────────────
// Pehle range find: j double jab tak arr[j]<target
// Phir BS on [i, j] — bounded range pe search
// ════════════════════════════════════════════════════════════════════════════


// ── binarysearch: BS helper ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
int binarysearch(int *arr, int i, int j, int & target){
    int mid= i+j/2;
    while(i<=j){
        if(arr[mid]== target){
            return mid;
        }
        else if(arr[mid]> target){
            j= mid-1;
        }
        else {
            i= mid+1;
        }
        mid= i+j/2;
    }
    return -1;

}



// ── unboundedsearch: unbounded range ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
int unboundedsearch(int *arr, int& target){
    int i=0, j= i+1;
    while(arr[j]<target){
        i=j;
        j<<1;
    }
    return binarysearch(arr,i,j,target);

}



// ── main: demo ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
int main() {

    
}
