/*
 * ============================================================================
 * TOPIC    : Arrays
 * FILE     : array_practice_1.cpp
 * PROBLEM  : Array Practice 1
 * ABOUT    : Array manipulation, searching, sorting, and 2D matrix problems
 * APPROACH : Iterate with two pointers / sliding window / prefix sum.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>

using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// LARGEST ELEMENT — single pass linear scan
// ────────────────────────────────────────────────────────────────────────────
// Funda: largest ko pehle element maan ke poori array traverse karo
// Har step pe max update — koi extra space nahi chahiye
// COMPLEX: Time O(n)  |  Space O(1)
// ════════════════════════════════════════════════════════════════════════════

// ── main: array me sabse bada element dhundho ──────────────────────────────
//   1) arr[] aur size set karo
//   2) largest = arr[0], loop me har element compare
//   3) result print karo
int main(){
    int arr[] = { 1,2,4,5,6,7,8,9,10};
    int size = 9;
    int largest = arr[0];
    
    for(int i=0; i<size; i++) {
        if(arr[i] > largest ) {
            largest = arr[i];
        }

    }
    cout<< "largest element of array is  "<< largest<< endl;
    
    return 0;
}
