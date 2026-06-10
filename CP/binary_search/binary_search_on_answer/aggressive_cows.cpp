/*
 * ============================================================================
 * TOPIC    : Binary Search on Answer
 * FILE     : aggressive_cows.cpp
 * PROBLEM  : Place K cows in stalls — maximize minimum distance
 * APPROACH : BS on answer (distance), check if K cows fit
 * COMPLEX  : Time: O(n log(max))  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// AGGRESSIVE COWS — Maximize minimum distance between K cows
// ────────────────────────────────────────────────────────────────────────────
// BS on answer = minimum distance d
// canPlace(d): greedy — pehli stall pe cow, agli jahan x-last >= d
// d badhane pe harder -> monotonic: false...false true...true
// MAX answer pattern: possible -> lo=mid+1
// ════════════════════════════════════════════════════════════════════════════

// ── canPlace: distance d pe K cows fit ho sakti hain? ─────────────────────
//   1) pehli cow stalls[0] pe, cows=1
//   2) agli stall jahan gap >= d -> nayi cow, last update
//   3) cows >= k -> true
bool canPlace(const vector<int> &stalls, int k, int dist) {
    int cows = 1, last = stalls[0];
    for (int x : stalls) {
        if (x - last >= dist) {
            cows++;
            last = x;
        }
    }
    return cows >= k;
}

// ── maxMinDistance: maximum possible minimum distance ───────────────────────
//   1) stalls sort karo
//   2) lo=0, hi=max gap — BS on distance
//   3) canPlace(mid) -> ans=mid, aur bada try (lo=mid+1)
int maxMinDistance(vector<int> stalls, int k) {
    sort(stalls.begin(), stalls.end());
    int lo = 0, hi = stalls.back() - stalls[0], ans = 0;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (canPlace(stalls, k, mid)) {
            ans = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return ans;
}

int main() {
    vector<int> stalls = {1, 2, 7, 10, 11};
    int k = 3;
    cout << "Max minimum distance = " << maxMinDistance(stalls, k) << endl;
    return 0;
}
