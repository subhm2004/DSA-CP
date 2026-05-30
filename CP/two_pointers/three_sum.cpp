/*
 * ============================================================================
 * TOPIC    : Two Pointers
 * FILE     : three_sum.cpp
 * PROBLEM  : Find all unique triplets with sum zero
 * APPROACH : Sort + fix i + two pointers on rest
 * COMPLEX  : Time: O(n^2)  |  Space: O(1) extra
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> threeSum(vector<int> nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> ans;
    int n = nums.size();

    for (int i = 0; i < n; i++) {
        if (i > 0 && nums[i] == nums[i - 1])
            continue;
        int l = i + 1, r = n - 1;
        while (l < r) {
            long long sum = (long long)nums[i] + nums[l] + nums[r];
            if (sum == 0) {
                ans.push_back({nums[i], nums[l], nums[r]});
                while (l < r && nums[l] == nums[l + 1])
                    l++;
                while (l < r && nums[r] == nums[r - 1])
                    r--;
                l++;
                r--;
            } else if (sum < 0)
                l++;
            else
                r--;
        }
    }
    return ans;
}

int main() {
    vector<int> nums = {-1, 0, 1, 2, -1, -4};
    for (auto &t : threeSum(nums)) {
        cout << t[0] << " " << t[1] << " " << t[2] << endl;
    }
    return 0;
}
