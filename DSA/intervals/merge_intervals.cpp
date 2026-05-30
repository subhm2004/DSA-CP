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

vector<vector<int>> merge(vector<vector<int>> &intervals) {
    sort(intervals.begin(), intervals.end());
    vector<vector<int>> ans;
    for (auto &iv : intervals) {
        if (ans.empty() || iv[0] > ans.back()[1])
            ans.push_back(iv);
        else
            ans.back()[1] = max(ans.back()[1], iv[1]);
    }
    return ans;
}

int main() {
    vector<vector<int>> v = {{1,3},{2,6},{8,10},{15,18}};
    for (auto &iv : merge(v))
        cout << iv[0] << " " << iv[1] << endl;
    return 0;
}
