/*
 * ============================================================================
 * TOPIC    : Bit Manipulation — Reverse Bits
 * FILE     : reverse_bits.cpp
 * PROBLEM  : Reverse bits of a 32-bit unsigned integer
 * LEETCODE : 190 — Reverse Bits
 * APPROACH : Extract LSB, shift into result
 * COMPLEX  : Time: O(32)  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

uint32_t reverseBits(uint32_t n) {
    uint32_t ans = 0;
    for (int i = 0; i < 32; i++) {
        ans <<= 1;
        ans |= (n & 1);
        n >>= 1;
    }
    return ans;
}

int main() {
    cout << reverseBits(43261596) << endl;
    return 0;
}
