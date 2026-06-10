/*
 * ============================================================================
 * TOPIC    : Backtracking — Permutations
 * FILE     : permutations.cpp
 * PROBLEM  : All permutations of distinct nums
 * LEETCODE : 46 — Permutations
 * APPROACH : Swap / used array backtracking
 * COMPLEX  : Time: O(n * n!)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// PERMUTATIONS — distinct numbers ke saare possible arrangements nikalo
// ────────────────────────────────────────────────────────────────────────────
// Funda: har position par abhi-tak-unused element try karo (used array)
// Path size == n ho to ek complete permutation mil gaya
// COMPLEX: Time O(n * n!)  |  Space O(n)
// ════════════════════════════════════════════════════════════════════════════

class Solution {
    vector<vector<int>> ans;
    vector<int> path;
    vector<bool> used;

    // ── bt: used array se saari permutations build karo ────────────────────
    //   1) path.size() == n -> complete permutation, ans me save
    //   2) har index i par element try karo
    //   3) used[i] true ho to skip — already path me hai
    //   4) mark used, push, recurse, backtrack (pop + unmark)
    void bt(vector<int> &nums) {
        if (path.size() == nums.size()) {
            ans.push_back(path); // saare n elements place ho gaye
            return;
        }
        for (int i = 0; i < (int)nums.size(); i++) {
            if (used[i]) continue; // ye number pehle se use ho chuka
            used[i] = true;
            path.push_back(nums[i]);
            bt(nums); // agla empty slot fill karo
            path.pop_back();
            used[i] = false; // free karo — is position par dusra num try hoga
        }
    }

public:
    // ── permute: used array init karke backtrack start ─────────────────────
    //   1) used sab false set karo
    //   2) bt chalao
    //   3) saari permutations return
    vector<vector<int>> permute(vector<int> &nums) {
        used.assign(nums.size(), false);
        bt(nums);
        return ans;
    }
};

// ── main: {1,2,3} ke 3! = 6 permutations verify ────────────────────────────
//   1) permute call
//   2) size print
int main() {
    vector<int> nums = {1, 2, 3};
    cout << Solution().permute(nums).size() << endl; // 6
    return 0;
}
