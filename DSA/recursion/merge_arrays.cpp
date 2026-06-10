/*
 * ============================================================================
 * TOPIC    : Recursion
 * FILE     : merge_arrays.cpp
 * PROBLEM  : Merge Arrays
 * ABOUT    : Recursion, backtracking, and recursive sorting/searching
 * APPROACH : Base case + solve smaller subproblem recursively.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <vector>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// MERGE TWO SORTED ARRAYS — Two-pointer technique
// ────────────────────────────────────────────────────────────────────────────
// arr1 aur arr2 sorted — chhota element ans me daalo
// Jab ek khatam -> baaki copy karo
// Merge sort ka merge step — O(n+m) time
// ════════════════════════════════════════════════════════════════════════════

// ── main: do sorted arrays merge karke print ────────────────────────────────
//   1) i, j pointers — dono arrays ke start
//   2) chhota element ans[k] me, pointer aage
//   3) leftover elements copy karo
int main() {
    int arr1[] = {2,4,6};
    int size1= 3;
    int arr2[] = {3,5,7,9,11};
    int size2 = 5;
    int ans[sizeof(arr1) + sizeof(arr2)];
    int i=0, j=0, k=0;
    while(i<size1 && j<size2 ) {
    if(arr1[i]< arr2[j]) {
        ans[k] = arr1[i];
        i++;
    }
    else {
        ans[k] = arr2[j];
        j++;
    }
    k++;
    }
    while(i< size1) {  // arr1 ka baaki hissa
        ans[k] = arr1[i];
        i++;
        k++;
    }
    while(j< size2) {  // arr2 ka baaki hissa
        ans[k] = arr2[j];
        j++;
        k++;
    }

    for(int i=0; i< (size1 + size2); i++) {
        cout<< ans[i]<< "  ";
    }

}
