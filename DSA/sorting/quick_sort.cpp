/*
 * ============================================================================
 * TOPIC    : Sorting
 * FILE     : quick_sort.cpp
 * PROBLEM  : Quick Sort
 * LEETCODE : 912 — Sort an Array
 * ABOUT    : Comparison-based sorting algorithms
 * APPROACH : Partition around pivot; recursively sort left and right.
 * COMPLEX  : Time: O(n log n) avg  |  Space: O(log n)
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// QUICK SORT — Partition based in-place sort
// ────────────────────────────────────────────────────────────────────────────
// Pivot choose, uske left chhote right bade
// Recursively sort [s,p-1] aur [p+1,e]
// Average O(n log n), worst O(n²) — pivot choice matter karta hai
// ════════════════════════════════════════════════════════════════════════════

// ── partition: pivot ko sahi index pe fix ───────────────────────────────────
//   1) count kitne <= pivot
//   2) pivot swap to s+count
//   3) i,j se galat elements swap
int partition(int *arr, int s, int e){
    int pivotindex= s;
    int pivotelement= arr[s];
    int count=0;
    for(int i=s+1; i<=e; i++){
        if(arr[i]<=pivotelement){
            count++;
        }
    }
    int rightindex= s+count;
    swap(arr[pivotindex], arr[rightindex]);
    pivotindex= rightindex;
    int i=s;
    int j=e;
    while(i<pivotindex && j>pivotindex ){
        if(arr[i]< pivotelement){
            i++;
        }
        if(arr[j]> pivotelement){
            j--;
        }
    }
        if(i<pivotindex && j> pivotindex){
            swap(arr[i], arr[j]);
        }
    
    return pivotindex;
}

// ── quicksort: partition + recursive sort ─────────────────────────────────────
void quicksort(int* arr, int s, int e){
    if(s>=e){
        return ;
    }
    int index= partition(arr,s,e);
    quicksort(arr,s,index-1);
    quicksort(arr,index+1,e);
}

// ── main: quick sort demo ───────────────────────────────────────────────────
int main(){
    int arr[]= {12,11,1,56,34,23,22};
    int size= 7;
    int s=0, e= size-1;
    quicksort(arr,s,e);
    for(int i=0; i< size; i++){
        cout<< arr[i]<< " ";
    }
}
