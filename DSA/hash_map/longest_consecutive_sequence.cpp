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

int longestConsecutive(vector<int> &nums) {
    unordered_set<int> st(nums.begin(), nums.end());
    int best = 0;
    for (int x : st) {
        if (st.count(x - 1)) continue;
        int len = 1;
        while (st.count(x + len)) len++;
        best = max(best, len);
    }
    return best;
}

int main() {
    vector<int> nums = {100, 4, 200, 1, 3, 2};
    cout << longestConsecutive(nums) << endl; // 4
    return 0;
}
