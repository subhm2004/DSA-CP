/*
 * ============================================================================
 * TOPIC    : Computational Geometry — Oriented (Signed) Triangle Area
 * FILE     : oriented_triangle_area.cpp
 * PROBLEM  : Signed area of triangle (p1, p2, p3); orientation; unsigned area
 * APPROACH : 2×2 determinant / 2D cross product of edges p1→p2 and p2→p3
 * REF      : CP-Algorithms — Oriented area of a triangle
 * COMPLEX  : Time: O(1) per query
 * ============================================================================
 *
 * SIGNED AREA (orientation)
 * -------------------------
 * Imagine you stand at p1 facing p2, walk to p2:
 *   • p3 is to your RIGHT  → clockwise turn  → signed area < 0
 *   • p3 is to your LEFT   → counter-clockwise → signed area > 0
 *   • p1, p2, p3 collinear → area = 0
 *
 * MATH
 * ----
 * Parallelogram spanned by vectors (p2−p1) and (p3−p2) has signed area:
 *
 *   2S = | x2−x1   x3−x2 |
 *        | y2−y1   y3−y2 |
 *      = (x2−x1)(y3−y2) − (x3−x2)(y2−y1)
 *      = cross(p2 − p1, p3 − p2)
 *
 * Triangle area = |2S| / 2 = |signed_parallelogram_area| / 2
 *
 * USES
 * ----
 * • Convex hull (Andrew / Graham): pop while turn is not CCW
 * • Polygon area (shoelace) builds on same cross idea
 * • Point-in-polygon / orientation tests
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// ORIENTED TRIANGLE AREA — Signed area + orientation
// ────────────────────────────────────────────────────────────────────────────
// cross(p2-p1, p3-p2) = 2× signed triangle area (parallelogram area)
// Sign batata hai p3, p1→p2 ke left/right me hai
// Convex hull pop, polygon area, orientation — sab isi pe based
// ════════════════════════════════════════════════════════════════════════════

struct Point2d {
    long long x, y;
};

// ── operator-: vector b se a tak ka displacement ───────────────────────────
Point2d operator-(const Point2d &a, const Point2d &b) {
    return {a.x - b.x, a.y - b.y};
}

// ── cross: 2D cross product a × b (signed parallelogram area) ───────────────
long long cross(const Point2d &a, const Point2d &b) {
    return a.x * b.y - a.y * b.x;
}

// ── signed_area_parallelogram: edges p1→p2 aur p2→p3 se 2× triangle area ──
long long signed_area_parallelogram(const Point2d &p1, const Point2d &p2, const Point2d &p3) {
    return cross(p2 - p1, p3 - p2);
}

// ── triangle_area: unsigned area (|2S|/2) ─────────────────────────────────
double triangle_area(const Point2d &p1, const Point2d &p2, const Point2d &p3) {
    return abs(signed_area_parallelogram(p1, p2, p3)) / 2.0;
}

// ── triangle_area2: |2S| integer (lattice / exact use) ─────────────────────
long long triangle_area2(const Point2d &p1, const Point2d &p2, const Point2d &p3) {
    return abs(signed_area_parallelogram(p1, p2, p3));
}

// ── collinear: teen points ek line pe? (2S == 0) ──────────────────────────
bool collinear(const Point2d &p1, const Point2d &p2, const Point2d &p3) {
    return signed_area_parallelogram(p1, p2, p3) == 0;
}

// ── clockwise: p1→p2 chalte waqt p3 right side pe? (2S < 0) ────────────────
bool clockwise(const Point2d &p1, const Point2d &p2, const Point2d &p3) {
    return signed_area_parallelogram(p1, p2, p3) < 0;
}

// ── counter_clockwise: p3 left side pe? (2S > 0) ──────────────────────────
bool counter_clockwise(const Point2d &p1, const Point2d &p2, const Point2d &p3) {
    return signed_area_parallelogram(p1, p2, p3) > 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Right triangle: (0,0) → (4,0) → (0,3)
    // Walk 0→4 along x-axis; (0,3) is to the left → counter-clockwise → positive area
    Point2d p1{0, 0}, p2{4, 0}, p3{0, 3};

    cout << fixed << setprecision(1);
    cout << "=== Oriented Triangle Area ===\n\n";

    long long signed2 = signed_area_parallelogram(p1, p2, p3);
    cout << "Points: p1(0,0) p2(4,0) p3(0,3)\n";
    cout << "signed parallelogram area (2S) = " << signed2 << "\n";
    cout << "triangle area                  = " << triangle_area(p1, p2, p3) << "\n";
    cout << "orientation                    = "
         << (collinear(p1, p2, p3) ? "collinear"
             : counter_clockwise(p1, p2, p3) ? "counter-clockwise"
             : "clockwise")
         << "\n\n";

    // Collinear: all on a line
    Point2d a{0, 0}, b{2, 2}, c{4, 4};
    cout << "Collinear (0,0)-(2,2)-(4,4): area = " << triangle_area(a, b, c)
         << ", signed2 = " << signed_area_parallelogram(a, b, c) << "\n";

    // Clockwise example: (0,0) → (4,0) → (4,-3) — p3 to the right when going 0→4
    Point2d q1{0, 0}, q2{4, 0}, q3{4, -3};
    cout << "Clockwise (0,0)-(4,0)-(4,-3): signed2 = "
         << signed_area_parallelogram(q1, q2, q3)
         << ", clockwise = " << (clockwise(q1, q2, q3) ? "yes" : "no") << "\n";

    return 0;
}
