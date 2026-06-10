/*
 * ============================================================================
 * TOPIC    : Difference Array Technique
 * FILE     : difference_array_1d.cpp
 * PROBLEM  : Range update [l,r] += val on array (offline / batch updates)
 * APPROACH : diff[l] += val, diff[r+1] -= val, then prefix sum
 * COMPLEX  : Update O(1), Rebuild O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// DIFFERENCE ARRAY (1D) — Batch Range Updates
// ────────────────────────────────────────────────────────────────────────────
// Range [l, r] me val add karna ho to poori array iterate karne ki jagah:
//   diff[l]   += val
//   diff[r+1] -= val   (boundary pe cancel)
// Ant me prefix sum = final array.
// ════════════════════════════════════════════════════════════════════════════

// ── applyDifferenceArray: saari range updates apply karke final array banao ──
//   1) diff array banao (size n+1) — yahan sirf range boundaries mark hongi
//   2) har update [l,r]+=val ke liye diff[l]+=val, diff[r+1]-=val (O(1) each)
//   3) prefix sum chalao: cur += diff[i], arr[i] = cur
//   4) prefix sum se overlapping ranges automatically merge ho jaati hain
//   5) final arr return karo — poori array ek baar me rebuild ho gayi
vector<long long> applyDifferenceArray(int n, const vector<tuple<int, int, long long>> &updates) {
    vector<long long> diff(n + 1, 0);

    // har update: [l,r] me val add -> diff me mark karo
    for (auto [l, r, val] : updates) {
        diff[l] += val;
        if (r + 1 <= n)          // r+1 out of bounds na ho to cancel mark lagao
            diff[r + 1] -= val;
    }

    // prefix sum se actual array nikalo
    vector<long long> arr(n);
    long long cur = 0;
    for (int i = 0; i < n; i++) {
        cur += diff[i];          // i tak cumulative effect = arr[i]
        arr[i] = cur;
    }
    return arr;
}

int main() {
    int n = 5;
    vector<tuple<int, int, long long>> updates = {
        {0, 2, 3}, {1, 3, 2}, {2, 4, 1}
    };

    vector<long long> result = applyDifferenceArray(n, updates);
    cout << "After range updates: ";
    for (long long x : result)
        cout << x << " ";
    cout << endl;
    return 0;
}
