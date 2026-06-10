/*
 * ============================================================================
 * TOPIC    : Greedy — Meeting Rooms (can attend all?)
 * FILE     : meeting_rooms.cpp
 * PROBLEM  : Any overlap in meeting intervals?
 * LEETCODE : 252 — Meeting Rooms
 * APPROACH : Sort by start, check start[i] >= end[i-1]
 * COMPLEX  : Time: O(n log n)  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// MEETING ROOMS I — Kya saari meetings attend ho sakti hain?
// ────────────────────────────────────────────────────────────────────────────
// Intervals sort by start time
// Agar kisi meeting ka start < pichli ka end -> overlap -> NO
// Sab non-overlapping -> YES attend kar sakte ho
// Greedy: sort se adjacent check kaafi hai
// ════════════════════════════════════════════════════════════════════════════

// ── canAttendMeetings: overlap hai to false ────────────────────────────────
//   1) intervals start se sort
//   2) i=1 se: start[i] < end[i-1] -> overlap, return false
//   3) sab check pass -> return true
bool canAttendMeetings(vector<vector<int>> &intervals) {
    sort(intervals.begin(), intervals.end());
    for (int i = 1; i < (int)intervals.size(); i++)
        if (intervals[i][0] < intervals[i - 1][1])
            return false; // pehli meeting khatam hone se pehle nayi shuru
    return true;
}

// ── main: {{0,30},{5,10},{15,20}} overlap -> NO ───────────────────────────
int main() {
    vector<vector<int>> intervals = {{0,30},{5,10},{15,20}};
    cout << (canAttendMeetings(intervals) ? "YES" : "NO") << endl; // NO
    return 0;
}
