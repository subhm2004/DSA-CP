/*
 * ============================================================================
 * TOPIC    : Backtracking — Combination Sum
 * FILE     : combination_sum.cpp
 * PROBLEM  : Combinations summing to target (reuse allowed)
 * LEETCODE : 39 — Combination Sum
 * APPROACH : Backtrack; pick same index for reuse
 * COMPLEX  : Time: O(2^target)  |  Space: O(target)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// COMBINATION SUM — target sum banane wale combos (same number reuse allowed)
// ────────────────────────────────────────────────────────────────────────────
// Funda: sorted array se pick karo; reuse ke liye i (not i+1) se recurse
// target 0 ho gaya to valid combo — path save karo
// COMPLEX: Time O(2^target)  |  Space O(target)
// ════════════════════════════════════════════════════════════════════════════

class Solution {
    vector<vector<int>> ans;

    // ── bt: start se pick karke target 0 tak pahuncho ──────────────────────
    //   1) target == 0 -> valid combo, path ans me push
    //   2) start se end tak har candidate try
    //   3) c[i] > target -> sorted hai, break (pruning)
    //   4) pick karo, same index i se recurse (reuse allowed)
    //   5) backtrack: pop_back
    void bt(vector<int> &c, int target, int start, vector<int> &path) {
        if (target == 0) {
            ans.push_back(path); // sum exactly target — valid combination
            return;
        }
        for (int i = start; i < (int)c.size(); i++) {
            if (c[i] > target) break; // aage ke numbers aur bade — fayda nahi
            path.push_back(c[i]);
            bt(c, target - c[i], i, path); // i hi — same number dubara use kar sakte
            path.pop_back();
        }
    }

public:
    // ── combinationSum: sort + backtrack se saari combos ───────────────────
    //   1) candidates sort — early break ke liye
    //   2) empty path se bt start
    //   3) ans return
    vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<int> path;
        bt(candidates, target, 0, path);
        return ans;
    }
};

// ── main: target=7 par 2 combos verify ─────────────────────────────────────
//   1) candidates {2,3,6,7} define
//   2) combinationSum call, size print — [[2,2,3], [7]]
int main() {
    vector<int> c = {2, 3, 6, 7};
    cout << Solution().combinationSum(c, 7).size() << endl; // 2
    return 0;
}
