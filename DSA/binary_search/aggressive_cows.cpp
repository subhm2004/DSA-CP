/*
 * ============================================================================
 * TOPIC    : Binary Search
 * FILE     : aggressive_cows.cpp
 * PROBLEM  : Aggressive Cows
 * LEETCODE : 410 — Split Array Largest Sum (BS on answer — GFG variant)
 * ABOUT    : Binary search templates and classic interview problems
 * APPROACH : Binary search on sorted array or on answer.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <algorithm>
using namespace std;



// ════════════════════════════════════════════════════════════════════════════
// AGGRESSIVE COWS — K cows, maximum minimum distance (BS on answer)
// ────────────────────────────────────────────────────────────────────────────
// Stalls sort karo — distance d pe greedy check: pehli cow, agli jahan gap>=d
// d badhane pe harder — monotonic false...true pattern
// MAX answer: possible -> lo=mid+1
// ════════════════════════════════════════════════════════════════════════════


// ── ispossible: d distance pe K cows fit? ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
bool ispossible(int *arr, int& size, int& mid, int& k){
    int cowcount= 1;
    int stallallocate= arr[0];  // pehli cow pehli stall pe
    for(int i=1; i<size; i++){
        if(arr[i]-stallallocate>= mid){  // gap >= d — nayi cow yahan
            cowcount++;
            stallallocate= arr[i];
        }
        if(cowcount==k){
            return true;  // K cows fit ho gayi
        }
    }
    return false;
}



// ── mindistance: max min distance BS ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
int mindistance(int *arr, int& size, int& k){
    sort(arr,arr+size);  // stalls sorted honi chahiye
    int s=0;
    int e= arr[size-1];  // max possible distance
    int mid= s+(e-s)/2;
    int ans= -1;
    while(s<=e){
        if(ispossible(arr,size,mid,k)){
            ans= mid;       // possible — aur bada distance try
            s= mid+1;
        }
        else {
            e= mid-1;       // nahi fit — chhota distance
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
    int arr[]= {10,1,2,7,5};
    int size= 5;
    int k= 3;
    int ans= mindistance(arr,size,k);
    cout<< ans<< endl;
}
