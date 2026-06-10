/*
 * ============================================================================
 * TOPIC    : Computational Geometry — Ray Casting
 * FILE     : ray_casting_algorithm.cpp
 * PROBLEM  : Point inside polygon? (odd-even crossing rule)
 * APPROACH : Cast horizontal ray; count edge crossings
 * COMPLEX  : Time: O(n)  |  Space: O(1)
 * NOTE     : Edge cases → use winding_number.cpp
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// RAY CASTING — Point in polygon (even-odd rule)
// ────────────────────────────────────────────────────────────────────────────
// Point P se rightward horizontal ray maaro
// Har edge crossing count karo — odd = andar, even = bahar
// Edge P.y ko cross kare tab hi count (strict inequality)
// Concave polygons pe bhi kaam karta hai (winding se simpler par edge cases zyada)
// ════════════════════════════════════════════════════════════════════════════

struct Point {
    double x, y;
};

// ── pointInPolygon: ray casting se andar/bahar check ────────────────────────
//   1) har edge (A,B): ray P.y ko cross karta hai?
//   2) cross ho to intersection x nikalo — P.x < xIntersect pe count++
//   3) crossings odd -> true (andar)
bool pointInPolygon(vector<Point> &polygon, Point P) {
    int n = polygon.size();
    int crossings = 0;

    for (int i = 0; i < n; i++) {
        Point A = polygon[i];
        Point B = polygon[(i + 1) % n];

        // edge P.y ko straddle kare (ek upar ek neeche)
        if ((A.y <= P.y && B.y > P.y) || (B.y <= P.y && A.y > P.y)) {
            double xIntersect = A.x + (P.y - A.y) / (B.y - A.y) * (B.x - A.x);
            if (P.x < xIntersect)
                crossings++;
        }
    }
    return crossings % 2 == 1;
}

int main() {
    vector<Point> polygon = {{0, 0}, {4, 0}, {4, 4}, {0, 4}};
    cout << boolalpha;
    cout << pointInPolygon(polygon, {2, 2}) << endl; // true
    cout << pointInPolygon(polygon, {5, 5}) << endl; // false
    return 0;
}
