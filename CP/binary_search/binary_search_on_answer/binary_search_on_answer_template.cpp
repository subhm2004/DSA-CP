/*
 * ============================================================================
 * TOPIC    : Binary Search on Answer
 * FILE     : binary_search_on_answer_template.cpp
 * PROBLEM  : Generic template — find min/max X such that isPossible(X)
 * APPROACH : Binary search on answer range [lo, hi]
 * COMPLEX  : Time: O(log(range) * check(X))  |  Space: O(1)
 * ============================================================================
 *
 * Pattern:
 *   1. Identify monotonic predicate isPossible(mid)
 *   2. lo = minimum possible answer, hi = maximum possible answer
 *   3. For MIN answer: if possible → ans=mid, hi=mid-1 else lo=mid+1
 *   4. For MAX answer: if possible → ans=mid, lo=mid+1 else hi=mid-1
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// BINARY SEARCH ON ANSWER — Template
// ────────────────────────────────────────────────────────────────────────────
// Answer space [lo, hi] pe binary search — array pe nahi!
// isPossible(mid) monotonic hona chahiye (false...false true...true ya ulta)
// MIN answer: possible ho to ans=mid, aur chhota dhundho (hi=mid-1)
// MAX answer: possible ho to ans=mid, aur bada dhundho (lo=mid+1)
// ════════════════════════════════════════════════════════════════════════════

// ── isPossible: mid answer valid hai ya nahi (problem-specific) ───────────
//   1) yahan example: mid^2 >= 50
//   2) real problems me greedy/simulation check lagao
bool isPossible(int mid) {
    return mid * mid >= 50;
}

// ── binarySearchOnAnswerMin: sabse chhota valid answer ──────────────────────
//   1) mid possible -> ans update, left me aur chhota dhundho (hi=mid-1)
//   2) impossible -> lo=mid+1 (bada answer chahiye)
//   3) ans return — minimum feasible X
int binarySearchOnAnswerMin(int lo, int hi) {
    int ans = -1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (isPossible(mid)) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return ans;
}

// ── binarySearchOnAnswerMax: sabse bada valid answer ────────────────────────
//   1) mid possible -> ans update, right me aur bada dhundho (lo=mid+1)
//   2) impossible -> hi=mid-1
int binarySearchOnAnswerMax(int lo, int hi) {
    int ans = -1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (isPossible(mid)) {
            ans = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return ans;
}

int main() {
    cout << "Min X with X^2 >= 50: " << binarySearchOnAnswerMin(0, 100) << endl;
    cout << "Max X with X^2 <= 50: " << binarySearchOnAnswerMax(0, 100) << endl;
    return 0;
}
