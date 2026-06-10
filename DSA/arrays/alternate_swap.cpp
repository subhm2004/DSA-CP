/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : alternate_swap.cpp
 * PROBLEM  : Alternate Swap
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Iterate with two pointers / sliding window / prefix sum.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// ALTERNATE SWAP — har pair (i, i+1) ko swap karo
// ────────────────────────────────────────────────────────────────────────────
// Funda: i = 0, 2, 4... pe jao — adjacent elements swap karo
// Last element ke saath special case handle karo
// COMPLEX: Time O(n)  |  Space O(1)
// ════════════════════════════════════════════════════════════════════════════

// ── printarray: array elements print karo ──────────────────────────────────
//   1) i=0 se size tak loop
//   2) har arr[i] space-separated print
void printarray(int arr[], int size) {
    for(int i=0; i<size; i++) {
        cout<< arr[i] << " ";
    }

}



// ── alterswap: alternate positions pe swap karo ────────────────────────────
//   1) i ko 0, 2, 4... pe badhao (i += 2)
//   2) last element special case — sirf print
//   3) warna arr[i] aur arr[i+1] swap karke print
void alterswap(int arr[], int size) {
    for(int i=0; i<=size-1; i=i+2) {
        if(arr[i] == arr[size-1]) {
                cout<< arr[i]<< " ";
            }
        else {
            int j= i+1; 
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            cout<< arr[i] << " "<< arr[j] << " "; 
        }         
        }
    }


// ── main: pehle print, phir swap karke print ───────────────────────────────
//   1) array declare, printarray se original dikhao
//   2) alterswap call — swapped pairs print
int main() {
    int arr[] = {1,2,3,5,6,7,8 ,9};
    int size = 8;
    cout<< "elements of array are"<< endl;
    printarray(arr, size);
    cout<< endl;
    cout<< "array after swapping are"<< endl;
    alterswap(arr, size);
    cout<< endl;
    return 0;
}
