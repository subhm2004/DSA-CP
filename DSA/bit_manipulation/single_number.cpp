/*
 * ============================================================================
 * TOPIC    : Bit Manipulation — Single Number
 * FILE     : single_number.cpp
 * PROBLEM  : Every element appears twice except one
 * LEETCODE : 136 — Single Number
 * APPROACH : XOR all elements — pairs cancel to 0
 * COMPLEX  : Time: O(n)  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

int singleNumber(vector<int> &nums) {
    int ans = 0;
    for (int x : nums) ans ^= x;
    return ans;
}

int main() {
    vector<int> nums = {4, 1, 2, 1, 2};
    cout << singleNumber(nums) << endl; // 4
    return 0;
}
