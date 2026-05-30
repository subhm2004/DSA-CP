/*
 * ============================================================================
 * TOPIC    : Hash Map — Subarray Sum Equals K
 * FILE     : subarray_sum_equals_k.cpp
 * PROBLEM  : Count subarrays with sum exactly k
 * LEETCODE : 560 — Subarray Sum Equals K
 * APPROACH : Prefix sum + hashmap of prefix frequency
 * COMPLEX  : Time: O(n)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

int subarraySum(vector<int> &nums, int k) {
    unordered_map<int, int> freq;
    freq[0] = 1;
    int sum = 0, ans = 0;
    for (int x : nums) {
        sum += x;
        if (freq.count(sum - k)) ans += freq[sum - k];
        freq[sum]++;
    }
    return ans;
}

int main() {
    vector<int> nums = {1, 1, 1};
    cout << subarraySum(nums, 2) << endl; // 2
    return 0;
}
