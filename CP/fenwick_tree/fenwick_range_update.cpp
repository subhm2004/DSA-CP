/*
 * ============================================================================
 * TOPIC    : Fenwick Tree — Range Update, Point Query
 * FILE     : fenwick_range_update.cpp
 * PROBLEM  : Range add on array, query value at index i
 * APPROACH : Difference array technique on BIT
 * COMPLEX  : O(log n) per update/query
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// FENWICK TREE — Range Add + Point Query
// ────────────────────────────────────────────────────────────────────────────
// Trick: difference array BIT pe. Range [l,r] me +v:
//   add(l, +v) aur add(r+1, -v)
// Point query = prefix sum at i (wo hi arr[i] ban jaata hai)
//
// i & -i -> LSB jump (update/query dono me)
// ════════════════════════════════════════════════════════════════════════════

struct Fenwick {
    int n;
    vector<long long> bit;

    // ── Fenwick: difference-array BIT setup ──
    //   1) n = original array size store karo
    //   2) bit size n+2 — r+1 update ke liye extra slot safe rehta hai
    //   3) sab 0 — difference array initially zero hai
    Fenwick(int n) : n(n), bit(n + 2, 0) {}

    // ── add: index 'i' pe 'v' add karo (internal BIT update) ──
    //   1) i se n tak loop — standard BIT point update pattern
    //   2) har bit[i] += v — difference array me delta daal rahe ho
    //   3) i += i & -i se agla responsible parent node (LSB jump)
    void add(int i, long long v) {
        for (; i <= n; i += i & -i)  // i & -i = lowest set bit, next BIT index
            bit[i] += v;
    }

    // ── prefix: [1, i] ka sum (difference array ka prefix = actual value) ──
    //   1) difference array ka prefix sum = original array ki value at i
    //   2) i se 1 tak: har bit[i] ko s me add karo
    //   3) i -= i & -i se pichla covered range node lo
    //   4) yahi point query ka answer hai — rebuild array nahi karna padta
    long long prefix(int i) const {
        long long s = 0;
        for (; i > 0; i -= i & -i)
            s += bit[i];
        return s;
    }

    // ── rangeAdd: [l, r] ke har element me 'v' add karo ──
    //   1) difference trick: arr[l] += v, arr[r+1] -= v (conceptually)
    //   2) add(l, +v) — range start pe positive delta
    //   3) add(r+1, -v) — range ke baad negative delta, aage wale indices affect nahi
    //   4) prefix sum karoge to [l..r] me +v accumulate hoga, baahar 0
    void rangeAdd(int l, int r, long long v) {
        add(l, v);
        add(r + 1, -v);  // difference array: r+1 pe -v daal ke range band karo
    }

    // ── pointQuery: index 'i' ki current value ──
    //   1) direct prefix(i) return — difference array ka i-th prefix = arr[i]
    //   2) koi alag logic nahi, rebuild ya loop over range ki zaroorat nahi
    long long pointQuery(int i) const { return prefix(i); }
};

// ── main: range add + point query demo ──
//   1) overlapping rangeAdd calls lagao
//   2) har index ki final value pointQuery se print karo
int main() {
    int n = 5;
    Fenwick fw(n);
    fw.rangeAdd(1, 3, 10);
    fw.rangeAdd(2, 4, 5);

    for (int i = 1; i <= n; i++)
        cout << "arr[" << i << "] = " << fw.pointQuery(i) << endl;
    return 0;
}
