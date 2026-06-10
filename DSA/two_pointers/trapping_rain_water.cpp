/*
 * ============================================================================
 * TOPIC    : Two Pointers — Trapping Rain Water
 * FILE     : trapping_rain_water.cpp
 * PROBLEM  : Total water trapped between bars
 * LEETCODE : 42 — Trapping Rain Water
 * APPROACH : Two pointers with leftMax/rightMax
 * COMPLEX  : Time: O(n)  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// TRAPPING RAIN WATER — Two pointers, O(1) space
// ────────────────────────────────────────────────────────────────────────────
// Pani tab rukta hai jab left aur right dono taraf wall ho
// Chhote side process karo — us side ka max se water add
// h[l] < h[r] -> left side limited by leftMax
// Warna right side limited by rightMax
// ════════════════════════════════════════════════════════════════════════════

// ── trap: total trapped water units ────────────────────────────────────────
//   1) l=0, r=n-1, leftMax=0, rightMax=0, water=0
//   2) h[l] < h[r]: leftMax update, water += leftMax - h[l], l++
//   3) warna: rightMax update, water += rightMax - h[r], r--
//   4) l < r tak repeat, water return
int trap(vector<int> &h) {
    int l = 0, r = h.size() - 1, leftMax = 0, rightMax = 0, water = 0;
    while (l < r) {
        if (h[l] < h[r]) {
            leftMax = max(leftMax, h[l]);
            water += leftMax - h[l]; // is bar pe kitna pani
            l++;
        } else {
            rightMax = max(rightMax, h[r]);
            water += rightMax - h[r];
            r--;
        }
    }
    return water;
}

// ── main: height array -> total water 6 ────────────────────────────────────
int main() {
    vector<int> h = {0,1,0,2,1,0,1,3,2,1,2,1};
    cout << trap(h) << endl; // 6
    return 0;
}
