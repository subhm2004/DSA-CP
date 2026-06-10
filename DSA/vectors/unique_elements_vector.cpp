/*
 * ============================================================================
 * TOPIC    : Vectors
 * FILE     : unique_elements_vector.cpp
 * PROBLEM  : Unique Elements Vector
 * ABOUT    : STL vector usage and applications
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <vector>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// UNIQUE ELEMENT — XOR se woh element jo baaki sab se alag
// ────────────────────────────────────────────────────────────────────────────
// Funda: XOR property — a^a=0, sab pairs cancel, bacha ek element
// Works jab ek element odd frequency me ho, baaki even
// COMPLEX: Time O(n)  |  Space O(1)
// ════════════════════════════════════════════════════════════════════════════

// ── find: XOR se unique element nikalo ─────────────────────────────────────
//   1) ans=0 se start
//   2) har arr[i] ko ans se XOR — duplicates cancel
//   3) final ans hi unique element
int find(vector<int>arr) {
    int ans=0;
    for(int i=0; i< arr.size(); i++) {
    ans= ans^arr[i];
    }
    return ans;
}


// ── main: user input vector, unique element print ──────────────────────────
//   1) n lo, vector<int> arr(n) banao
//   2) elements input
//   3) find() se unique print
int main() {
    
    int n;
    cout<< "enter number of elements"<< endl;
    cin>> n;
    vector<int> arr(n);
    cout<< "enter the elements in array"<< endl;
    for(int i=0; i<arr.size(); i++) {
        cin>> arr[i];

    }
    int unique= find(arr);
    cout<< "unique element is "<< unique<< endl;
    return 0;

}
