/*
 * ============================================================================
 * TOPIC    : Computational Geometry — Convex Hull (Graham's Scan)
 * FILE     : graham_scan_convex_hull.cpp
 * PROBLEM  : Smallest convex polygon containing all given points
 * APPROACH : Graham's scan (1972) — polar sort + stack
 * REF      : https://cp-algorithms.com/geometry/convex-hull.html
 * COMPLEX  : Time: O(n log n)  |  Space: O(n)
 * ============================================================================
 *
 * STEPS
 * -----
 * 1. Bottom-most point p0 (min y; tie → min x)
 * 2. Sort other points by polar angle around p0 (clockwise)
 *    Tie-break: nearer to p0 first
 * 3. Stack scan: pop while last turn is not clockwise
 * 4. Result: hull vertices in clockwise order
 *
 * See graham_scan_convex_hull.md for when to use vs monotone chain.
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;

    bool operator==(const Point &t) const { return x == t.x && y == t.y; }
};

// Twice the signed area of triangle (a, b, c); sign = orientation
// ── orientation: triangle (a,b,c) ka turn — -1 CW, +1 CCW, 0 collinear ───
long long orientation(const Point &a, const Point &b, const Point &c) {
    long long v = a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
    if (v < 0) return -1; // clockwise
    if (v > 0) return 1;  // counter-clockwise
    return 0;             // collinear
}

// ── cw: clockwise turn? include_collinear pe collinear bhi allow ───────────
bool cw(const Point &a, const Point &b, const Point &c, bool include_collinear) {
    int o = orientation(a, b, c);
    return o < 0 || (include_collinear && o == 0);
}

bool collinear(const Point &a, const Point &b, const Point &c) {
    return orientation(a, b, c) == 0;
}

static long long dist2(const Point &p0, const Point &p) {
    long long dx = p0.x - p.x, dy = p0.y - p.y;
    return dx * dx + dy * dy;
}

// ── convex_hull_graham: Graham scan se hull nikalo (in-place modify) ────────
//   1) p0 = bottom-most point (min y, tie min x)
//   2) baaki points polar angle se sort around p0 (clockwise)
//   3) stack scan: non-CW turn pe pop, phir push
//   4) result stack = hull vertices clockwise order me
void convex_hull_graham(vector<Point> &a, bool include_collinear = false) {
    if (a.empty()) return;

    Point p0 = *min_element(a.begin(), a.end(), [](const Point &u, const Point &v) {
        return make_pair(u.y, u.x) < make_pair(v.y, v.x);
    });

    sort(a.begin(), a.end(), [&p0](const Point &u, const Point &v) {
        int o = orientation(p0, u, v);
        if (o == 0)
            return dist2(p0, u) < dist2(p0, v);
        return o < 0; // clockwise polar order around p0
    });

    if (include_collinear) {
        int i = (int)a.size() - 1;
        while (i >= 0 && collinear(p0, a[i], a.back())) i--;
        reverse(a.begin() + i + 1, a.end());
    }

    vector<Point> st;
    for (const Point &p : a) {
        while (st.size() > 1 && !cw(st[st.size() - 2], st.back(), p, include_collinear))
            st.pop_back();
        st.push_back(p);
    }

    if (!include_collinear && st.size() == 2 && st[0] == st[1])
        st.pop_back();

    a = std::move(st);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<Point> pts = {
        {0, 0}, {4, 0}, {4, 4}, {0, 4}, {2, 2}, {1, 3}, {3, 1},
    };

    cout << "=== Graham's Scan Convex Hull ===\n\n";
    cout << "Input points: " << pts.size() << "\n";

    convex_hull_graham(pts, false);
    cout << "Hull vertices (strict, no collinear on edges): " << pts.size() << "\n";
    for (const Point &p : pts)
        cout << "  (" << p.x << ", " << p.y << ")\n";

    vector<Point> line = {{0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}};
    convex_hull_graham(line, true);
    cout << "\nCollinear line with include_collinear=true: " << line.size() << " points on hull\n";

    return 0;
}
