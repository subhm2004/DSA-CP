/*
 * ============================================================================
 * TOPIC    : Intervals — Merge Intervals
 * FILE     : merge_intervals.cpp
 * PROBLEM  : Merge all overlapping intervals
 * LEETCODE : 56 — Merge Intervals
 * APPROACH : Sort by start; extend or push new interval
 * COMPLEX  : Time: O(n log n)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// MERGE INTERVALS — Sort by start, greedy merge
// ────────────────────────────────────────────────────────────────────────────
// Start se sort — overlapping adjacent ban jaate hain
// Agar current start > last end -> naya interval push
// Warna last interval ka end extend karo max se
// Classic interval merging pattern
// ════════════════════════════════════════════════════════════════════════════

// ── merge: overlapping intervals merge karke return ────────────────────────
//   1) intervals start se sort
//   2) har iv: ans khali ya iv.start > last.end -> naya push
//   3) warna ans.back().end = max(last.end, iv.end) — extend
//   4) merged ans return
vector<vector<int>> merge(vector<vector<int>> &intervals) {
    sort(intervals.begin(), intervals.end());
    vector<vector<int>> ans;
    for (auto &iv : intervals) {
        if (ans.empty() || iv[0] > ans.back()[1])
            ans.push_back(iv); // overlap nahi — naya interval
        else
            ans.back()[1] = max(ans.back()[1], iv[1]); // merge extend
    }
    return ans;
}

// ── main: 4 intervals merge demo ───────────────────────────────────────────
int main() {
    vector<vector<int>> v = {{1,3},{2,6},{8,10},{15,18}};
    for (auto &iv : merge(v))
        cout << iv[0] << " " << iv[1] << endl;
    return 0;
}
