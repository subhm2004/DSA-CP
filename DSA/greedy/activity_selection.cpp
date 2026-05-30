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

int maxActivities(vector<pair<int,int>> &act) {
    sort(act.begin(), act.end(), [](auto &a, auto &b) {
        return a.second < b.second;
    });
    int count = 0, lastEnd = INT_MIN;
    for (auto &[s, e] : act)
        if (s >= lastEnd) {
            count++;
            lastEnd = e;
        }
    return count;
}

int main() {
    vector<pair<int,int>> act = {{1,3},{2,5},{0,6},{5,7},{8,9},{5,9}};
    cout << maxActivities(act) << endl; // 4
    return 0;
}
