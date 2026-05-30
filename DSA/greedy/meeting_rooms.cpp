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

bool canAttendMeetings(vector<vector<int>> &intervals) {
    sort(intervals.begin(), intervals.end());
    for (int i = 1; i < (int)intervals.size(); i++)
        if (intervals[i][0] < intervals[i - 1][1])
            return false;
    return true;
}

int main() {
    vector<vector<int>> intervals = {{0,30},{5,10},{15,20}};
    cout << (canAttendMeetings(intervals) ? "YES" : "NO") << endl; // NO
    return 0;
}
