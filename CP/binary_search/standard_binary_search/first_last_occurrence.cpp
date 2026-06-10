/*
 * ============================================================================
 * TOPIC    : Standard Binary Search
 * FILE     : first_last_occurrence.cpp
 * PROBLEM  : First and last index of target in sorted array
 * APPROACH : lower_bound + upper_bound - 1
 * COMPLEX  : Time: O(log n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// FIRST & LAST OCCURRENCE — Sorted array me duplicate target
// ────────────────────────────────────────────────────────────────────────────
// first = lower_bound index
// last  = upper_bound index - 1
// target nahi mila -> {-1, -1}
// ════════════════════════════════════════════════════════════════════════════

// ── firstLast: target ka pehla aur aakhri index ───────────────────────────
//   1) lower_bound se pehla >= target index lo
//   2) agar end pe ya value != target -> target nahi hai
//   3) upper_bound - 1 = last occurrence index
//   4) {first, last} return karo
pair<int, int> firstLast(const vector<int> &a, int target) {
    auto lb = lower_bound(a.begin(), a.end(), target);
    if (lb == a.end() || *lb != target)
        return {-1, -1};
    auto ub = upper_bound(a.begin(), a.end(), target);
    return {(int)(lb - a.begin()), (int)(ub - a.begin()) - 1};
}

int main() {
    vector<int> a = {1, 2, 2, 2, 3, 4, 5};
    auto [f, l] = firstLast(a, 2);
    cout << "First = " << f << ", Last = " << l << endl;
    return 0;
}
