/*
 * ============================================================================
 * TOPIC    : Backtracking — Combination Sum II
 * FILE     : combination_sum_ii.cpp
 * PROBLEM  : Unique combinations (each number once, no duplicate sets)
 * LEETCODE : 40 — Combination Sum II
 * APPROACH : Sort + skip duplicate at same recursion level
 * COMPLEX  : Time: O(2^n)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// COMBINATION SUM II — target sum ke unique combos (har number ek baar)
// ────────────────────────────────────────────────────────────────────────────
// Funda: sort karo, same level par duplicate values skip karo
// Har element sirf ek baar use — i+1 se aage recurse (reuse nahi)
// COMPLEX: Time O(2^n)  |  Space O(n)
// ════════════════════════════════════════════════════════════════════════════

class Solution {
    vector<vector<int>> ans;

    // ── bt: start se elements pick karke target 0 tak pahuncho ─────────────
    //   1) target == 0 -> valid combo, path save
    //   2) i > start aur c[i]==c[i-1] -> same level duplicate skip
    //   3) c[i] > target -> sorted hai, aage sab bade — break
    //   4) pick karo, i+1 se recurse (reuse allowed nahi)
    //   5) backtrack: pop_back
    void bt(vector<int> &c, int target, int start, vector<int> &path) {
        if (target == 0) {
            ans.push_back(path); // sum exactly target — valid unique combo
            return;
        }
        for (int i = start; i < (int)c.size(); i++) {
            if (i > start && c[i] == c[i - 1]) continue; // duplicate combo avoid — same depth
            if (c[i] > target) break; // sorted array — aage sab target se bade
            path.push_back(c[i]);
            bt(c, target - c[i], i + 1, path); // i+1 — is number dubara use nahi
            path.pop_back();
        }
    }

public:
    // ── combinationSum2: sort + backtrack se unique combos ─────────────────
    //   1) candidates sort — duplicate skip aur early break ke liye
    //   2) empty path se bt start
    //   3) ans return
    vector<vector<int>> combinationSum2(vector<int> &candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<int> path;
        bt(candidates, target, 0, path);
        return ans;
    }
};

// ── main: target=8 par 4 unique combos verify ────────────────────────────────
//   1) candidates with duplicates define
//   2) combinationSum2 call, size print
int main() {
    vector<int> c = {10, 1, 2, 7, 6, 1, 5};
    cout << Solution().combinationSum2(c, 8).size() << endl; // 4
    return 0;
}
