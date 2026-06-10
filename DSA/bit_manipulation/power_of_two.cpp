/*
 * ============================================================================
 * TOPIC    : Bit Manipulation — Power of Two
 * FILE     : power_of_two.cpp
 * PROBLEM  : Check if n is a power of 2
 * LEETCODE : 231 — Power of Two
 * APPROACH : n > 0 && (n & (n-1)) == 0
 * COMPLEX  : Time: O(1)  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// POWER OF TWO — n = 2^k hai ya nahi?
// ────────────────────────────────────────────────────────────────────────────
// Power of 2 ka binary: sirf ek bit set (e.g. 8 = 1000)
// n-1 se AND: rightmost set bit clear, baaki same
// n power of 2 -> n & (n-1) = 0 (sirf ek bit tha)
// n <= 0 -> false (0 aur negative power of 2 nahi)
// ════════════════════════════════════════════════════════════════════════════

// ── isPowerOfTwo: n 2 ki power hai? ───────────────────────────────────────
//   1) n > 0 check — 0/negative invalid
//   2) n & (n-1) == 0 — sirf ek set bit?
//   3) dono true -> power of 2
//   4) warna false return
bool isPowerOfTwo(int n) {
    return n > 0 && (n & (n - 1)) == 0;
}

int main() {
    cout << isPowerOfTwo(16) << " " << isPowerOfTwo(18) << endl; // 1 0
    return 0;
}
