/*
 * ============================================================================
 * TOPIC    : Intervals — Meeting Rooms II
 * FILE     : meeting_rooms_ii.cpp
 * PROBLEM  : Minimum conference rooms required
 * LEETCODE : 253 — Meeting Rooms II
 * APPROACH : Sort starts & ends; two pointers count overlap
 * COMPLEX  : Time: O(n log n)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// MEETING ROOMS II — Min rooms = max simultaneous meetings
// ────────────────────────────────────────────────────────────────────────────
// Start aur end arrays alag sort karo
// start[i] < end[j] -> nayi meeting shuru, rooms++, i++
// warna meeting khatam, rooms--, j++
// maxRooms = peak overlap count
// Chronological order simulate — greedy two pointers
// ════════════════════════════════════════════════════════════════════════════

// ── minMeetingRooms: minimum conference rooms chahiye ──────────────────────
//   1) start[] aur end[] alag arrays, sort
//   2) i,j pointers — start vs end compare
//   3) start < end -> rooms++ (overlap badha), i++
//   4) warna rooms-- (ek meeting khatam), j++
//   5) maxRooms return
int minMeetingRooms(vector<vector<int>> &intervals) {
    vector<int> start, end;
    for (auto &iv : intervals) {
        start.push_back(iv[0]);
        end.push_back(iv[1]);
    }
    sort(start.begin(), start.end());
    sort(end.begin(), end.end());

    int rooms = 0, maxRooms = 0, i = 0, j = 0;
    while (i < (int)start.size()) {
        if (start[i] < end[j]) {
            rooms++;
            maxRooms = max(maxRooms, rooms); // peak simultaneous
            i++;
        } else {
            rooms--;
            j++;
        }
    }
    return maxRooms;
}

// ── main: 3 intervals -> 2 rooms ───────────────────────────────────────────
int main() {
    vector<vector<int>> v = {{0,30},{5,10},{15,20}};
    cout << minMeetingRooms(v) << endl; // 2
    return 0;
}
