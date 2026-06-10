/*
 * ============================================================================
 * TOPIC    : Binary Search
 * FILE     : ekos_spoj.cpp
 * PROBLEM  : Ekos Spoj
 * LEETCODE : 410 — Split Array Largest Sum (binary search on answer)
 * ABOUT    : Binary search templates and classic interview problems
 * APPROACH : Binary search on sorted array or on answer.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <algorithm>
using namespace std;



// ════════════════════════════════════════════════════════════════════════════
// EKO SPOJ — Max height cut, min wood waste (BS on answer)
// ────────────────────────────────────────────────────────────────────────────
// Trees height mid pe cut — sum(arr[i]-mid) >= woodreq?
// MAX height pattern: possible -> ans=mid, s=mid+1
// ════════════════════════════════════════════════════════════════════════════


// ── ispossible: enough wood at mid? ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
bool ispossible(int *arr, int& size, int& woodreq, int& mid){
    int sum = 0;
    // Iterate over all elements
    for(int i=0; i<size; i++){
        if(arr[i]- mid> 0){
            sum = sum+ (arr[i]- mid);
        }
    }
    if(sum>= woodreq){
        return true;
    }
    else {
        return false;
    }
}



// ── maximumheight: max cut height ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
int maximumheight(int *arr, int& size, int& woodreq){
    int maxi= -1;
    // Iterate over all elements
    for(int i=0; i<size; i++){
        maxi= max(maxi, arr[i]);
    }
    int ans= -1;
    int s=0;
    int e= *max_element(arr, arr+size); // stl function
    int mid= s+(e-s)/2;
    while(s<=e){
        if(ispossible(arr, size,woodreq,mid)){
        ans= mid;
        s= mid+1;
         }
        else {
        e= mid-1;
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
    int arr[]= {4,42,40,26,46};
    int size= 5;
    int woodreq= 20;
    int f= maximumheight(arr,size,woodreq);
    cout<< f<< endl;
}
