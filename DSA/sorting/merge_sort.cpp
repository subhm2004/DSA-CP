/*
 * ============================================================================
 * TOPIC    : Sorting
 * FILE     : merge_sort.cpp
 * PROBLEM  : Merge Sort
 * LEETCODE : 912 — Sort an Array
 * ABOUT    : Comparison-based sorting algorithms
 * APPROACH : Divide, sort halves recursively, merge sorted halves.
 * COMPLEX  : Time: O(n log n)  |  Space: O(n)
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// MERGE SORT — Divide & Conquer stable sort
// ────────────────────────────────────────────────────────────────────────────
// Array todo, dono halves sort, phir merge
// mergearray: temp left/right, two-pointer merge
// Guaranteed O(n log n) — worst case bhi same
// ════════════════════════════════════════════════════════════════════════════

// ── mergearray: sorted halves merge karo ────────────────────────────────────
//   1) left/right temp arrays copy
//   2) chhota element arr[index] me
//   3) leftover copy
void mergearray(int *arr, int s, int e){
    int mid= s+(e-s)/2;
    int size1= mid-s+1;
    int *left = new int[size1];
    int size2= e-mid;
    int *right= new int[size2];
    int k= s;
    for(int i=0;i< size1; i++){
        left[i]= arr[k];
        k++;
    }
    k= mid+1;
    for(int i=0;i< size2; i++){
        right[i]= arr[k];
        k++;
    }

    int i=0, j=0;
    int index=s;
    while(i<size1 && j<size2){
        if(left[i]<= right[j]){
            arr[index]= left[i];
            index++;
            i++;
        }
        else if(right[j]< left[i]){
            arr[index]= right[j];
            index++;
            j++;
        }
    }
    while(i<size1){
        arr[index++]= left[i++];
    }
    while(j<size2){
        arr[index++]= right[j++];
    }
}

// ── mergesort: recursively sort karo ────────────────────────────────────────
//   1) s>=e base case
//   2) mid split, dono halves sort
//   3) mergearray se jodo
void mergesort(int *arr, int s, int e){
    if(s>=e){
        return;
    }
    int mid= s+(e-s)/2;
    mergesort(arr,s,mid);
    mergesort(arr,mid+1,e);
    mergearray(arr,s,e);

}

// ── main: merge sort demo ───────────────────────────────────────────────────
int main(){
    int arr[]= {23,2,11,4,1,33,10};
    int size= 7;
    int s=0, e= size-1;
    mergesort(arr,s,e);
    for(int i=0; i<size; i++){
        cout<< arr[i]<< " ";
    }

}
