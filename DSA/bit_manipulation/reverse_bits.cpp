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

// ════════════════════════════════════════════════════════════════════════════
// REVERSE BITS — 32-bit number ke bits ulte order mein
// ────────────────────────────────────────────────────────────────────────────
// Har iteration: ans ko left shift, n ka LSB ans mein OR
// n ko right shift — next bit extract karo
// 32 baar repeat — poora 32-bit reverse ho jata hai
// ════════════════════════════════════════════════════════════════════════════

// ── reverseBits: n ke 32 bits reverse karo ────────────────────────────────
//   1) ans = 0 se start
//   2) 32 iterations: ans <<= 1 (result mein jagah banao)
//   3) ans |= (n & 1) — n ka last bit ans mein daalo
//   4) n >>= 1 — agla bit nikaalo
//   5) ans return — reversed 32-bit value
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
