/*
 * ============================================================================
 * TOPIC    : Intervals — Insert Interval
 * FILE     : insert_interval.cpp
 * PROBLEM  : Insert new interval and merge overlaps
 * LEETCODE : 57 — Insert Interval
 * APPROACH : Add non-overlapping before; merge middle; append rest
 * COMPLEX  : Time: O(n)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> insert(vector<vector<int>> &intervals, vector<int> &newInterval) {
    vector<vector<int>> ans;
    int i = 0, n = intervals.size();

    while (i < n && intervals[i][1] < newInterval[0])
        ans.push_back(intervals[i++]);

    while (i < n && intervals[i][0] <= newInterval[1]) {
        newInterval[0] = min(newInterval[0], intervals[i][0]);
        newInterval[1] = max(newInterval[1], intervals[i][1]);
        i++;
    }
    ans.push_back(newInterval);

    while (i < n) ans.push_back(intervals[i++]);
    return ans;
}

int main() {
    vector<vector<int>> intervals = {{1,3},{6,9}};
    vector<int> ni = {2,5};
    for (auto &iv : insert(intervals, ni))
        cout << iv[0] << " " << iv[1] << endl;
    return 0;
}
