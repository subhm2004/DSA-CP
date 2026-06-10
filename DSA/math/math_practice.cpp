/*
 * ============================================================================
 * TOPIC    : Math
 * FILE     : math_practice.cpp
 * PROBLEM  : Math Practice
 * ABOUT    : Number theory — GCD, primes, sieve, fast exponentiation
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// ARRAY REARRANGEMENT — negatives left, Dutch National Flag (0,1,2)
// ────────────────────────────────────────────────────────────────────────────
// Funda: two-pointer technique se elements ko sections me baanto
// sortarray — negatives left shift; sortcolor — 0,1,2 sort (LeetCode 75)
// ════════════════════════════════════════════════════════════════════════════

// ── sortarray: negatives ko array ke start me lao ───────────────────────────
//   1) j=0 — next negative ki jagah track karo
//   2) har element pe — negative mila? swap(arr[i], arr[j]), j++
//   3) positives apni jagah rehte hain
void sortarray(int *arr, int size) {
    int j=0;
    for(int i=0; i<size; i++) {
        if(arr[i] < 0) {
            swap(arr[i],arr[j] ); // negative ko left section me daalo
            j++;
        }
    }
}

// ── sortcolor: Dutch National Flag — 0,1,2 sort in-place ───────────────────
//   1) j=0 (0s ke liye), k=size-1 (2s ke liye), i pointer
//   2) arr[i]==0? swap with j, dono aage
//   3) arr[i]==2? swap with k, k peeche — i same (naya element check)
//   4) arr[i]==1? sirf i++ — beech me rehne do
void sortcolor(int arr[], int size) {
    int j=0, k= size-1;
    int i=0;
    while(i <= k) {
        if(arr[i] == 0) {
            swap(arr[i], arr[j]);
            j++;
            i++;
        }
        else if(arr[i] == 2) {
            swap(arr[i], arr[k]);
            k--; // 2 ko end me bhejo — i check dubara
        }
        else {
            i++; // 1 — already sahi section me
        }
    }
}

// ── printarray: array elements print karo ───────────────────────────────────
//   1) i=0 se size-1 tak har element space-separated cout
void printarray(int arr[], int size) {
    for(int i=0; i<size; i++) {
        cout<< arr[i]<< " ";
    }
}

// ── main: sortcolor demo on sample array ─────────────────────────────────────
//   1) arr set karo, sortcolor call, printarray se result dikhao
int main() {
    int arr[] = {1,0,2,2,1,0,1,0,2};
    int size = 9;
    sortcolor(arr,size);
    printarray(arr,size);
}
