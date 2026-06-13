/*
 * ============================================================================
 * TOPIC    : Difference Array Technique with Jumps
 * FILE     : difference_array_with_jumps.cpp
 * PROBLEM  : Query [L, R, val, K] — sirf L, L+K, L+2K, ... <= R par +val
 * APPROACH : diff[L]+=val, diff[stop]-=val, prefix sum along K-chain
 * COMPLEX  : Mark O(1) | Prefix O(n) per query | Apply O(n)
 * ============================================================================
 *
 * NORMAL DIFF ARRAY (K=1, har consecutive index):
 *   Range [L,R] me +val:
 *     diff[L]   += val
 *     diff[R+1] -= val
 *   Prefix sum (step 1): diff[i] += diff[i-1]
 *   arr[i] += diff[i]
 *
 * JUMP DIFF ARRAY (step K):
 *   Range [L,R] me +val sirf L, L+K, L+2K, ... <= R par:
 *     steps = (R - L) / K
 *     stop  = L + (steps + 1) * K    // range ke BAAD pehla index (cancel yahan)
 *
 *     diff[L]    += val
 *     diff[stop] -= val               (agar stop <= n)
 *
 *   Prefix sum (step K, same residue chain):
 *     diff[i] += diff[i - K]   for i = K, K+1, ..., n
 *
 *   nums[i] += diff[i]
 *
 * BRUTE (mat karo jab diff use ho sakta):
 *   for (i = L; i <= R; i += K) nums[i] += val;   → har query O((R-L)/K)
 *
 * Example: L=1, R=5, val=10, K=2
 *   Updated indices: 1, 3, 5
 *   steps = (5-1)/2 = 2
 *   stop  = 1 + (2+1)*2 = 7
 *   marks: diff[1]+=10, diff[7]-=10
 *   prefix K=2: diff[1]=10, diff[3]=10, diff[5]=10, diff[7]=0
 *
 * LC 3655 (multiply): leetcode_3655_xor_range_multiply.cpp
 *   diff[L]*=v, diff[stop]*=inv(v), prefix PRODUCT along K-chain
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// DIFFERENCE ARRAY WITH K-JUMPS
// ────────────────────────────────────────────────────────────────────────────
// Har query [L, R, val, K] ke liye:
//   1) chhota diff array banao (size n+1)
//   2) start/stop pe mark karo — O(1)
//   3) K-chain pe prefix sum chalao — O(n)
//   4) nums me diff add karo
//
// Note: K=1 pe yeh normal 1D difference array ban jata hai (stop = R+1).
// ════════════════════════════════════════════════════════════════════════════

class DifferenceArrayKJump {
private:
    int n; // array size (nums ke indices 0 .. n-1)

public:
    // ── Constructor: array size store karo ───────────────────────────────────
    //   n = kitne elements hain un par queries lagengi
    DifferenceArrayKJump(int size) : n(size) {}

    // ── update: ek [L, R, val, K] query diff array se apply karo ───────────
    //
    // Parameters:
    //   nums  — jis array pe update lagana hai (modify hoga)
    //   L     — range start index (yahan se jump shuru)
    //   R     — range end index (yahan tak, inclusive)
    //   val   — kitna add karna hai har touched index pe
    //   K     — jump size (har baar K index aage badho)
    //
    // Step 1 — diff array banao (size n+1, sab 0):
    //   Extra 1 slot kyun? stop index kabhi n ho sakta hai (cancel mark ke liye)
    //   nums sirf 0..n-1 hai, lekin diff[n] pe cancel mark safe hai
    //
    // Step 2 — start pe +val mark:
    //   diff[L] += val
    //   Matlab: L se jump chain pe effect shuru
    //
    // Step 3 — stop index nikalo aur cancel mark:
    //   steps   = (R - L) / K     kitni baar K jump karke R tak pahunche
    //   stop    = L + (steps + 1) * K
    //             = last updated index + K
    //             = range ke turant baad wala index (jahan effect BAND)
    //   diff[stop] -= val
    //
    //   Example: L=0, R=8, K=2
    //     touched: 0,2,4,6,8  (steps = 4)
    //     stop = 0 + 5*2 = 10  → diff[10]-=val (cancel)
    //
    // Step 4 — K-jump prefix sum:
    //   Normal diff: diff[i] += diff[i-1]     (step 1)
    //   Jump diff:    diff[i] += diff[i-K]     (step K)
    //
    //   Kyun kaam karta hai?
    //     diff[i] aur diff[i-K] hamesha SAME residue chain pe hain (mod K)
    //     i badhte hue jao → har chain ka prefix apne aap build ho jata hai
    //
    //   Example K=2, diff[0]=3, baaki 0:
    //     i=2: diff[2]+=diff[0]=3
    //     i=4: diff[4]+=diff[2]=3
    //     i=3: diff[3]+=diff[1]=0  (alag chain, disturb nahi hoti)
    //
    // Step 5 — nums me diff add karo:
    //   nums[i] += diff[i]  for i = 0 .. n-1
    //
    // Complexity: O(n) per query (prefix + apply)
    void update(vector<int>& nums, int L, int R, int val, int K) {
        vector<int> diff(n + 1, 0);

        // Step 2: range start pe effect shuru
        diff[L] += val;

        // Step 3: last touched ke baad cancel mark
        int steps = (R - L) / K;
        int stop = L + (steps + 1) * K;

        if (stop <= n) {
            diff[stop] -= val;
        }

        // Step 4: prefix sum along K-jump chains
        for (int i = K; i <= n; i++) {
            diff[i] += diff[i - K];
        }

        // Step 5: final array me apply
        for (int i = 0; i < n; i++) {
            nums[i] += diff[i];
        }
    }
};

int main() {
    vector<int> nums(10, 0);
    DifferenceArrayKJump da(nums.size());

    // ── Query 1: [L=0, R=8, val=3, K=2] ───────────────────────────────────
    //   touched indices: 0, 2, 4, 6, 8  (sab me +3)
    //   steps = (8-0)/2 = 4
    //   stop  = 0 + 5*2 = 10 → diff[10]-=3
    //   after prefix: diff[0,2,4,6,8] = 3
    da.update(nums, 0, 8, 3, 2);

    // ── Query 2: [L=1, R=7, val=2, K=3] ───────────────────────────────────
    //   touched indices: 1, 4, 7  (sab me +2)
    //   steps = (7-1)/3 = 2
    //   stop  = 1 + 3*3 = 10 → diff[10]-=2
    da.update(nums, 1, 7, 2, 3);

    // ── Query 3: [L=0, R=4, val=1, K=1] ───────────────────────────────────
    //   K=1 → NORMAL difference array (har index 0,1,2,3,4)
    //   stop = 0 + 5*1 = 5 → diff[5]-=1  (same as diff[R+1] in normal diff)
    da.update(nums, 0, 4, 1, 1);

    // Final expected:
    //   idx 0: 3+0+1 = 4
    //   idx 1: 0+2+1 = 3
    //   idx 2: 3+0+1 = 4
    //   idx 3: 0+0+1 = 1
    //   idx 4: 3+2+1 = 6
    //   idx 5: 0
    //   idx 6: 3
    //   idx 7: 0+2   = 2
    //   idx 8: 3
    //   idx 9: 0
    //   → 4 3 4 1 6 0 3 2 3 0

    cout << "Final: ";
    for (int x : nums) {
        cout << x << " ";
    }
    cout << "\n";

    return 0;
}
