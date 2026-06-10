/*
 * ============================================================================
 * TOPIC    : Basics
 * FILE     : sorting_practice_3.cpp
 * PROBLEM  : Sorting Practice 3
 * ABOUT    : Fundamental DSA — loops, sorting, strings, character operations
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// INSERTION SORT PRACTICE — sorted prefix me insert
// ────────────────────────────────────────────────────────────────────────────
// Funda: i=1 se — value=arr[i] uthao, left me sahi jagah dhundho
// Bade elements right shift, break jab arr[j] <= value
// COMPLEX: Time O(n²)  |  Space O(1)
// ════════════════════════════════════════════════════════════════════════════

// ── insertion: insertion sort in-place ─────────────────────────────────────
//   1) i=1 se — har element sorted left part me insert
//   2) value=arr[i], j=i-1 se 0 — bade elements shift right
//   3) arr[j]<=value ya j<0 pe break, arr[j+1]=value
void insertion(int arr[], int size) {
    for(int i=1; i<size; i++) {
        int value = arr[i];
        int j= i-1;
        for(; j>=0; j--) {
            if(arr[j] > value) {
                arr[j+1] = arr[j];  // right shift — jagah banao
            }
            else {
                break;
            }
            
           
        }
        arr[j+1]= value;
    }
}


// ── printarray: sorted array print ───────────────────────────────────────────
//   1) size tak elements print
void printarray(int arr[], int size) {
    for(int i=0; i<size; i++) {
        cout<< arr[i]<< " ";
    }
}


// ── main: insertion sort demo ──────────────────────────────────────────────
//   1) unsorted array
//   2) insertion() + printarray()
int main() {
    int arr[] = {10,7,1,6,14,9};
    int size = 6;
    insertion(arr,size);
    printarray(arr,size);
}
