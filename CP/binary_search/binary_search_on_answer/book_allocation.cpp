/*
 * ============================================================================
 * TOPIC    : Binary Search on Answer
 * FILE     : book_allocation.cpp
 * PROBLEM  : Allocate books to M students — minimize max pages
 * APPROACH : BS on answer (max pages), greedy check
 * COMPLEX  : Time: O(n log(sum))  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// BOOK ALLOCATION — M students, minimize maximum pages assigned to one student
// ────────────────────────────────────────────────────────────────────────────
// BS on answer = max pages cap per student
// canAllocate: greedy — books sequentially jodo jab tak cap exceed na ho
// lo = max single book, hi = total sum
// MIN answer pattern
// ════════════════════════════════════════════════════════════════════════════

// ── canAllocate: maxPages cap pe M students me baant sakte hain? ────────────
//   1) koi book > maxPages -> impossible
//   2) greedy: curr student me jodo, exceed ho to naya student
//   3) students used <= M -> true
bool canAllocate(const vector<int> &pages, int students, int maxPages) {
    int count = 1, curr = 0;
    for (int p : pages) {
        if (p > maxPages)
            return false;
        if (curr + p <= maxPages)
            curr += p;
        else {
            count++;
            curr = p;
        }
    }
    return count <= students;
}

// ── minMaxPages: minimum possible maximum pages ─────────────────────────────
//   1) lo = sabse badi book, hi = total pages
//   2) mid possible -> ans update, chhota try (hi=mid-1)
int minMaxPages(const vector<int> &pages, int students) {
    if ((int)students > (int)pages.size())
        return -1;

    int lo = *max_element(pages.begin(), pages.end());
    int hi = accumulate(pages.begin(), pages.end(), 0);
    int ans = hi;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (canAllocate(pages, students, mid)) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return ans;
}

int main() {
    vector<int> pages = {12, 34, 67, 90};
    int students = 2;
    cout << "Minimum max pages = " << minMaxPages(pages, students) << endl;
    return 0;
}
