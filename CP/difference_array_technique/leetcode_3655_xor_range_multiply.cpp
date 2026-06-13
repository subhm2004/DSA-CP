/*
 * ============================================================================
 * LEETCODE 3655 — XOR After Range Multiplication Queries II
 * FILE     : leetcode_3655_xor_range_multiply.cpp
 * PROBLEM  : Query [l,r,k,v]: idx=l,l+k,...<=r par nums[idx]*=v; return XOR
 * APPROACH : sqrt threshold + multiplicative jump diff array
 * COMPLEX  : O(n*sqrt(n) + q*sqrt(n)) approx
 * ============================================================================
 *
 * QUERY: [l, r, k, v]
 *   idx = l, l+k, l+2k, ... <= r  →  nums[idx] = nums[idx] * v  (mod MOD)
 *
 * BRUTE: har query pe walk  →  O(q * n/k)  →  TLE
 *
 * SQRT SPLIT (threshold B = sqrt(n)):
 *   k > B  → seedha walk (kam indices, O(n/k) per query)
 *   k <= B → MULTIPLICATIVE jump diff array (batch mark + prefix product)
 *
 * JUMP DIFF (multiplicative, additive jump diff ka bhai):
 *   Normal add jump:  diff[L]+=val,  diff[stop]-=val  → prefix SUM
 *   LC 3655 multiply: diff[L]*=v,   diff[stop]*=v^-1  → prefix PRODUCT
 *
 *   steps = (r - l) / k
 *   stop  = l + (steps + 1) * k
 *
 *   Prefix product along k-chain:
 *     diff[i] *= diff[i - k]
 */

#include <bits/stdc++.h>
using namespace std;

static const long long MOD = 1'000'000'007LL;

// ── modPow: a^e mod MOD (modular inverse = modPow(a, MOD-2)) ───────────────
long long modPow(long long a, long long e) {
    long long r = 1 % MOD;
    a %= MOD;
    while (e > 0) {
        if (e & 1) {
            r = r * a % MOD;
        }
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

long long modInv(long long a) {
    return modPow(a, MOD - 2);
}

// ════════════════════════════════════════════════════════════════════════════
// SQRT THRESHOLD HELPER — LC 3655 me k chhota hai ya bada?
// ────────────────────────────────────────────────────────────────────────────
// B = sqrt(n) + 1
//   k > B  → "large k" → direct idx += k walk (O(n/k), k bada hai to fast)
//   k <= B → "small k"  → jump diff array batch (O(n) per distinct small k)
// ════════════════════════════════════════════════════════════════════════════

class SqrtThreshold {
private:
    int n;
    int B;

public:
    // ── SqrtThreshold: n se block size B nikalo ─────────────────────────────
    SqrtThreshold(int n) : n(n) {
        B = (int)sqrt(n) + 1;
    }

    int size() const {
        return n;
    }

    int threshold() const {
        return B;
    }

    // ── isLargeK: k > sqrt(n) ? direct walk use karo ──────────────────────
    bool isLargeK(int k) const {
        return k > B;
    }

    // ── isSmallK: k <= sqrt(n) ? jump diff batch use karo ─────────────────
    bool isSmallK(int k) const {
        return k <= B;
    }
};

// ════════════════════════════════════════════════════════════════════════════
// MULTIPLICATIVE DIFF JUMP — [L,R,v,K] multiply on k-chain
// ────────────────────────────────────────────────────────────────────────────
// Additive jump (difference_array_with_jumps.cpp):
//   diff[L]+=val, diff[stop]-=val, prefix: diff[i]+=diff[i-K]
//
// Multiplicative jump (LC 3655):
//   diff[L]*=v, diff[stop]*=inv(v), prefix: diff[i]*=diff[i-K]
// ════════════════════════════════════════════════════════════════════════════

class MultiplicativeDiffJump {
private:
    int n;
    vector<long long> diff;

    // ── prefixProductChain: diff[i] *= diff[i-K] along k-chain ────────────
    static void prefixProductChain(vector<long long>& diff, int K, int n) {
        for (int i = K; i < n; i++) {
            diff[i] = diff[i] * diff[i - K] % MOD;
        }
    }

public:
    // ── MultiplicativeDiffJump: diff sab 1 se start (multiply identity) ───
    MultiplicativeDiffJump(int n) : n(n), diff(n, 1) {}

    // ── rangeMultJump: [L,R,v,K] mark karo ────────────────────────────────
    //   1) steps = (R-L)/K, stop = L + (steps+1)*K
    //   2) diff[L] *= v           — chain pe multiply shuru
    //   3) diff[stop] *= v^-1    — range ke baad cancel
    void rangeMultJump(int L, int R, long long v, int K) {
        diff[L] = diff[L] * v % MOD;

        int steps = (R - L) / K;
        int stop = L + (steps + 1) * K;

        if (stop < n) {
            diff[stop] = diff[stop] * modInv(v) % MOD;
        }
    }

    // ── applyTo: prefix product + nums me multiply ────────────────────────
    void applyTo(vector<int>& nums, int K) {
        prefixProductChain(diff, K, n);

        for (int i = 0; i < n; i++) {
            nums[i] = (int)((long long)nums[i] * diff[i] % MOD);
        }
    }

    // reset for reuse
    void reset() {
        fill(diff.begin(), diff.end(), 1);
    }
};

// ════════════════════════════════════════════════════════════════════════════
// LC 3655 SOLVER — sqrt split + jump diff + direct walk
// ════════════════════════════════════════════════════════════════════════════

class LC3655Solver {
private:
    int n;
    SqrtThreshold sqrtHelper;

    // ── applyLargeKQueries: k > B wale direct walk se ─────────────────────
    void applyLargeKQueries(vector<int>& nums,
                            const vector<array<int, 4>>& queries) {
        for (auto [l, r, k, v] : queries) {
            for (int idx = l; idx <= r; idx += k) {
                nums[idx] = (int)((long long)nums[idx] * v % MOD);
            }
        }
    }

    // ── applySmallKQueries: same k wale batch jump diff se ────────────────
    void applySmallKQueries(vector<int>& nums, int k,
                            const vector<array<int, 3>>& qs) {
        MultiplicativeDiffJump mdj(n);

        for (auto [l, r, v] : qs) {
            mdj.rangeMultJump(l, r, v, k);
        }

        mdj.applyTo(nums, k);
    }

public:
    LC3655Solver(int n) : n(n), sqrtHelper(n) {}

    // ── xorAfterQueries: main LC 3655 function ───────────────────────────
    //   1) queries split: large k vs small k (SqrtThreshold)
    //   2) large k → direct walk
    //   3) small k → group by k, MultiplicativeDiffJump batch
    //   4) sab nums ka XOR return
    int xorAfterQueries(vector<int>& nums,
                        vector<vector<int>>& queries) {
        vector<array<int, 4>> largeQ;
        map<int, vector<array<int, 3>>> smallByK;

        for (auto& qq : queries) {
            int l = qq[0], r = qq[1], k = qq[2], v = qq[3];

            if (sqrtHelper.isLargeK(k)) {
                largeQ.push_back({l, r, k, v});
            } else {
                smallByK[k].push_back({l, r, v});
            }
        }

        applyLargeKQueries(nums, largeQ);

        for (auto& [k, qs] : smallByK) {
            applySmallKQueries(nums, k, qs);
        }

        int xr = 0;
        for (int x : nums) {
            xr ^= x;
        }
        return xr;
    }
};

// ════════════════════════════════════════════════════════════════════════════
// ALTERNATIVE — sirf jump diff (sqrt ke bina, teaching / chhote n)
// ════════════════════════════════════════════════════════════════════════════

class LC3655JumpDiffOnly {
public:
    static int xorAfterQueries(vector<int>& nums,
                                 vector<vector<int>>& queries) {
        int n = (int)nums.size();
        map<int, vector<array<int, 3>>> byK;

        for (auto& qq : queries) {
            byK[qq[2]].push_back({qq[0], qq[1], qq[3]});
        }

        for (auto& [k, qs] : byK) {
            MultiplicativeDiffJump mdj(n);
            for (auto [l, r, v] : qs) {
                mdj.rangeMultJump(l, r, v, k);
            }
            mdj.applyTo(nums, k);
        }

        int xr = 0;
        for (int x : nums) {
            xr ^= x;
        }
        return xr;
    }
};

int main() {
    cout << "=== LeetCode 3655 — XOR After Range Multiplication Queries II ===\n\n";

    // ── Example 1 ─────────────────────────────────────────────────────────
    // nums = [1,1,1], query [0,2,1,4] → sab *4 → [4,4,4] → XOR=4
    {
        vector<int> nums = {1, 1, 1};
        vector<vector<int>> queries = {{0, 2, 1, 4}};

        LC3655Solver solver(nums.size());
        int ans = solver.xorAfterQueries(nums, queries);
        cout << "Example 1 (sqrt + jump diff): XOR = " << ans << " (expect 4)\n";
    }

    // ── Example 2 ─────────────────────────────────────────────────────────
    // nums = [2,3,1,5,4]
    // [1,4,2,3] → idx 1,3 *3  → [2,9,1,15,4]
    // [0,2,1,2] → idx 0,1,2 *2 → [4,18,2,15,4]
    // XOR = 4^18^2^15^4 = 31
    {
        vector<int> nums = {2, 3, 1, 5, 4};
        vector<vector<int>> queries = {{1, 4, 2, 3}, {0, 2, 1, 2}};

        LC3655Solver solver(nums.size());
        int ans = solver.xorAfterQueries(nums, queries);
        cout << "Example 2 (sqrt + jump diff): XOR = " << ans << " (expect 31)\n";
    }

    // ── Jump diff only (same answer) ──────────────────────────────────────
    {
        vector<int> nums = {2, 3, 1, 5, 4};
        vector<vector<int>> queries = {{1, 4, 2, 3}, {0, 2, 1, 2}};

        int ans = LC3655JumpDiffOnly::xorAfterQueries(nums, queries);
        cout << "Example 2 (jump diff only):   XOR = " << ans << " (expect 31)\n";
    }

    // ── SqrtThreshold demo ────────────────────────────────────────────────
    {
        SqrtThreshold st(100);
        cout << "\nSqrtThreshold n=100 → B = " << st.threshold() << "\n";
        cout << "k=5  large? " << boolalpha << st.isLargeK(5) << "\n";
        cout << "k=15 large? " << st.isLargeK(15) << "\n";
    }

    // ── MultiplicativeDiffJump walkthrough ────────────────────────────────
    {
        cout << "\nJump diff walkthrough: [L=1,R=4,v=3,K=2] on n=5\n";
        vector<int> nums = {2, 3, 1, 5, 4};
        MultiplicativeDiffJump mdj(5);
        mdj.rangeMultJump(1, 4, 3, 2); // idx 1,3 multiply by 3
        mdj.applyTo(nums, 2);
        cout << "Result: ";
        for (int x : nums) {
            cout << x << " ";
        }
        cout << "(expect 2 9 1 15 4)\n";
    }

    return 0;
}
