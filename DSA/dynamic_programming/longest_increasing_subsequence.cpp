/*
 * ============================================================================
 * TOPIC    : Dynamic Programming — LIS
 * FILE     : longest_increasing_subsequence.cpp
 * PROBLEM  : Length of longest strictly increasing subsequence
 * LEETCODE : 300 — Longest Increasing Subsequence
 * APPROACH : O(n log n) — patience sorting with lower_bound
 * COMPLEX  : Time: O(n log n)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

int lisLength(const vector<int> &nums) {
    vector<int> tail;
    for (int x : nums) {
        auto it = lower_bound(tail.begin(), tail.end(), x);
        if (it == tail.end())
            tail.push_back(x);
        else
            *it = x;
    }
    return tail.size();
}

int main() {
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << lisLength(nums) << endl; // 4
    return 0;
}
