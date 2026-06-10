/*
 * ============================================================================
 * TOPIC    : Binary Search on Answer
 * FILE     : prata_cooking_time.cpp
 * PROBLEM  : P pratas, C cooks with ranks — minimum time (POJ PRATA)
 * APPROACH : BS on answer (time), simulate pratas cooked
 * COMPLEX  : Time: O(C log(maxTime))  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// PRATA COOKING (POJ) — Minimum time me P pratas banao
// ────────────────────────────────────────────────────────────────────────────
// Cook rank R: 1st prata R min, 2nd 2R, 3rd 3R... (triangular time)
// BS on answer = total time T
// canCook(T): har cook se kitne pratas ban sakte simulate karo
// MIN answer pattern
// ════════════════════════════════════════════════════════════════════════════

// ── canCook: time T me P pratas ban sakti hain? ─────────────────────────────
//   1) har cook rank r ke liye: batch 1,2,3... jab tak time exceed na ho
//   2) batch k prata time = k*r, cumulative time track karo
//   3) total cooked >= pratas -> true
bool canCook(const vector<int> &ranks, int pratas, long long time) {
    long long cooked = 0;
    for (int r : ranks) {
        long long t = 0, batch = 1;
        while (t + batch * r <= time) {
            t += batch * r;
            cooked += batch;
            batch++;
        }
    }
    return cooked >= pratas;
}

// ── minCookTime: minimum time jahan P pratas ready ──────────────────────────
//   1) lo=0, hi = worst case upper bound (maxRank * P*(P+1)/2)
//   2) canCook(mid) -> ans=mid, hi=mid-1 (minimize time)
long long minCookTime(vector<int> ranks, int pratas) {
    long long lo = 0;
    long long hi = 1LL * (*max_element(ranks.begin(), ranks.end())) * pratas * (pratas + 1) / 2;
    long long ans = hi;

    while (lo <= hi) {
        long long mid = lo + (hi - lo) / 2;
        if (canCook(ranks, pratas, mid)) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return ans;
}

int main() {
    vector<int> ranks = {1, 2, 3, 4};
    int pratas = 10;
    cout << "Minimum cooking time = " << minCookTime(ranks, pratas) << endl;
    return 0;
}
