/*
 * ============================================================================
 * TOPIC    : Difference Array Technique with Jumps
 * FILE     : difference_array_with_jumps.cpp
 * PROBLEM  : Jump-range DP without O(n * window) — LC 1871 Jump Game VII
 * APPROACH : Diff array se sliding window [i-maxJ, i-minJ] maintain karo
 * COMPLEX  : Time O(n)  |  Space O(n)
 * ============================================================================
 *
 * NAIVE DP (slow):
 *   dp[i] = koi bhi j ∈ [i-minJump, i-maxJump] se jump karke aaya?
 *   Har i ke liye poori window scan → O(n * (maxJump-minJump)) → TLE
 *
 * DIFF ARRAY TRICK (fast) — INCOMING window:
 *   Index i par poochho: kaun-kaun se purane indices mujh tak jump kar sakte?
 *   Valid predecessors = [i-maxJump, i-minJump]
 *   Jab window slide hoti hai:
 *     diff[i - minJump]     += 1   (naya predecessor enter)
 *     diff[i - maxJump]     -= 1   (purana predecessor exit)  [boundary careful]
 *   Running prefix `cur` = kitne reachable predecessors is i ke liye
 *
 * OUTGOING variant bhi hai (reachable i se [i+minJ, i+maxJ] mark) — same idea,
 * direction ulta. Yahan incoming use kiya — LC 1871 ke liye zyada clean.
 *
 * MULTIPLICATIVE variant (LC 3655):
 *   Query [l,r,k,v]: indices l, l+k, l+2k, ... <= r par nums *= v
 *   Additive diff ki jagah multiplicative diff:
 *     diff[l] *= v,  diff[R] *= v^(-1)   (R = range ke baad pehla index same chain pe)
 *   Prefix PRODUCT along k-jumps: diff[i] *= diff[i-k]
 *   Phir nums[i] *= diff[i]
 */

#include <bits/stdc++.h>
using namespace std;

static const long long MOD = 1'000'000'007LL;

// ── modPow: a^e mod MOD (Fermat se inverse bhi) ─────────────────────────────
long long modPow(long long a, long long e) {
    long long r = 1 % MOD;
    a %= MOD;
    while (e > 0) {
        if (e & 1)
            r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

// ════════════════════════════════════════════════════════════════════════════
// JUMP GAME VII — Boolean reachability (LeetCode 1871)
// ────────────────────────────────────────────────────────────────────────────
// s[i]=='0' par khade ho sakte ho, '1' blocked hai.
// Index 0 se start, har baar [minJump, maxJump] door jump.
// Last index tak pahunch sakte ho?
// ════════════════════════════════════════════════════════════════════════════

// ── canReachJumpGameVII: incoming diff window + prefix se O(n) ─────────────
//   1) diff[i]=1 agar index i reachable hai (start pe i==0 && s[0]=='0')
//   2) har i pe:
//        cur += diff[i - minJump]   — naya predecessor window me aaya
//        cur -= diff[i - maxJump - 1] — purana predecessor window se gaya
//   3) s[i]=='0' aur (i==0 ya cur>0) → i reachable, diff[i]=1
//   4) last index reachable? → diff[n-1]==1
bool canReachJumpGameVII(const string &s, int minJump, int maxJump) {
    int n = (int)s.size();
    if (s[0] == '1' || s[n - 1] == '1')
        return false;

    vector<int> diff(n, 0); // diff[i]=1 → index i reachable hai
    if (s[0] == '0')
        diff[0] = 1;

    int cur = 0; // kitne reachable predecessors is i ke liye active hain
    for (int i = 1; i < n; i++) {
        if (i - minJump >= 0)
            cur += diff[i - minJump];
        if (i - maxJump - 1 >= 0)
            cur -= diff[i - maxJump - 1];

        if (s[i] == '0' && cur > 0)
            diff[i] = 1;
    }

    return diff[n - 1] == 1;
}

// ════════════════════════════════════════════════════════════════════════════
// COUNT WAYS WITH JUMPS — incoming diff window, paths count
// ────────────────────────────────────────────────────────────────────────────
// diff[i] = kitne tareeke se index i tak pahunche (not just 0/1)
// cur += diff[i-minJump], cur -= diff[i-maxJump-1]
// new ways at i = cur (sum of ways from all valid predecessors)
// ════════════════════════════════════════════════════════════════════════════

// ── countWaysWithJumps: blocked skip, end tak total ways ───────────────────
//   1) diff[0]=1 agar start free
//   2) har i>0: cur += diff[i-minJ], cur -= diff[i-maxJ-1]
//   3) free ho to diff[i]=cur (itne tareeke)
//   4) return diff[n-1]
long long countWaysWithJumps(int n, int minJump, int maxJump,
                             const vector<int> &blocked) {
    vector<int> isBlocked(n, 0);
    for (int x : blocked)
        if (0 <= x && x < n)
            isBlocked[x] = 1;

    if (isBlocked[0] || isBlocked[n - 1])
        return 0;

    vector<long long> diff(n, 0);
    if (!isBlocked[0])
        diff[0] = 1;

    long long cur = 0;
    for (int i = 1; i < n; i++) {
        if (i - minJump >= 0)
            cur += diff[i - minJump];
        if (i - maxJump - 1 >= 0)
            cur -= diff[i - maxJump - 1];

        if (!isBlocked[i] && cur > 0)
            diff[i] = cur;
    }

    return diff[n - 1];
}

// ════════════════════════════════════════════════════════════════════════════
// OUTGOING VARIANT — reachable i se [i+minJ, i+maxJ] mark (alternative)
// ────────────────────────────────────────────────────────────────────────────
// Kabhi problem me "aage ki window" mark karna zyada natural ho.
// cur = prefix of mark array; jab i reachable ho to range mark karo.
// ════════════════════════════════════════════════════════════════════════════

// ── canReachOutgoing: outgoing diff marks + prefix ─────────────────────────
//   1) mark[i] pe prefix cur = kya i reachable hai
//   2) i reachable + s[i]=='0' → [i+minJ, i+maxJ] me mark += 1
//   3) last index pe cur > 0
bool canReachOutgoing(const string &s, int minJump, int maxJump) {
    int n = (int)s.size();
    if (s[0] == '1' || s[n - 1] == '1')
        return false;

    vector<int> mark(n + 1, 0);
    int cur = 0;

    for (int i = 0; i < n; i++) {
        cur += mark[i];

        if (s[i] == '1')
            continue;

        bool reachable = (i == 0) || (cur > 0);
        if (!reachable)
            continue;

        int l = i + minJump;
        if (l >= n)
            continue;

        int r = min(i + maxJump, n - 1);
        mark[l] += 1;
        mark[r + 1] -= 1;
    }

    return cur > 0;
}

// ════════════════════════════════════════════════════════════════════════════
// LC 3655 — XOR After Range Multiplication Queries II
// ────────────────────────────────────────────────────────────────────────────
// Query [l, r, k, v]: idx = l, l+k, l+2k, ... <= r tak nums[idx] *= v (mod MOD)
// Ant me sab elements ka XOR return karo.
//
// SAME PATTERN — multiplicative diff on k-jump chain:
//   Normal diff:  diff[l]+=v, diff[r+1]-=v  → prefix SUM
//   Yahan:        diff[l]*=v, diff[R]*=v^-1  → prefix PRODUCT (step k)
//
// k > sqrt(n): direct walk O((r-l)/k) — kam indices touch
// k <= sqrt(n): events[k][residue] pe diff marks, phir chain sweep O(n)
// ════════════════════════════════════════════════════════════════════════════

// ── xorAfterQueries: LC 3655 full solution ─────────────────────────────────
//   1) B = sqrt(n) threshold — chhote/large k alag handle
//   2) k > B: seedha idx += k loop se multiply
//   3) k <= B: chain residue = l % k, t-index pe events mark:
//        t1 = (l-res)/k pe *= v,  t2+1 pe *= v^(-1)  (range band)
//   4) har (k, residue) chain sweep: cur prefix product, nums[idx] *= cur
//   5) sab nums ka XOR return
int xorAfterQueries(vector<int> &nums, vector<vector<int>> &queries) {
    int n = (int)nums.size();
    int B = (int)sqrt(n) + 1;

    // events[k][res] = is k-jump chain (residue res) par (t, multiplier) marks
    vector<vector<vector<pair<int, long long>>>> events(B + 1);
    for (int k = 1; k <= B; k++)
        events[k].resize(k);

    for (auto &qq : queries) {
        int l = qq[0], r = qq[1], k = qq[2];
        long long v = qq[3];

        if (k > B) {
            // large step — direct jump walk
            for (int idx = l; idx <= r; idx += k)
                nums[idx] = (int)((long long)nums[idx] * v % MOD);
        } else {
            // small step — multiplicative diff on chain t-index
            int res = l % k;
            int t1 = (l - res) / k;
            int t2 = (r - res) / k;
            events[k][res].push_back({t1, v});

            // R = range ke baad pehla index → yahan v^-1 se cancel
            if (t2 + 1 <= (n - 1 - res) / k)
                events[k][res].push_back({t2 + 1, modPow(v, MOD - 2)});
        }
    }

    for (int k = 1; k <= B; k++) {
        for (int res = 0; res < k; res++) {
            auto &ev = events[k][res];
            if (ev.empty())
                continue;

            sort(ev.begin(), ev.end());
            // same t pe multiple marks → multiply merge
            vector<pair<int, long long>> comp;
            for (auto [t, val] : ev) {
                if (!comp.empty() && comp.back().first == t)
                    comp.back().second = comp.back().second * val % MOD;
                else
                    comp.push_back({t, val});
            }

            // prefix product sweep along chain: res, res+k, res+2k, ...
            long long cur = 1;
            int ptr = 0;
            for (int idx = res, t = 0; idx < n; idx += k, t++) {
                while (ptr < (int)comp.size() && comp[ptr].first == t) {
                    cur = cur * comp[ptr].second % MOD;
                    ptr++;
                }
                nums[idx] = (int)((long long)nums[idx] * cur % MOD);
            }
        }
    }

    int xr = 0;
    for (int x : nums)
        xr ^= x;
    return xr;
}

// ── applyMultDiffOnChain: ek fixed k ke liye diff pattern (teaching helper) ─
//   Query [l,r,v] on step-k chain:
//     diff[l] *= v,  diff[stop] *= v^-1
//   stop = l + (floor((r-l)/k)+1)*k  (range ke baad pehla index)
//   Prefix product: diff[i] *= diff[i-k]
//   nums[i] *= diff[i]
void applyMultDiffOnChain(vector<long long> &nums, int k,
                          const vector<tuple<int, int, long long>> &updates) {
    int n = (int)nums.size();
    vector<long long> diff(n, 1);

    for (auto [l, r, v] : updates) {
        diff[l] = diff[l] * v % MOD;
        int stop = l + ((r - l) / k + 1) * k;
        if (stop < n)
            diff[stop] = diff[stop] * modPow(v, MOD - 2) % MOD;
    }

    // prefix product along k-jumps (additive diff ka prefix sum jaisa)
    for (int i = k; i < n; i++)
        diff[i] = diff[i] * diff[i - k] % MOD;

    for (int i = 0; i < n; i++)
        nums[i] = nums[i] * diff[i] % MOD;
}

int main() {
    // ── Demo 1: LeetCode 1871 style ───────────────────────────────────────
    cout << "=== Jump Game VII (incoming diff window) ===\n";
    cout << boolalpha;
    cout << "canReach(\"011010\", 2, 3) = "
         << canReachJumpGameVII("011010", 2, 3) << "\n"; // true
    cout << "canReach(\"01101110\", 2, 3) = "
         << canReachJumpGameVII("01101110", 2, 3) << "\n"; // false

    // outgoing variant bhi same answer
    cout << "canReachOutgoing(\"01101110\", 2, 3) = "
         << canReachOutgoing("01101110", 2, 3) << "\n";

    // ── Demo 2: Count ways ────────────────────────────────────────────────
    cout << "\n=== Count ways with jumps ===\n";
    cout << "ways(n=6, min=2, max=3, no block) = "
         << countWaysWithJumps(6, 2, 3, {}) << "\n";

    cout << "ways(n=6, min=2, max=3, block={2}) = "
         << countWaysWithJumps(6, 2, 3, {2}) << "\n";

    // ── Demo 3: LeetCode 3655 — multiplicative diff on k-jump chains ──────
    cout << "\n=== LC 3655 XOR After Range Multiplication Queries II ===\n";

    vector<int> nums1 = {1, 1, 1};
    vector<vector<int>> q1 = {{0, 2, 1, 4}};
    cout << "Example 1 XOR = " << xorAfterQueries(nums1, q1) << "\n"; // 4

    vector<int> nums2 = {2, 3, 1, 5, 4};
    vector<vector<int>> q2 = {{1, 4, 2, 3}, {0, 2, 1, 2}};
    cout << "Example 2 XOR = " << xorAfterQueries(nums2, q2) << "\n"; // 31

    // teaching helper: fixed k=2 chain
    vector<long long> chain = {2, 3, 1, 5, 4};
    applyMultDiffOnChain(chain, 2, {{1, 4, 3}}); // idx 1,3 *= 3
    cout << "Chain helper after [1,4,k=2,v=3]: ";
    for (long long x : chain)
        cout << x << " ";
    cout << "\n"; // 2 9 1 15 4

    return 0;
}
