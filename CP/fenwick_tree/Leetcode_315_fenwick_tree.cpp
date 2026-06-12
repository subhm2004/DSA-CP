// Leetcode 315: Count of Smaller Numbers After Self
#include <bits/stdc++.h>
#include "../coordinate_compression/coordinate_compression.h"
using namespace std;
using ll = long long;

// ════════════════════════════════════════════════════════════════════════════
// LEETCODE 315 — Coordinate_Compression (shared header) + BIT
// ────────────────────────────────────────────────────────────────────────────
// RIGHT → LEFT scan + frequency BIT
// Detailed version: leetcode_315_count_smaller_after_self.cpp
// ════════════════════════════════════════════════════════════════════════════

class BIT {
public:
    int n;
    vector<ll> bit;

    // ── BIT: frequency Fenwick tree, 1-indexed ──
    BIT(int n) : n(n), bit(n + 1, 0) {}

    // ── update: index i pe frequency +x (i & -i LSB jump) ──
    void update(int i, ll x) {
        for (; i <= n; i += (i & -i))
            bit[i] += x;
    }

    // ── sum: [1,i] prefix — kitne elements compressed rank < i ──
    ll sum(int i) {
        ll total = 0;
        for (; i > 0; i -= (i & -i))
            total += bit[i];
        return total;
    }
};

class Solution {
public:
    /*
     * countSmaller(nums)
     * RIGHT se LEFT: BIT me right wale elements.
     * ans[i] = sum(compress[id]) = right me chhote count.
     */
    vector<int> countSmaller(vector<int>& nums) {
        int n = (int)nums.size();

        Coordinate_Compression cc(nums);
        BIT bit(cc.size());
        vector<int> ans(n, 0);

        for (int i = n - 1; i >= 0; i--) {
            int id = cc.compress[nums[i]];
            ans[i] = (int)bit.sum(id);
            bit.update(cc.bit_id(nums[i]), 1);
        }

        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution sol;
    vector<int> nums = {5, 2, 6, 1};
    vector<int> result = sol.countSmaller(nums);

    for (int count : result)
        cout << count << " ";
    cout << "\n";

    return 0;
}
