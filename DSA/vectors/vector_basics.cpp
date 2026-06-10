/*
 * ============================================================================
 * TOPIC    : Vectors
 * FILE     : vector_basics.cpp
 * PROBLEM  : Vector Basics
 * ABOUT    : STL vector usage and applications
 * APPROACH : Standard DSA solution for this problem.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <vector>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// VECTOR STL BASICS — push_back, pop_back, size, capacity
// ────────────────────────────────────────────────────────────────────────────
// Funda: dynamic array — size badhta hai, capacity double hoti hai
// Initialization: {}, (n, val), push_back — teen tarike
// COMPLEX: push_back amortized O(1)  |  Space O(capacity)
// ════════════════════════════════════════════════════════════════════════════

// ── main: vector operations demo ─────────────────────────────────────────────
//   1) empty vector — push_back 5,7; size/capacity print
//   2) pop_back — last element hatao
//   3) brace init brr{10,20,30} aur fill construct crr(10,-2) demo
int main() {
    vector<int> arr;
    arr.push_back(5);
    arr.push_back(7);
    cout<< arr.size() << endl;
    cout<< arr.capacity() << endl;
    
    for(int i=0; i< arr.size(); i++) {
        cout<< arr[i]<< " ";
    }
    cout<< "\n";
    arr.pop_back();
    for(int i=0; i< arr.size(); i++) {
        cout<< arr[i]<< " ";
    }
    cout<< endl;
    cout<< arr.size() << endl;
    cout<< arr.capacity() << endl;
    vector<int> brr{10, 20, 30};
    for(int i=0; i< brr.size(); i++) {
        cout<< brr[i] << " ";
    }
    cout<< "\n";
    vector<int> crr(10, -2);
    for(int i=0; i< crr.size(); i++) {
        cout<< crr[i]<< " ";
    }
    return 0;

}
