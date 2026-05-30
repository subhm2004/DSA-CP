/*
 * ============================================================================
 * TOPIC    : Two Pointers — Remove Duplicates from Sorted Array
 * FILE     : remove_duplicates_sorted_array.cpp
 * PROBLEM  : In-place unique elements, return new length
 * LEETCODE : 26 — Remove Duplicates from Sorted Array
 * APPROACH : Slow pointer for write position
 * COMPLEX  : Time: O(n)  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

int removeDuplicates(vector<int> &nums) {
    if (nums.empty()) return 0;
    int w = 1;
    for (int i = 1; i < (int)nums.size(); i++)
        if (nums[i] != nums[i - 1])
            nums[w++] = nums[i];
    return w;
}

int main() {
    vector<int> nums = {1,1,2,2,3};
    int k = removeDuplicates(nums);
    for (int i = 0; i < k; i++) cout << nums[i] << " ";
    cout << endl; // 1 2 3
    return 0;
}
