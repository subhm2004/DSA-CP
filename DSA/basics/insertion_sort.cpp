/*
 * ============================================================================
 * TOPIC    : Basics
 * FILE     : insertion_sort.cpp
 * PROBLEM  : Insertion Sort
 * ABOUT    : Fundamental DSA — loops, sorting, strings, character operations
 * APPROACH : Insert each element into sorted prefix.
 * COMPLEX  : Time: O(n²)  |  Space: O(1)
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// INSERTION SORT — sorted prefix me naya element insert karo
// ────────────────────────────────────────────────────────────────────────────
// Funda: i=1 se — current element ko sorted left part me sahi jagah daalo
// Bade elements right shift, chhoti jagah pe place
// COMPLEX: Time O(n²) worst  |  Space O(1)
// ════════════════════════════════════════════════════════════════════════════

// ── insertionsort: in-place insertion sort ─────────────────────────────────
//   1) i=1 se end — har element sorted prefix me insert
//   2) value = arr[i], j=i-1 se 0 tak — bade elements right shift
//   3) arr[j+1] = value — correct position pe place
void insertionsort(int arr[], int size) {
    for(int i=1; i<size; i++) { 
        int value=i;
       int j= i-1;
       for(; j>=0; j--) {
        if(arr[value]< arr[j]) {
           arr[j+1]= arr[j];
        }
       }
       arr[j+1]= arr[value];
    }
}


// ── printarray: sorted array print ─────────────────────────────────────────
//   1) size tak elements space-separated print
void printarray(int arr[], int size) {
    for(int i=0; i<size; i++) {
        cout<< arr[i]<< " ";
    }
}


// ── main: insertion sort demo ──────────────────────────────────────────────
//   1) unsorted array
//   2) insertionsort + printarray
int main() {
    int arr[] = {10,7,1,6,14,9};
    int size = 6;
    insertionsort(arr,size);
    printarray(arr,size);


}
