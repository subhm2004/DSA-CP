/*
 * ============================================================================
 * TOPIC    : Practice
 * FILE     : longest_increasing_subsequence.cpp
 * PROBLEM  : Longest Increasing Subsequence
 * ABOUT    : General practice and mixed problems
 * APPROACH : Include/exclude each element — recursive branching.
 * COMPLEX  : Time: O(2^n)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    
    
    /*
     * solveRE()
     * Purpose : Standard DSA solution for this problem.
     * Params  : vector<int> &arr, int curr, int prev
     * Returns : int
     */
    int solveRE(vector<int> &arr, int curr, int prev)
    {
        if (curr >= arr.size())
            return 0;

        int include = 0;
        if (prev == -1 || arr[curr] > arr[prev])
            include = 1 + solveRE(arr, curr + 1, curr);

        int exclude = solveRE(arr, curr + 1, prev);
        return max(include, exclude);
    }

    
    
    /*
     * solveME()
     * Purpose : Standard DSA solution for this problem.
     * Params  : vector<int> &arr, int curr, int prev, vector<vector<int>> &dp
     * Returns : int
     */
    int solveME(vector<int> &arr, int curr, int prev, vector<vector<int>> &dp)
    {
        if (curr >= arr.size())
            return 0;

        if (dp[curr][prev + 1] != -1)
            return dp[curr][prev + 1];

        int include = 0;
        if (prev == -1 || arr[curr] > arr[prev])
            include = 1 + solveME(arr, curr + 1, curr, dp);

        int exclude = solveME(arr, curr + 1, prev, dp);
        return dp[curr][prev + 1] = max(include, exclude);
    }

    void solveWithPrint(vector<int> &arr, int curr, int prev, vector<vector<int>> &dp,
                        vector<int> &temp, vector<int> &best)
    {
        if (curr >= arr.size())
        {
            if (temp.size() > best.size())
                best = temp;
            return;
        }

        if (prev == -1 || arr[curr] > arr[prev])
        {
            temp.push_back(arr[curr]);
            if (dp[curr][prev + 1] == 1 + solveME(arr, curr + 1, curr, dp))
                solveWithPrint(arr, curr + 1, curr, dp, temp, best);
            temp.pop_back();
        }

        if (dp[curr][prev + 1] == solveME(arr, curr + 1, prev, dp))
            solveWithPrint(arr, curr + 1, prev, dp, temp, best);
    }

    
    
    /*
     * lengthOfLIS_bottomUp()
     * Purpose : DP: longest increasing subsequence ending at i.
     * Params  : vector<int> &nums
     * Returns : int
     */
    int lengthOfLIS_bottomUp(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 0)
            return 0;

        vector<int> dp(n, 1);    // LIS ending at i
        vector<int> prev(n, -1); // store path

        int maxLength = 1;
        int lastIndex = 0;

        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (nums[j] < nums[i] && dp[j] + 1 > dp[i])
                {
                    dp[i] = dp[j] + 1;
                    prev[i] = j;
                }
            }
            if (dp[i] > maxLength)
            {
                maxLength = dp[i];
                lastIndex = i;
            }
        }

        vector<int> ans_LIS;
        while (lastIndex != -1)
        {
            ans_LIS.push_back(nums[lastIndex]);
            lastIndex = prev[lastIndex];
        }
        reverse(ans_LIS.begin(), ans_LIS.end());

        cout << "LIS (Bottom-Up): ";
        for (int num : ans_LIS)
            cout << num << " ";
        cout << "\n";

        return maxLength;
    }

    
    
    /*
     * runAllApproaches()
     * Purpose : Standard DSA solution for this problem.
     * Params  : vector<int> &nums
     * Returns : void
     */
    void runAllApproaches(vector<int> &nums)
    {
        int n = nums.size();
        int curr = 0, prev = -1;

        cout << "Recursive LIS Length: " << solveRE(nums, curr, prev) << endl;

        vector<vector<int>> dp(n, vector<int>(n + 1, -1));
        int len = solveME(nums, curr, prev, dp);
        vector<int> temp, best;
        solveWithPrint(nums, curr, prev, dp, temp, best);

        cout << "Memoized LIS Length: " << len << "\n";
        cout << "LIS (Memoized): ";
        for (int x : best)
            cout << x << " ";
        cout << "\n";

        int dpLen = lengthOfLIS_bottomUp(nums);
        cout << "Bottom-Up LIS Length: " << dpLen << endl;
    }
};



/*
 * main()
 * Purpose : Entry point — demo/test for Longest Increasing Subsequence
 */
int main()
{
    Solution s;
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};

    s.runAllApproaches(nums);
    return 0;
}
