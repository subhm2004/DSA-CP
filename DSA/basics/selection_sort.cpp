/*
 * ============================================================================
 * TOPIC    : Basics
 * FILE     : selection_sort.cpp
 * PROBLEM  : Selection Sort
 * ABOUT    : Fundamental DSA — loops, sorting, strings, character operations
 * APPROACH : Select minimum from unsorted suffix each pass.
 * COMPLEX  : Time: O(n²)  |  Space: O(1)
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// SELECTION SORT — har pass me minimum dhundho, front pe swap
// ────────────────────────────────────────────────────────────────────────────
// Funda: i=0 se — unsorted part me smallest dhundho, arr[i] se swap
// Har round ek element sahi jagah pe — sorted prefix badhta hai
// COMPLEX: Time O(n²)  |  Space O(1)
// ════════════════════════════════════════════════════════════════════════════

// ── printarray: array print karo ─────────────────────────────────────────────
//   1) label + elements print
void printarray(int arr[], int size) {
    cout<< "array is \n";
    for(int i=0; i<size; i++) {
        cout<< arr[i]<< " ";
    }
}


// ── selection: selection sort in-place ─────────────────────────────────────
//   1) outer i — har position pe minimum chahiye
//   2) inner j=i se end — smallest dhundho
//   3) swap(arr[i], smallest) — minimum front pe
//   4) sorted array print
void selection(int arr[],int size ) {
   
    for(int i=0; i< size-1; i++) {
        int smallest = arr[i];
        for(int j = i; j< size; j++) {
        if(arr[j] < smallest) {
            smallest = arr[j];
        }
      }
      swap(arr[i], smallest);
    } 
    cout<< "sorted array is\n"<< endl;
    for(int i=0; i<size; i++) {
        cout<< arr[i]<< " ";
    }
}


// ── main: selection sort demo ────────────────────────────────────────────────
//   1) unsorted array
//   2) selection() call
int main() {
    int arr[] = { 12,4,7,11,56,34,2};
    int size = 7;
    selection(arr,size);
    

}
