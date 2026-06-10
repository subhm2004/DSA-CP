/*
 * ============================================================================
 * TOPIC    : Binary Search
 * FILE     : exponential_search.cpp
 * PROBLEM  : Exponential Search
 * LEETCODE : 704 — Binary Search (exponential search variant)
 * ABOUT    : Binary search templates and classic interview problems
 * APPROACH : Binary search on sorted array or on answer.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <algorithm>
using namespace std;



// ════════════════════════════════════════════════════════════════════════════
// EXPONENTIAL SEARCH — Range double, phir BS
// ────────────────────────────────────────────────────────────────────────────
// i=1,2,4,8... jab tak arr[i]<=target
// Phir binarysearch(i/2, min(i,n-1))
// Unbounded/infinite array ke liye useful
// ════════════════════════════════════════════════════════════════════════════


// ── binarysearch: BS helper ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
int binarysearch(int *arr, int& size, int s, int e, int& target){
    int mid= s+(e-s)/2;
    while(s<=e){
        if(arr[mid]== target){
            return mid;
        }
        else if(arr[mid]> target){
            e= mid-1;
        }
        else{
            s= mid+1;
        }
        mid= s+(e-s)/2;
    }
    return -1;
}



// ── exponential: exp search ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
int exponential(int *arr, int& size, int& target){
    if(arr[0]== target){
        return 0;
    }
    int i=1;
    while(i<size && arr[i]<= target){
        i= i<<1;
    }
    return binarysearch(arr, size, i/2, min(i,size-1),target);
}



// ── main: demo ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
int main(){
    int arr[] = {3,4,5,6,11,13,14,15,56,70};
    int size= 10;
    int target= 70;
    int ans= exponential(arr,size,target);
    cout<< ans<< endl;


}
