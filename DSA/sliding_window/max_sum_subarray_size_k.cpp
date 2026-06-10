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

// ════════════════════════════════════════════════════════════════════════════
// FIXED WINDOW SIZE K — Sum maintain karke max nikalo
// ────────────────────────────────────────────────────────────────────────────
// Window [i-k+1 .. i] jab i >= k-1
// Har step: nums[i] add, nums[i-k] subtract (purana left hatao)
// best = max running sum jab window size k ho
// O(n) single pass — brute O(n*k) se better
// ════════════════════════════════════════════════════════════════════════════

// ── maxSumK: size-k subarray ka max sum ────────────────────────────────────
//   1) sum=0, best=INT_MIN
//   2) i pe nums[i] add karo
//   3) i>=k: sum -= nums[i-k] (left element bahar)
//   4) i>=k-1: best = max(best, sum)
int maxSumK(const vector<int> &nums, int k) {
    int sum = 0, best = INT_MIN;
    for (int i = 0; i < (int)nums.size(); i++) {
        sum += nums[i];
        if (i >= k) sum -= nums[i - k]; // fixed window — purana hatao
        if (i >= k - 1) best = max(best, sum);
    }
    return best;
}

// ── main: nums, k=3 -> max sum 9 ───────────────────────────────────────────
int main() {
    vector<int> nums = {2, 1, 5, 1, 3, 2};
    cout << maxSumK(nums, 3) << endl; // 9
    return 0;
}
