/*
 * ============================================================================
 * TOPIC    : Basics
 * FILE     : sorting_practice_2.cpp
 * PROBLEM  : Sorting Practice 2
 * ABOUT    : Fundamental DSA — loops, sorting, strings, character operations
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// SELECTION SORT PRACTICE — minimum dhundho, swap karo
// ────────────────────────────────────────────────────────────────────────────
// Funda: har i ke liye i+1 se end me minimum dhundho
// swap(arr[i], min) — sorted prefix grow karta hai
// main me inline bhi likha — function aur inline dono demo
// COMPLEX: Time O(n²)  |  Space O(1)
// ════════════════════════════════════════════════════════════════════════════

// ── selection: selection sort function ─────────────────────────────────────
//   1) i=0 se size-2 — har position pe min chahiye
//   2) j=i+1 se scan — minimum dhundho
//   3) swap(arr[i], min)
void selection(int arr[] , int size) {    
    for(int i=0; i<size-1; ) {
        int min= arr[i];
        for(int j=i+1; j<size; j++) {
        if(arr[j] < min) {
            min= arr[j];
        }
        }
        swap(arr[i], min);
        i++;        
    }    
}


// ── printarray: sorted result print ──────────────────────────────────────────
//   1) elements space-separated print
void printarray(int arr[], int size) {
    cout<< "sorted array is\n";
    for(int i=0; i<size; i++) {
        cout<< arr[i]<< "  ";
    }
}


// ── main: inline selection sort + print ────────────────────────────────────
//   1) array declare
//   2) main me directly selection sort loop
//   3) printarray se result
int main() {
    int arr[] = { 12,3,1,9,5,7};
    int size = 6;
     for(int i=0; i<size-1;i++ ) {
        int min= arr[i];
        for(int j=i+1; j<size; j++) {
        if(arr[j] < min) {
            min= arr[j];
        }
        }
        swap(arr[i], min);      
    }    
    printarray(arr, size);
}
