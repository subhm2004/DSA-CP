/*
 * ============================================================================
 * TOPIC    : Two Pointers
 * FILE     : container_with_most_water.cpp
 * PROBLEM  : Max area between two vertical lines
 * APPROACH : Move pointer at shorter height inward
 * COMPLEX  : Time: O(n)  |  Space: O(1)
 * LEETCODE : 11 — Container With Most Water
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// CONTAINER WITH MOST WATER — Two Pointers Greedy
// ────────────────────────────────────────────────────────────────────────────
// Area = min(h[l], h[r]) * (r - l)  — pani ki height shorter wall se limit
// Greedy: hamesha SHORTER wall wala pointer andar move karo
//   Kyon? Width kam hogi, lekin shorter side ko chhodne se koi fayda nahi —
//   min height wahi rahegi. Taller side rakh ke behtar min dhundh sakte ho.
// COMPLEX: O(n) single pass
// ════════════════════════════════════════════════════════════════════════════

// ── maxArea: do lines ke beech max water area ──
//   1) l=0, r=n-1 — sabse wide container se start
//   2) current area = min(h[l],h[r]) * (r-l), best update karo
//   3) shorter height wala pointer move karo (equal ho to dono me se koi bhi)
//   4) jab tak l < r
int maxArea(vector<int> h)
{
    int l = 0, r = (int)h.size() - 1, best = 0;

    while (l < r)
    {
        best = max(best, min(h[l], h[r]) * (r - l));
        if (h[l] < h[r])
            l++; // left chhota hai — isko hata ke naya min try karo
        else
            r--; // right chhota (ya equal) — right andar lao
    }
    return best;
}

int main()
{
    vector<int> h = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    cout << "Max water area = " << maxArea(h) << endl; // 49 (8 aur 7 ke beech)
    return 0;
}
