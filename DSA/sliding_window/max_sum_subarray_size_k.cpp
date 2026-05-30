/*
 * ============================================================================
 * TOPIC    : Sliding Window — Max Sum Subarray of Size K
 * FILE     : max_sum_subarray_size_k.cpp
 * PROBLEM  : Maximum sum of any contiguous subarray of length k
 * LEETCODE : 643 — Maximum Average Subarray I
 * APPROACH : Fixed-size window — add right, remove left
 * COMPLEX  : Time: O(n)  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

int maxSumK(const vector<int> &nums, int k) {
    int sum = 0, best = INT_MIN;
    for (int i = 0; i < (int)nums.size(); i++) {
        sum += nums[i];
        if (i >= k) sum -= nums[i - k];
        if (i >= k - 1) best = max(best, sum);
    }
    return best;
}

int main() {
    vector<int> nums = {2, 1, 5, 1, 3, 2};
    cout << maxSumK(nums, 3) << endl; // 9
    return 0;
}
