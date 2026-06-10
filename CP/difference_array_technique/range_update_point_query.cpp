/*
 * ============================================================================
 * TOPIC    : Difference Array Technique
 * FILE     : range_update_point_query.cpp
 * PROBLEM  : Multiple range add updates, then point query
 * APPROACH : Difference array + prefix on demand
 * COMPLEX  : Update O(1), Point query O(n) once after all updates
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// DIFFERENCE ARRAY — Range Add + Point Query / Final Array Build
// ────────────────────────────────────────────────────────────────────────────
// rangeAdd(l,r,val): diff[l]+=val, diff[r+1]-=val  (O(1))
// valueAt(i): index i tak prefix sum = arr[i] after all updates
// buildFinalArray(): poori final array ek baar me nikalo
// ════════════════════════════════════════════════════════════════════════════

class DiffArray {
    vector<long long> diff;
    int n;

public:
    // ── DiffArray: n-size ka diff array initialize karo ─────────────────────
    //   1) n store karo, diff size n+1 (boundary cancel ke liye extra slot)
    //   2) sab diff[i] = 0 — abhi koi update nahi lagaya
    DiffArray(int n) : n(n), diff(n + 1, 0) {}

    // ── rangeAdd: [l, r] ke har element me 'val' add karo ───────────────────
    //   1) diff[l] += val — range yahan se shuru, effect +val
    //   2) diff[r+1] -= val — r ke baad effect cancel (sirf [l,r] tak rahe)
    //   3) poori range iterate nahi karte — sirf 2 jagah mark, O(1) update
    void rangeAdd(int l, int r, long long val) {
        diff[l] += val;
        if (r + 1 < n)
            diff[r + 1] -= val;
    }

    // ── valueAt: index 'i' ki value (prefix sum 0..i) ───────────────────────
    //   1) 0 se i tak diff[j] ka sum nikalo
    //   2) yeh prefix sum hi arr[i] ki final value hai
    //   3) slow hai O(i) — sirf ek point ke liye; poori array ke liye buildFinalArray use karo
    long long valueAt(int i) const {
        long long sum = 0;
        for (int j = 0; j <= i; j++)
            sum += diff[j];
        return sum;
    }

    // ── buildFinalArray: prefix sum se poori array banao ────────────────────
    //   1) cur = 0 se running sum shuru karo
    //   2) har i pe cur += diff[i], arr[i] = cur
    //   3) ek pass me poori final array mil jaati hai — O(n)
    vector<long long> buildFinalArray() const {
        vector<long long> arr(n);
        long long cur = 0;
        for (int i = 0; i < n; i++) {
            cur += diff[i];
            arr[i] = cur;
        }
        return arr;
    }
};

int main() {
    DiffArray da(6);
    da.rangeAdd(1, 3, 5);
    da.rangeAdd(2, 5, 2);
    da.rangeAdd(0, 0, 10);

    cout << "Point query index 2 = " << da.valueAt(2) << endl;
    cout << "Final array: ";
    for (long long x : da.buildFinalArray())
        cout << x << " ";
    cout << endl;
    return 0;
}
