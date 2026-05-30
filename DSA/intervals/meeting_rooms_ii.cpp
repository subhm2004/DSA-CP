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
            maxRooms = max(maxRooms, rooms);
            i++;
        } else {
            rooms--;
            j++;
        }
    }
    return maxRooms;
}

int main() {
    vector<vector<int>> v = {{0,30},{5,10},{15,20}};
    cout << minMeetingRooms(v) << endl; // 2
    return 0;
}
