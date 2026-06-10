/*
 * ============================================================================
 * TOPIC    : Backtracking — Subsets (Power Set)
 * FILE     : subsets.cpp
 * PROBLEM  : All subsets of distinct integers
 * LEETCODE : 78 — Subsets
 * APPROACH : Include / exclude each element (pick from index)
 * COMPLEX  : Time: O(n * 2^n)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// SUBSETS (POWER SET) — distinct numbers ke saare possible subsets nikalo
// ────────────────────────────────────────────────────────────────────────────
// Funda: har index se aage ke elements pick karo ya skip karo
// Har recursion level par current path ek valid subset hai
// COMPLEX: Time O(n * 2^n)  |  Space O(n)
// ════════════════════════════════════════════════════════════════════════════

class Solution {
    vector<vector<int>> ans;
    vector<int> path;

    // ── bt: index se aage ke elements se subsets build karo ────────────────
    //   1) current path ko ans me push — har state valid subset hai
    //   2) idx se end tak har element try karo
    //   3) element pick karo, recurse i+1 par
    //   4) backtrack: pop_back karke agla element try
    void bt(vector<int> &nums, int idx) {
        ans.push_back(path); // empty subset bhi yahan capture hota hai
        for (int i = idx; i < (int)nums.size(); i++) {
            path.push_back(nums[i]); // is element ko subset me include karo
            bt(nums, i + 1); // aage ke elements se extend karo
            path.pop_back(); // include hatao — exclude wala branch explore hoga
        }
    }

public:
    // ── subsets: backtracking se saari subsets generate karo ───────────────
    //   1) idx 0 se bt start
    //   2) ans return
    vector<vector<int>> subsets(vector<int> &nums) {
        bt(nums, 0);
        return ans;
    }
};

// ── main: {1,2,3} ke 2^3 = 8 subsets verify ────────────────────────────────
//   1) nums banake subsets call
//   2) size print
int main() {
    vector<int> nums = {1, 2, 3};
    cout << Solution().subsets(nums).size() << endl; // 8
    return 0;
}
