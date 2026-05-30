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

struct Point {
    long long x, y;
};

long long cross(const Point &o, const Point &a, const Point &b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

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

    for (int i = 0; i < n; i++) {
        while (k >= 2 && cross(hull[k - 2], hull[k - 1], pts[i]) <= 0) k--;
        hull[k++] = pts[i];
    }
    for (int i = n - 2, t = k + 1; i >= 0; i--) {
        while (k >= t && cross(hull[k - 2], hull[k - 1], pts[i]) <= 0) k--;
        hull[k++] = pts[i];
    }
    hull.resize(k - 1);
    return hull;
}

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
    cout << "Hull size = " << hull.size() << endl; // 4 (square corners)
    cout << "Perimeter (Manhattan) = " << hullPerimeter(hull) << endl;
    return 0;
}
