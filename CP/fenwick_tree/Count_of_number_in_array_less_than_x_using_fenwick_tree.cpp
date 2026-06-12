// Count of numbers in array GREATER than x using Fenwick Tree
// Formula: count > x  ==  total - count <= x

#include <bits/stdc++.h>
#include "../coordinate_compression/coordinate_compression.h"
using namespace std;
using ll = long long;

// ════════════════════════════════════════════════════════════════════════════
// COUNT ELEMENTS > x — BIT + Coordinate_Compression
// ────────────────────────────────────────────────────────────────────────────
// Steps:
//   1) Values compress karo
//   2) Saari frequencies BIT me daalo
//   3) count <= x nikalo → total - le_x = > x
// ════════════════════════════════════════════════════════════════════════════

class Fenwick_Tree {
public:
    int n;
    vector<ll> bit;

    /*
     * Fenwick_Tree(n)
     * n = unique value count after compression.
     */
    Fenwick_Tree(int n) : n(n), bit(n + 1, 0) {}

    /*
     * update(i, x)
     * Compressed 1-indexed position i pe frequency +x.
     */
    void update(int i, ll x) {
        for (; i <= n; i += (i & -i))
            bit[i] += x;
    }

    /*
     * sum_query(i)
     * [1..i] prefix frequency — kitne elements compressed rank < i.
     */
    ll sum_query(int i) {
        ll total = 0;
        for (; i > 0; i -= (i & -i))
            total += bit[i];
        return total;
    }
};

int main() {
    vector<int> arr = {5, 1, 3, 3, 10, 7};

    int x;
    cin >> x;

    // Step 1: compress — BIT size = unique values only
    Coordinate_Compression cc(arr);

    int K = cc.size();
    Fenwick_Tree bit(K);

    // Step 2: har element ki frequency BIT me daalo
    for (int v : arr)
        bit.update(cc.bit_id(v), 1);

    // Step 3: count > x = total - count(<= x)
    ll total = bit.sum_query(K);
    ll le_x = bit.sum_query(cc.upper_bit_id(x));  // ≤ x wale
    ll greater = total - le_x;

    cout << "Elements > " << x << " = " << greater << "\n";

    return 0;
}
