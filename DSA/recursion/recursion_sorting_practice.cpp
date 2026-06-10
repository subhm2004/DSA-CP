/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : recursion_sorting_practice.cpp
 * PROBLEM  : Recursion Sorting Practice
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Base case + solve smaller subproblem recursively.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// MERGE SORT PRACTICE — Divide, sort, merge recursively
// ────────────────────────────────────────────────────────────────────────────
// merge(): temp left/right arrays, two-pointer merge back
// mergesort(): s>=e base, mid split, recurse both halves
// Classic O(n log n) sorting via recursion
// ════════════════════════════════════════════════════════════════════════════

// ── merge: sorted halves ko ek array me jodo ────────────────────────────────
//   1) left/right temp arrays banao aur copy karo
//   2) chhota element arr[k] me daalo
//   3) leftover copy karo
void merge(int* arr, int s, int e) {
    int mid = s+(e-s)/2;
    int length1 = mid-s+1;
    int length2 = e-mid;
    int* left = new int[length1];
    int* right = new int[length2];
    int k=s;
    for(int i=0; i<length1; i++) {
        left[i] = arr[k];
        k++;
    }
    k= mid+1;
    for(int i=0; i< length2; i++) {
        right[i] = arr[k];
        k++;
    }
    int i=0, j=0;
    k=s;
    while(i<length1 && j< length2) {
        if(left[i]< right[j]) {
            arr[k++] = left[i++];
        }
        if(left[i] >= right[j]) {
            arr[k++] = right[j++];
        }
    }
    while(i<length1) {
        arr[k++] = left[i++];
    }
    while(j< length2) {
        arr[k++] = right[j++];
    }
}
 
// ── mergesort: array ko recursively sort karo ───────────────────────────────
//   1) s>=e -> base case
//   2) mid pe divide, dono halves sort
//   3) merge se jodo
 void mergesort(int* arr, int s, int e) {
    if(s>=e) {
        return;
    }
    int mid = s+ (e-s)/2;
    mergesort(arr, s, mid);
    mergesort(arr, mid+1, e);
    merge(arr, s, e);

}

// ── main: merge sort demo ─────────────────────────────────────────────────────
int main() {
    int arr[]= {4,2,12,5,13};
    int size = 5;
    int s=0, e = size-1;
    mergesort(arr,s,e);
    cout<< "sorted array is"<< endl;
    for(int i=0; i< size; i++) {
        cout<< arr[i] << " ";
    }
}
