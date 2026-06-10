/*
 * ============================================================================
 * TOPIC    : Two Pointers — Container With Most Water
 * FILE     : container_with_most_water.cpp
 * PROBLEM  : Max area between vertical lines
 * LEETCODE : 11 — Container With Most Water
 * APPROACH : Two pointers from ends — move shorter line inward
 * COMPLEX  : Time: O(n)  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// CONTAINER WITH MOST WATER — Greedy two pointers
// ────────────────────────────────────────────────────────────────────────────
// Area = min(h[l], h[r]) * (r - l) — pani chhote line se limited
// Chhoti line andar move karo — shayad badi mile, width kam hogi
// Badi line move karne se area kabhi improve nahi (width kam, height same/kam)
// O(n) — har pointer ek baar move
// ════════════════════════════════════════════════════════════════════════════

// ── maxArea: maximum water container area ──────────────────────────────────
//   1) l=0, r=n-1, best=0
//   2) area = min(h[l],h[r]) * (r-l), best update
//   3) chhoti height wali pointer andar move
//   4) l < r tak repeat
int maxArea(vector<int> &h) {
    int l = 0, r = h.size() - 1, best = 0;
    while (l < r) {
        best = max(best, min(h[l], h[r]) * (r - l));
        if (h[l] < h[r]) l++; // chhoti line ko andar bhejo
        else r--;
    }
    return best;
}

// ── main: height array -> max area 49 ────────────────────────────────────────
int main() {
    vector<int> h = {1,8,6,2,5,4,8,3,7};
    cout << maxArea(h) << endl; // 49
    return 0;
}
