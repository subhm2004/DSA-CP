/*
 * ============================================================================
 * TOPIC    : Vectors
 * FILE     : pair_sum_vector.cpp
 * PROBLEM  : Pair Sum Vector
 * ABOUT    : STL vector usage and applications
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <vector>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// PAIR SUM — vector me do elements jinka sum = target
// ────────────────────────────────────────────────────────────────────────────
// Funda: nested loop — har pair (i,j) check karo j=i+1 se
// arr[i]+arr[j]==sum ho to pair print — brute force O(n²)
// COMPLEX: Time O(n²)  |  Space O(n) for vector
// ════════════════════════════════════════════════════════════════════════════

// ── main: vector input, pair with sum 9 dhundho ──────────────────────────
//   1) n lo, vector<int> arr(n) se dynamic array banao
//   2) elements input karo
//   3) nested loop i,j — sum==9 wale pairs print
int main() {
    int n;
    cout<< "enter size of array"<< endl;
    cin>> n;
    vector<int> arr(n);
    cout<< "enter the elements of dynamic array"<< endl;
    for(int i=0; i< arr.size(); i++) {
        cin>> arr[i];
    }
    int sum =9;
    for(int i=0; i<n-1; i++) {
        for(int j= i+1; j<n; j++) {
            if(arr[i] + arr[j] == sum) {
                cout<< "pair with sum 9 is " << arr[i]<< " "<< arr[j]<< endl;
            }

        }
    }
   
}
