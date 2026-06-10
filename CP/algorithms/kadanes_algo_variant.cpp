#include <iostream>
#include <vector>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// KADANE'S VARIANT — Max Subarray Sum + Actual Subarray Return
// ────────────────────────────────────────────────────────────────────────────
// Same Kadane logic but track start/end indices of best subarray.
// Params: currSum, maxSum, start/end (best), tempStart (current subarray start)
// Recursion se har index pe decision simulate hoti hai (iterative se equivalent).
// Complexity: O(n) time, O(n) space (recursion stack + subarray vector)
// ════════════════════════════════════════════════════════════════════════════

class Solution
{
public:
    // ── maxSubarrayHelper: recursive Kadane with subarray tracking ────────────
    //   1) base: i == n -> [start..end] ka subarray extract karke return
    //   2) currSum < 0 -> naya subarray i se shuru (tempStart = i)
    //   3) warna currSum += nums[i] — extend current subarray
    //   4) currSum > maxSum -> maxSum, start, end update karo
    //   5) i+1 pe recurse — next element process karo
    pair<int, vector<int>> maxSubarrayHelper(const vector<int> &nums, int i, int currSum, int maxSum, int start, int tempStart, int end)
    {
        if (i == nums.size())
        {
            vector<int> subarray(nums.begin() + start, nums.begin() + end + 1);
            return {maxSum, subarray};
        }

        if (currSum < 0)
        {
            currSum = nums[i];
            tempStart = i; // negative prefix discard — naya start
        }
        else
        {
            currSum += nums[i];
        }

        if (currSum > maxSum)
        {
            maxSum = currSum;
            start = tempStart;
            end = i;
        }

        return maxSubarrayHelper(nums, i + 1, currSum, maxSum, start, tempStart, end);
    }

    // ── maxSubArray: recursion start karo index 1 se ────────────────────────
    //   1) pehla element nums[0] se init — currSum=maxSum=nums[0], start=0
    //   2) helper call karke {sum, subarray} return karo
    pair<int, vector<int>> maxSubArray(vector<int> &nums)
    {
        return maxSubarrayHelper(nums, 1, nums[0], nums[0], 0, 0, 0);
    }
};

int main()
{
    vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    Solution sol;
    auto result = sol.maxSubArray(nums);

    cout << "Maximum Subarray Sum: " << result.first << endl;
    cout << "Subarray: ";
    for (int num : result.second)
    {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
