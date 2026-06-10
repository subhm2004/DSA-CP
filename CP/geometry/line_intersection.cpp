/*
 * ============================================================================
 * TOPIC    : Computational Geometry
 * FILE     : line_intersection.cpp
 * PROBLEM  : Check if two line segments intersect
 * APPROACH : Orientation (ccw) tests for segment intersection
 * COMPLEX  : Time: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// SEGMENT INTERSECTION — Do line segments cut each other?
// ────────────────────────────────────────────────────────────────────────────
// cross(o,a,b) = signed area of parallelogram (o→a, o→b)
// General case: endpoints alag sides pe hon (opposite orientation signs)
// Special case: collinear + point segment pe ho -> intersect
// ════════════════════════════════════════════════════════════════════════════

struct Point {
    long long x, y;
};

// ── cross: point o se vectors oa aur ob ka 2D cross product ───────────────
//   1) (a-o) × (b-o) ka z-component
//   2) sign batata hai b, oa ke left/right me hai
long long cross(const Point &o, const Point &a, const Point &b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

// ── onSegment: point p segment [a,b] pe hai? ────────────────────────────────
//   1) p ka x aur y dono [a,b] ke bounding box me hon
//   2) collinear check alag se cross se hota hai
bool onSegment(const Point &p, const Point &a, const Point &b) {
    return min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
           min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}

// ── segmentsIntersect: segments (p1,p2) aur (p3,p4) intersect? ────────────
//   1) d1,d2 = p3-p4 line ke relative to p1,p2 — opposite signs -> straddle
//   2) d3,d4 = p1-p2 line ke relative to p3,p4 — same check
//   3) collinear cases: endpoint dusre segment pe ho to true
bool segmentsIntersect(Point p1, Point p2, Point p3, Point p4) {
    long long d1 = cross(p3, p4, p1);
    long long d2 = cross(p3, p4, p2);
    long long d3 = cross(p1, p2, p3);
    long long d4 = cross(p1, p2, p4);

    if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
        ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0)))
        return true;

    if (d1 == 0 && onSegment(p1, p3, p4))
        return true;
    if (d2 == 0 && onSegment(p2, p3, p4))
        return true;
    if (d3 == 0 && onSegment(p3, p1, p2))
        return true;
    if (d4 == 0 && onSegment(p4, p1, p2))
        return true;

    return false;
}

int main() {
    Point a{0, 0}, b{4, 4}, c{0, 4}, d{4, 0};
    cout << "Segments intersect? " << (segmentsIntersect(a, b, c, d) ? "YES" : "NO") << endl;
    return 0;
}
