/*
 * ============================================================================
 * TOPIC    : Dynamic Programming — Maximum Product Subarray
 * FILE     : max_product_subarray.cpp
 * PROBLEM  : Largest product of contiguous subarray
 * LEETCODE : 152 — Maximum Product Subarray
 * APPROACH : Track maxProd and minProd (negative flip)
 * COMPLEX  : Time: O(n)  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

int maxProduct(const vector<int> &nums) {
    int best = nums[0], curMax = nums[0], curMin = nums[0];
    for (int i = 1; i < (int)nums.size(); i++) {
        if (nums[i] < 0) swap(curMax, curMin);
        curMax = max(nums[i], curMax * nums[i]);
        curMin = min(nums[i], curMin * nums[i]);
        best = max(best, curMax);
    }
    return best;
}

int main() {
    vector<int> nums = {2, 3, -2, 4};
    cout << maxProduct(nums) << endl; // 6
    return 0;
}
