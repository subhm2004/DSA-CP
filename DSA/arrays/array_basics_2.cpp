/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : array_basics_2.cpp
 * PROBLEM  : Array Basics 2
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Iterate with two pointers / sliding window / prefix sum.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// LINEAR SEARCH — array me element dhundho
// ────────────────────────────────────────────────────────────────────────────
// Funda: har element ko ek-ek karke key se compare karo
// Mil gaya to true, poora scan ho gaya to false
// COMPLEX: Time O(n)  |  Space O(1)
// ════════════════════════════════════════════════════════════════════════════

// ── search: linear search se key dhundho ───────────────────────────────────
//   1) i=0 se start karo, har index pe jao
//   2) arr[i] == key ho to turant true return
//   3) loop khatam — element nahi mila to false
bool search(int arr[], int size,int key) {
    for(int i=0; i<size; i++) {
        if(arr[i]== key) {
            return true;
        }

    }
    return false;

}


// ── main: user se key lo aur search result print karo ──────────────────────
//   1) array declare karo, size pass karo
//   2) cin se key input lo
//   3) found / not found message print karo
int main() {
    int arr[] = {2,0,5,1,7} ;
    int size = 5;
    int key;
    cout<< "enter the element to find"<< endl;
    cin>> key;
    bool ans = search(arr, size, key);
    if(ans == true) {
        cout<< "element found"<< endl;
    }
    else {
        cout<< "not found"<< endl;
    }
    return 0;


}
