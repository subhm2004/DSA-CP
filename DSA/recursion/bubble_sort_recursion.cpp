/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : bubble_sort_recursion.cpp
 * PROBLEM  : Bubble Sort Recursion
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Swap adjacent out-of-order elements until sorted.
 * COMPLEX  : Time: O(n²)  |  Space: O(1)
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// BUBBLE SORT — Iterative aur Recursive dono versions
// ────────────────────────────────────────────────────────────────────────────
// Adjacent swap — bada element end ki taraf "bubble" hota hai
// bubblesort2: i=pass number, j=current index — recursive nested loops
// Base: i>=size-1 ya j>=size-i-1 -> sorted
// ════════════════════════════════════════════════════════════════════════════

// ── bubblesort: iterative bubble sort ───────────────────────────────────────
//   1) outer loop — n-1 passes
//   2) inner loop — adjacent compare aur swap
//   3) har pass pe largest element end pe
void bubblesort(int arr[], int size) {
    for(int i=0; i<size-1; i++) {
        for(int j=0; j<size-i-1; j++) {
            if(arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

// ── bubblesort2: recursive bubble sort ────────────────────────────────────────
//   1) arr[j]>arr[j+1] -> swap
//   2) j+1 pe recurse (same pass)
//   3) i+1 pe recurse (next pass) — j reset implicitly via call
void bubblesort2(int *arr, int& size, int i, int j) {
    if(i>= size-1 || j>= size-i-1) {
        return;  // saari passes complete
    }
    
    if(arr[j] > arr[j+1]) {
        swap(arr[j], arr[j+1]);
    }
    bubblesort2(arr,size,i,j+1);   // agla adjacent pair
    bubblesort2(arr, size, i+1,j ); // agli pass
}

// ── printarray: sorted array print ────────────────────────────────────────────
void printarray(int *arr, int size) {
    cout<< "sorted array is "<< endl;
    for(int i=0; i < size; i++) {
        cout<< arr[i]<< " ";
    }
}

// ── main: recursive bubble sort demo ────────────────────────────────────────
int main() {
    int arr[] = { 12,1,8,90,4,2};
    int size = 6;
    int i=0, j= 0;
    bubblesort2(arr, size, i, j);
    printarray(arr, size);   
}
