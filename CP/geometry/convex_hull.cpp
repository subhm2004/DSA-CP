/*
 * ============================================================================
 * TOPIC    : Computational Geometry — Convex Hull
 * FILE     : convex_hull.cpp
 * PROBLEM  : Smallest convex polygon containing all points
 * APPROACH : Andrew's monotone chain (1979) — sort by x + two-stack scan
 * REF      : https://cp-algorithms.com/geometry/convex-hull.html (Implementation 2)
 * NOTE     : Graham's scan → graham_scan_convex_hull.cpp + graham_scan_convex_hull.md
 * COMPLEX  : Time: O(n log n)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// ANDREW'S MONOTONE CHAIN — Convex Hull
// ────────────────────────────────────────────────────────────────────────────
// Points x se sort, lower hull + upper hull alag scan
// Stack se pop jab turn non-left (cross <= 0)
// Graham se simpler — polar sort ki zaroorat nahi
// ════════════════════════════════════════════════════════════════════════════

struct Point {
    long long x, y;
};

// ── cross: vectors (o→a) × (o→b) ka signed area ───────────────────────────
long long cross(const Point &o, const Point &a, const Point &b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

// ── convexHull: Andrew's monotone chain ─────────────────────────────────────
//   1) points sort by (x, y), duplicates hatao
//   2) lower hull: left se right scan, non-left turn pe pop
//   3) upper hull: right se left scan, same rule
//   4) hull resize — last duplicate point hatao
vector<Point> convexHull(vector<Point> pts) {
    sort(pts.begin(), pts.end(), [](const Point &a, const Point &b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    });
    pts.erase(unique(pts.begin(), pts.end(),
                     [](const Point &a, const Point &b) {
                         return a.x == b.x && a.y == b.y;
                     }),
              pts.end());

    int n = pts.size();
    if (n <= 1) return pts;

    vector<Point> hull(2 * n);
    int k = 0;

    // lower hull — left to right
    for (int i = 0; i < n; i++) {
        while (k >= 2 && cross(hull[k - 2], hull[k - 1], pts[i]) <= 0) k--;
        hull[k++] = pts[i];
    }
    // upper hull — right to left
    for (int i = n - 2, t = k + 1; i >= 0; i--) {
        while (k >= t && cross(hull[k - 2], hull[k - 1], pts[i]) <= 0) k--;
        hull[k++] = pts[i];
    }
    hull.resize(k - 1);
    return hull;
}

// ── hullPerimeter: Manhattan perimeter of hull ──────────────────────────────
//   1) har consecutive pair (including wrap) ka |dx|+|dy| jodo
long long hullPerimeter(const vector<Point> &hull) {
    long long per = 0;
    int n = hull.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        per += llabs(hull[j].x - hull[i].x) + llabs(hull[j].y - hull[i].y);
    }
    return per;
}

int main() {
    vector<Point> pts = {{0, 0}, {4, 0}, {4, 4}, {0, 4}, {2, 2}, {1, 3}};
    auto hull = convexHull(pts);
    cout << "Hull size = " << hull.size() << endl;
    cout << "Perimeter (Manhattan) = " << hullPerimeter(hull) << endl;
    return 0;
}
