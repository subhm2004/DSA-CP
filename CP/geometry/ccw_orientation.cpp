/*
 * ============================================================================
 * TOPIC    : Computational Geometry
 * FILE     : ccw_orientation.cpp
 * PROBLEM  : Orientation of triplet (counter-clockwise / clockwise / collinear)
 * APPROACH : Cross product sign
 * COMPLEX  : Time: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// CCW ORIENTATION — Teen points ka turn direction
// ────────────────────────────────────────────────────────────────────────────
// Cross product (b-a) × (c-b) ka sign:
//   > 0 -> counter-clockwise (CCW)
//   < 0 -> clockwise (CW)
//   = 0 -> collinear (teeno ek line pe)
// Convex hull, segment intersection me core building block
// ════════════════════════════════════════════════════════════════════════════

struct Point {
    long long x, y;
};

// ── orientation: a→b→c ka turn direction ──────────────────────────────────
//   1) val = cross product of vectors (b-a) and (c-b)
//   2) val == 0 -> collinear (0 return)
//   3) val > 0 -> CCW (2), val < 0 -> CW (1)
int orientation(const Point &a, const Point &b, const Point &c) {
    long long val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
    if (val == 0)
        return 0;
    return (val > 0) ? 1 : 2;
}

int main() {
    Point a{0, 0}, b{4, 4}, c{1, 2};
    int o = orientation(a, b, c);
    cout << "Orientation: ";
    if (o == 0)
        cout << "collinear\n";
    else if (o == 1)
        cout << "clockwise\n";
    else
        cout << "counter-clockwise\n";
    return 0;
}
