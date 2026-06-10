/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : binary_search.cpp
 * PROBLEM  : Binary Search
 * LEETCODE : 704 — Binary Search
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Binary search — eliminate half the search space each step.
 * COMPLEX  : Time: O(log n)  |  Space: O(1)
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// BINARY SEARCH — sorted array me element dhundho
// ────────────────────────────────────────────────────────────────────────────
// Funda: lo-hi range me mid nikalo, compare karke half eliminate karo
// arr[mid] < search -> left half chhod, warna right half chhod
// COMPLEX: Time O(log n)  |  Space O(1)
// ════════════════════════════════════════════════════════════════════════════

// ── printarray: array elements ek line me print ────────────────────────────
//   1) loop se har element print
//   2) end me newline
void printarray(int arr[], int size) {
    for(int i=0; i<size; i++) {
        cout<< arr[i]<< " ";
    }
    cout<< endl;
}


// ── binary_search: sorted array me 1-based position dhundho ────────────────
//   1) i=0, j=size-1 — classic two-pointer window
//   2) mid = (i+j)/2, arr[mid] compare karo
//   3) match -> mid+1 return (1-indexed), chhota -> i=mid+1, bada -> j=mid-1
//   4) nahi mila to -1
int binary_search(int arr[], int size, int search) {
    int i=0, j= size -1;    
    while(i<=j) {
        int mid = (i+j)/2;
        if(arr[mid]== search) {
            return mid+1;
            break;
        }
        else if(arr[mid]< search){
            i= mid +1;
        }
        else if(arr[mid] > search) {
            j= mid-1;
        }
    }
    return -1;
}


// ── main: user se search key lo, BS chalao ─────────────────────────────────
//   1) sorted array print karo
//   2) cin se element lo
//   3) 1-based index print karo
int main() {
    int arr[] = { 1,4,5,7,9,11,23,45};
    int size = 8;
    int search;
    cout<< "enter the elemnet to search"<< endl;
    cin>> search;
    printarray(arr,size);
    int key = binary_search(arr, size, search);
    cout<< key<< endl;

}
