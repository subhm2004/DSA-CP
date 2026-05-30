/*
 * ============================================================================
 * TOPIC    : LIS — Longest Increasing Subsequence
 * FILE     : lis_binary_search_o_nlogn.cpp
 * PROBLEM  : LIS length in O(n log n)
 * APPROACH : Patience sorting — tails[] + lower_bound
 * COMPLEX  : Time: O(n log n)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

int lisLength(const vector<int> &nums) {
    vector<int> tails;

    for (int x : nums) {
        auto it = lower_bound(tails.begin(), tails.end(), x);
        if (it == tails.end())
            tails.push_back(x);
        else
            *it = x;
    }

    return (int)tails.size();
}

int main() {
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << "LIS length (O(n log n)): " << lisLength(nums) << endl;
    return 0;
}
