/*
 * ============================================================================
 * TOPIC    : Binary Search
 * FILE     : book_allocation.cpp
 * PROBLEM  : Book Allocation
 * LEETCODE : 410 — Split Array Largest Sum
 * ABOUT    : Binary search templates and classic interview problems
 * APPROACH : Binary search on sorted array or on answer.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;



// ════════════════════════════════════════════════════════════════════════════
// BOOK ALLOCATION — Min max pages (BS on answer, Leetcode 410)
// ────────────────────────────────────────────────────────────────────────────
// M students, N books — contiguous allocation, minimize max pages
// ispossible(mid): mid pages limit pe sab allocate ho sakte?
// MIN max pattern: possible -> ans=mid, e=mid-1
// ════════════════════════════════════════════════════════════════════════════


// ── ispossible: mid pages feasible? ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
bool ispossible(int *arr, int& student, int& size, int mid){
    int scount = 1;
    int pagesum = 0;
    if(student> size){
            return false;
        }
    // Iterate over all elements
    for(int i=0; i<size; i++){
        if(pagesum + arr[i]<= mid){
            pagesum= pagesum+ arr[i];   
        }
        else {
            scount++;
            if(scount> student || arr[i]> mid) {
                return false;
            }
            pagesum= arr[i];
        }
    }
}



// ── findpages: min max pages ─────────────────────────────────────────────────────────
//   1) problem-specific logic yahan apply hoti hai
//   2) base case / boundary check pehle
//   3) recursive ya iterative step — chhota subproblem
//   4) return ans ya void
int findpages(int *arr, int& size, int& student){
    int s=0;
    int e= accumulate(arr, arr+size, 0);
    int mid= s+(e-s)/2;
    int ans= -1;
    while(s<=e){
        if(ispossible(arr,student,size,mid)){
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
    int arr[]= {12,34,67,90};
    int size= 4;
    int student= 2;
    int ans= findpages(arr,size,student);
    cout<< ans<< endl;
}
