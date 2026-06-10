/*
 * ============================================================================
 * TOPIC    : Greedy — Activity Selection
 * FILE     : activity_selection.cpp
 * PROBLEM  : Max non-overlapping activities by finish time
 * LEETCODE : 435 — Non-overlapping Intervals
 * APPROACH : Sort by end time, greedily pick compatible next
 * COMPLEX  : Time: O(n log n)  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// ACTIVITY SELECTION — Jaldi khatam hone wali pehle lo
// ────────────────────────────────────────────────────────────────────────────
// Intervals (start, end) — end time se sort (greedy classic)
// Pehli activity lo, lastEnd = uska end
// Agli tab lo jab start >= lastEnd (overlap nahi)
// Max non-overlapping count = answer
// ════════════════════════════════════════════════════════════════════════════

// ── maxActivities: max kitni activities select kar sakte ho ───────────────
//   1) end time (second) se sort
//   2) count=0, lastEnd=INT_MIN
//   3) start >= lastEnd -> pick, count++, lastEnd=end
//   4) count return
int maxActivities(vector<pair<int,int>> &act) {
    sort(act.begin(), act.end(), [](auto &a, auto &b) {
        return a.second < b.second; // jaldi finish wali pehle
    });
    int count = 0, lastEnd = INT_MIN;
    for (auto &[s, e] : act)
        if (s >= lastEnd) {
            count++;
            lastEnd = e;
        }
    return count;
}

// ── main: 6 activities -> max 4 non-overlapping ─────────────────────────────
int main() {
    vector<pair<int,int>> act = {{1,3},{2,5},{0,6},{5,7},{8,9},{5,9}};
    cout << maxActivities(act) << endl; // 4
    return 0;
}
