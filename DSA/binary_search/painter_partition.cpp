/*
 * ============================================================================
 * TOPIC    : Binary Search
 * FILE     : painter_partition.cpp
 * PROBLEM  : Painter Partition
 * LEETCODE : 410 — Split Array Largest Sum
 * ABOUT    : Binary search templates and classic interview problems
 * APPROACH : Binary search on sorted array or on answer.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <numeric>
using namespace std;



// ════════════════════════════════════════════════════════════════════════════
// PAINTER PARTITION — K painters, min max time (BS on answer)
// ────────────────────────────────────────────────────────────────────────────
// Boards contiguous — har painter ko consecutive boards
// ispossiblesln(mid): mid time me K painters kaam kar sakte?
// MIN max time — same book allocation pattern
// ════════════════════════════════════════════════════════════════════════════


// ── ispossiblesln: mid time feasible? ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
bool ispossiblesln(int *arr, int& size, int& k, int mid){
    int paintercount= 1;
    int boardlenalloc=0;
    // Iterate over all elements
    for(int i=0; i<size; i++){
        if(boardlenalloc+ arr[i]<= mid){
            boardlenalloc+= arr[i];
        }
        else {
            paintercount++;
            if(paintercount> k || arr[i]> mid){
                return false;
            }
            else {
                boardlenalloc=arr[i];
            }
        }
    }
}



// ── mintime: min max time ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
int mintime(int *arr, int& size, int& k){
    int s=0;
    int e= accumulate(arr,arr+size, 0);
    int mid= s+(e-s)/2;
    int ans= -1;
    while(s<=e){
        if(ispossiblesln(arr,size,k,mid)){
            ans= mid;
            e= mid-1;
        }
        else {
            s= mid+1;
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
int main(){
    int arr[]= {5,10,30,20,15};
    int size= 5; // number of boards= length of array
    int k= 3;
    int ans= mintime(arr,size,k);
    cout<< ans<< endl;

}
