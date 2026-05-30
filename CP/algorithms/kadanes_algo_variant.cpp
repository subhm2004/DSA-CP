#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    // Recursive function jo max subarray sum aur subarray return karega
    pair<int, vector<int>> maxSubarrayHelper(const vector<int> &nums, int i, int currSum, int maxSum, int start, int tempStart, int end)
    {
        if (i == nums.size())
        {
            vector<int> subarray(nums.begin() + start, nums.begin() + end + 1); // Max sum wala subarray extract karna
            return {maxSum, subarray};                                          // Max sum aur subarray return karna
        }

        // Agar naye element se start karna zyada behtar hai toh wahi choose karo
        if (currSum < 0)
        {
            currSum = nums[i];
            tempStart = i; // Naya subarray ka start update karna
        }
        else
        {
            currSum += nums[i]; // Otherwise, pehle wale sum me add karna
        }

        // Agar naye sum se max sum update hota hai toh start aur end update karo
        if (currSum > maxSum)
        {
            maxSum = currSum;
            start = tempStart;
            end = i;
        }

        // Recursion call karo next index ke liye
        return maxSubarrayHelper(nums, i + 1, currSum, maxSum, start, tempStart, end);
    }

    pair<int, vector<int>> maxSubArray(vector<int> &nums)
    {
        return maxSubarrayHelper(nums, 1, nums[0], nums[0], 0, 0, 0); // Recursion call start karna
    }
};

int main()
{
    vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4}; // Example input
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
