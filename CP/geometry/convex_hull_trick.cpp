/*
 * ============================================================================
 * TOPIC    : Computational Geometry — Convex Hull Trick
 * FILE     : convex_hull_trick.cpp
 * PROBLEM  : Minimize m*x + b queries with increasing x (DP optimization)
 * APPROACH : Maintain lower hull of lines, binary search best line
 * COMPLEX  : Insert amortized O(1), Query O(log n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// CONVEX HULL TRICK (CHT) — Minimize lines y = mx + b at query x
// ────────────────────────────────────────────────────────────────────────────
// Lines add karte waqt slopes increasing honi chahiye (typical DP use)
// bad(l1,l2,l3): l3 makes l2 useless on hull (intersection order wrong)
// query(x): front se pop jab next line cheaper ho
// DP optimization: dp[i] = min over j of dp[j] + cost(j,i)
// ════════════════════════════════════════════════════════════════════════════

struct Line {
    long long m, b;
    long long eval(long long x) const { return m * x + b; }
};

struct ConvexHullTrick {
    deque<Line> hull;

    // ── bad: middle line l2 redundant hai? ──────────────────────────────────
    //   1) l1-l2 aur l2-l3 ke intersection compare karo
    //   2) agar l1-l2 intersection >= l2-l3 -> l2 kabhi optimal nahi
    bool bad(const Line &l1, const Line &l2, const Line &l3) {
        return (l3.b - l1.b) * (l1.m - l2.m) >= (l2.b - l1.b) * (l1.m - l3.m);
    }

    // ── add: nayi line mx+b hull me daalo ───────────────────────────────────
    //   1) jab tak last 2 + new line me bad() true -> pop_back
    //   2) nayi line push_back
    void add(long long m, long long b) {
        Line nl{m, b};
        while (hull.size() >= 2 && bad(hull[hull.size() - 2], hull.back(), nl))
            hull.pop_back();
        hull.push_back(nl);
    }

    // ── query: x pe minimum value ───────────────────────────────────────────
    //   1) front se pop jab hull[1] x pe cheaper ho
    //   2) hull.front().eval(x) return
    long long query(long long x) {
        while (hull.size() >= 2 && hull[0].eval(x) >= hull[1].eval(x))
            hull.pop_front();
        return hull.front().eval(x);
    }
};

int main() {
    ConvexHullTrick cht;
    cht.add(2, 3);
    cht.add(0, 10);
    cht.add(4, -5);

    cout << "Min at x=5: " << cht.query(5) << endl;
    cout << "Min at x=1: " << cht.query(1) << endl;
    return 0;
}
