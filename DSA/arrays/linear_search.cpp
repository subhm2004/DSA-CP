/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : linear_search.cpp
 * PROBLEM  : Linear Search
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Iterate with two pointers / sliding window / prefix sum.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// LINEAR SEARCH — user input array me element dhundho
// ────────────────────────────────────────────────────────────────────────────
// Funda: start se end tak ek-ek element check karo
// Match mila to position print + break, nahi to not found
// COMPLEX: Time O(n)  |  Space O(1)
// ════════════════════════════════════════════════════════════════════════════

// ── main: VLA array pe linear search ───────────────────────────────────────
//   1) n lo, array input karo
//   2) search element lo
//   3) flag se track — mila to index print, warna not found
int main() {
    int n;
    cout<< "enter number of elements in array"<< endl;
    cin>> n;
    int arr[n];
    cout<< "enter the elements of array"<< endl;
    for(int i=0; i<n; i++) {
        cin>> arr[i];
    }
    int search;
    cout<< "enter the element to search"<< endl;
    cin>> search;
    
   int flag=0;
    for(int i=0; i<n; i++) {
        if(arr[i]== search) {
            flag =1;
            cout<< "element is found at position"<< i<< endl;
            break;  // mil gaya — aage scan ki zaroorat nahi
        }

    }
    if(flag ==0) {
        cout<< "element not found"<< endl;

    }
    
}
