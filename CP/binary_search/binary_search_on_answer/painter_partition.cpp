/*
 * ============================================================================
 * TOPIC    : Binary Search on Answer
 * FILE     : painter_partition.cpp
 * PROBLEM  : K painters, boards with lengths — minimize max time
 * APPROACH : BS on answer (max time per painter), greedy partition
 * COMPLEX  : Time: O(n log(sum))  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// PAINTER'S PARTITION — K painters, boards sequentially paint karo
// ────────────────────────────────────────────────────────────────────────────
// BS on answer = max time ek painter ko (book allocation jaisa hi)
// canPaint: greedy partition — boards jodo jab tak maxTime exceed na ho
// MIN answer: minimize maximum load on any painter
// ════════════════════════════════════════════════════════════════════════════

// ── canPaint: maxTime cap pe K painters kaafi hain? ─────────────────────────
//   1) board > maxTime -> impossible
//   2) greedy: curr painter me jodo, exceed -> naya painter
//   3) painters used <= k -> true
bool canPaint(const vector<int> &boards, int k, int maxTime) {
    int painters = 1, curr = 0;
    for (int b : boards) {
        if (b > maxTime)
            return false;
        if (curr + b <= maxTime)
            curr += b;
        else {
            painters++;
            curr = b;
        }
    }
    return painters <= k;
}

// ── minPaintTime: minimum possible maximum paint time ───────────────────────
//   1) lo = max board, hi = total sum
//   2) BS: possible -> ans=mid, hi=mid-1 (minimize)
int minPaintTime(const vector<int> &boards, int k) {
    int lo = *max_element(boards.begin(), boards.end());
    int hi = accumulate(boards.begin(), boards.end(), 0);
    int ans = hi;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (canPaint(boards, k, mid)) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return ans;
}

int main() {
    vector<int> boards = {5, 10, 30, 20, 15};
    int k = 3;
    cout << "Minimum paint time = " << minPaintTime(boards, k) << endl;
    return 0;
}
