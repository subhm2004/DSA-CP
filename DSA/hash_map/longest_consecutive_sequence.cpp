/*
 * ============================================================================
 * TOPIC    : Hash Map — Longest Consecutive Sequence
 * FILE     : longest_consecutive_sequence.cpp
 * PROBLEM  : Length of longest consecutive elements run
 * LEETCODE : 128 — Longest Consecutive Sequence
 * APPROACH : Hash set — start only from sequence minimum
 * COMPLEX  : Time: O(n)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// LONGEST CONSECUTIVE — Set se O(n) sequence length
// ────────────────────────────────────────────────────────────────────────────
// Sirf sequence ke START se count karo (x-1 set me nahi)
// x, x+1, x+2... jab tak set me hain — len badhao
// Har element max ek baar visit — total O(n)
// Sort O(n log n) ki jagah set trick
// ════════════════════════════════════════════════════════════════════════════

// ── longestConsecutive: sabse lambi consecutive chain ki length ────────────
//   1) saare nums unordered_set me daalo
//   2) har x ke liye: agar x-1 set me hai -> skip (start nahi hai)
//   3) x sequence ka start -> len=1, x+len jab tak set me
//   4) best = max(best, len)
int longestConsecutive(vector<int> &nums) {
    unordered_set<int> st(nums.begin(), nums.end());
    int best = 0;
    for (int x : st) {
        if (st.count(x - 1)) continue; // beech ka element — skip
        int len = 1;
        while (st.count(x + len)) len++; // aage badhte jao
        best = max(best, len);
    }
    return best;
}

// ── main: {100,4,200,1,3,2} -> consecutive 1,2,3,4 len=4 ──────────────────
int main() {
    vector<int> nums = {100, 4, 200, 1, 3, 2};
    cout << longestConsecutive(nums) << endl; // 4
    return 0;
}
