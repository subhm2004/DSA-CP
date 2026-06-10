#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// KADANE'S ALGORITHM — Maximum Subarray Sum
// ────────────────────────────────────────────────────────────────────────────
// Idea: running sum rakho. Agar sum negative ho jaye to discard karo (0 se restart).
//       Har step pe global max update karo.
// State: sum = current subarray ka sum, maxi = ab tak ka best answer
// Complexity: O(n) time, O(1) space
// ════════════════════════════════════════════════════════════════════════════

class Solution {
public:
    Solution() {
        ios_base::sync_with_stdio(false);
    }

    // ── maxSubarraySumHelper: Kadane's core loop ──────────────────────────────
    //   1) sum me nums[i] add karo — current subarray extend ho raha hai
    //   2) maxi = max(maxi, sum) — best answer update
    //   3) agar sum < 0 -> sum = 0 (negative prefix ka koi fayda nahi)
    //   4) loop ke baad maxi return — maximum subarray sum
    int maxSubarraySumHelper(vector<int>& nums) {
        int n = nums.size();
        int maxi = INT_MIN;
        int sum = 0;

        for (int i = 0; i < n; i++) {
            sum += nums[i];
            maxi = max(maxi, sum);
            if (sum < 0) {
                sum = 0; // negative sum discard — naya subarray yahan se shuru hoga
            }
        }
        return maxi;
    }

    // ── maxSubArray: LeetCode wrapper ─────────────────────────────────────────
    //   1) helper ko call karo aur result return karo
    int maxSubArray(vector<int>& nums) {
       return maxSubarraySumHelper(nums);
    }
};

int main() {
    vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    Solution sol;
    cout << sol.maxSubArray(nums) << endl; // expected: 6  [4,-1,2,1]
    return 0;
}
