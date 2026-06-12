#include <bits/stdc++.h>
#include "../coordinate_compression/coordinate_compression.h"
using namespace std;
using ll = long long;

// ════════════════════════════════════════════════════════════════════════════
// INVERSION COUNT — Fenwick Tree + Coordinate_Compression
// ────────────────────────────────────────────────────────────────────────────
// Inversion = pair (i,j) jahan i < j aur arr[i] > arr[j]
//
// LEFT → RIGHT scan:
//   BIT me arr[0..i-1] ki frequencies
//   "kitne pehle wale CURRENT se bade?" = totalSeen - count(≤ current)
// ════════════════════════════════════════════════════════════════════════════

class BIT {
public:
    int n;
    vector<ll> bit;

    /*
     * BIT(n)
     * n = unique compressed values count.
     * bit size n+1, 1-indexed Fenwick array.
     */
    BIT(int n) : n(n), bit(n + 1, 0) {}

    /*
     * update(i, x)
     * Index i (1-indexed) pe frequency +x.
     * i += i & -i se parent nodes update — O(log n).
     */
    void update(int i, ll x) {
        for (; i <= n; i += (i & -i))
            bit[i] += x;
    }

    /*
     * sum(i)
     * [1..i] prefix frequency count.
     * Kitne processed elements ki compressed value < i (0-based rank sense).
     */
    ll sum(int i) {
        ll total = 0;
        for (; i > 0; i -= (i & -i))
            total += bit[i];
        return total;
    }
};

/*
 * count_Inversions(arr)
 * ---------------------
 * Poori array me inversion pairs count.
 *
 * Step 1: Coordinate_Compression — values → 0..m-1
 * Step 2: get_compressed — har element ki compressed id
 * Step 3: Left → right:
 *           idx = comp[i] + 1  (1-indexed BIT)
 *           count += sum(m) - sum(idx)  → kitne pehle wale > arr[i]
 *           update(idx, 1)               → arr[i] ko BIT me daalo
 */
ll count_Inversions(vector<int>& arr) {
    int n = (int)arr.size();

    Coordinate_Compression cc(arr);
    vector<int> comp = cc.get_compressed(arr);

    int m = cc.size();
    BIT bit(m);

    ll count = 0;

    for (int i = 0; i < n; i++) {
        int idx = comp[i] + 1;
        count += bit.sum(m) - bit.sum(idx);
        bit.update(idx, 1);
    }

    return count;
}

int main() {
    vector<vector<int>> tests = {
        {8, 4, 2, 1},
        {3, 1, 2},
        {1, 20, 6, 4, 5},
        {10, 9, 8, 7, 6, 5},
        {1, 2, 3, 4, 5},
        {1000000, 999999, 2, 1, 5000},
        {5, 3, 5, 1, 3}};

    for (auto& arr : tests) {
        cout << "Array: ";
        for (int x : arr)
            cout << x << " ";
        cout << "\nInversions = " << count_Inversions(arr) << "\n\n";
    }

    return 0;
}
