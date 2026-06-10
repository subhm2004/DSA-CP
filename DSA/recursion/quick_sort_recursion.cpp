/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : quick_sort_recursion.cpp
 * PROBLEM  : Quick Sort Recursion
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Partition around pivot; recursively sort left and right.
 * COMPLEX  : Time: O(n log n) avg  |  Space: O(log n)
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// QUICK SORT (Recursion) — Partition + recursive sort
// ────────────────────────────────────────────────────────────────────────────
// Pivot choose (arr[s]) — count se sahi position nikalo
// Left me chhote, right me bade — swap karke fix
// Recurse left [s, p-1] aur right [p+1, e]
// ════════════════════════════════════════════════════════════════════════════

// ── partition: pivot ki sahi jagah fix karo ─────────────────────────────────
//   1) pivot = arr[s], count kitne <= pivot
//   2) pivot ko s+count pe swap — sahi index
//   3) i,j se left/right partition — galat jagah wale swap
//   4) pivot index return
int partition(int* arr, int s, int e ) {
    int pivotindex = s;
    int pivotelement = arr[s];
    int count =0;
    for(int i=s+1; i<=e; i++) {
        if(arr[i] <= pivotelement) {
            count++;
        }
    }
    int rightindex = s + count;
    swap(arr[pivotindex], arr[rightindex]);
    pivotindex = rightindex;
    int i=s, j= e;
    while(i< pivotindex && j> pivotindex) {
        while(arr[i] < pivotelement) {
            i++;
        }
        while(arr[j] > pivotelement) {
            j--;
        }
        if(i< pivotindex && j> pivotindex) {
            swap(arr[i], arr[j]);
        }
    }
    return pivotindex;
}

// ── quicksort: partition ke baad dono halves sort ───────────────────────────
//   1) s>=e -> base case
//   2) p = partition — pivot fix
//   3) left aur right recursively sort
void quicksort(int* arr, int s, int e) {
    if(s>=e) {
        return;
    }
    int p= partition(arr, s, e);
    quicksort(arr, s, p-1);   // left of pivot
    quicksort(arr, p+1, e);   // right of pivot
}

// ── main: quick sort demo ───────────────────────────────────────────────────
int main() {
    int arr[] = {8,1,3,4,20,50,30};
    int size = 7;
    int s=0, e = size-1;
    quicksort(arr, s, e);
    cout<< "sorted array is "<< endl;
    for(int i=0; i<size; i++) {
        cout<< arr[i] << " ";
    } cout<< endl;
}
