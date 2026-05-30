/*
 * ============================================================================
 * TOPIC    : Computational Geometry — Line Intersection Point
 * FILE     : lines_intersection_point.cpp
 * PROBLEM  : Intersection point of two infinite lines (if not parallel)
 * APPROACH : Cross product / Cramer's rule on line equations
 * COMPLEX  : Time: O(1)  |  Space: O(1)
 * NOTE     : Segment intersection check → line_intersection.cpp
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x, y;
};

// Returns true if lines (a,b) and (c,d) intersect; writes point in `out`
bool lineIntersection(const Point &a, const Point &b, const Point &c, const Point &d,
                      Point &out) {
    double a1 = b.y - a.y, b1 = a.x - b.x, c1 = a1 * a.x + b1 * a.y;
    double a2 = d.y - c.y, b2 = c.x - d.x, c2 = a2 * c.x + b2 * c.y;
    double det = a1 * b2 - a2 * b1;
    if (fabs(det) < 1e-9) return false; // parallel or coincident
    out.x = (b2 * c1 - b1 * c2) / det;
    out.y = (a1 * c2 - a2 * c1) / det;
    return true;
}

bool onSegment(const Point &p, const Point &a, const Point &b) {
    return min(a.x, b.x) - 1e-9 <= p.x && p.x <= max(a.x, b.x) + 1e-9 &&
           min(a.y, b.y) - 1e-9 <= p.y && p.y <= max(a.y, b.y) + 1e-9;
}

int main() {
    Point a{0, 0}, b{4, 4}, c{0, 4}, d{4, 0}, p;
    if (lineIntersection(a, b, c, d, p))
        cout << fixed << setprecision(2) << p.x << " " << p.y << endl; // 2.00 2.00
    else
        cout << "Parallel\n";
    return 0;
}
