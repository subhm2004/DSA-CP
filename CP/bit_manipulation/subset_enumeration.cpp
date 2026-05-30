/*
 * ============================================================================
 * TOPIC    : Bit Manipulation — Subset Enumeration
 * FILE     : subset_enumeration.cpp
 * PROBLEM  : Enumerate all subsets of a set {0..n-1}
 * APPROACH : for (sub = mask; sub; sub = (sub - 1) & mask)
 * COMPLEX  : Time: O(2^k) per mask  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

void enumerateSubsets(int mask) {
    for (int sub = mask; sub; sub = (sub - 1) & mask)
        cout << bitset<10>(sub).to_string().substr(32 - mask) << " ";
    cout << endl;
}

int main() {
    int n = 4;
    int fullMask = (1 << n) - 1;

    cout << "All subsets of {0,1,2,3}:\n";
    for (int mask = 0; mask <= fullMask; mask++) {
        cout << "mask " << mask << ": ";
        for (int sub = mask; ; sub = (sub - 1) & mask) {
            cout << sub << " ";
            if (sub == 0)
                break;
        }
        cout << endl;
    }

    cout << "\nSubsets of mask 1011 (bits 0,1,3):\n";
    enumerateSubsets(0b1011);

    return 0;
}
