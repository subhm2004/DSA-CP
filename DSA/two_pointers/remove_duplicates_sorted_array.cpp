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

// ════════════════════════════════════════════════════════════════════════════
// REMOVE DUPLICATES (SORTED) — Slow/fast write pointer
// ────────────────────────────────────────────────────────────────────────────
// Sorted array — duplicates adjacent hote hain
// w = write pointer — unique elements yahan likho
// nums[i] != nums[i-1] -> naya unique, nums[w++]=nums[i]
// Return w = nayi length
// ════════════════════════════════════════════════════════════════════════════

// ── removeDuplicates: in-place unique, nayi length return ────────────────
//   1) empty -> 0
//   2) w=1 — pehla element unique maan lo
//   3) i=1 se: alag pichle se -> nums[w++]=nums[i]
//   4) w return (unique count)
int removeDuplicates(vector<int> &nums) {
    if (nums.empty()) return 0;
    int w = 1;
    for (int i = 1; i < (int)nums.size(); i++)
        if (nums[i] != nums[i - 1])
            nums[w++] = nums[i]; // naya unique copy karo
    return w;
}

// ── main: {1,1,2,2,3} -> unique 1 2 3 ────────────────────────────────────
int main() {
    vector<int> nums = {1,1,2,2,3};
    int k = removeDuplicates(nums);
    for (int i = 0; i < k; i++) cout << nums[i] << " ";
    cout << endl; // 1 2 3
    return 0;
}
