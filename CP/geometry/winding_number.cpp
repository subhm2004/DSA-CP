/*
 * ============================================================================
 * TOPIC    : Computational Geometry — Winding Number
 * FILE     : winding_number.cpp
 * PROBLEM  : Point inside polygon? (robust vs ray casting on edges)
 * APPROACH : Count how many times polygon winds around point
 * COMPLEX  : Time: O(n)  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// WINDING NUMBER — Point in polygon (robust)
// ────────────────────────────────────────────────────────────────────────────
// Polygon point ke around kitni baar "wind" karta hai count karo
// winding == 0 -> bahar, non-zero -> andar (concave pe bhi sahi)
// Ray casting se zyada robust edge/vertex cases pe
// ════════════════════════════════════════════════════════════════════════════

struct Point
{
    double x, y;
};

// ── windingNumber: point P polygon ke andar hai? ────────────────────────────
//   1) har edge (A,B) ke liye upward/downward crossing check
//   2) upward cross + P left of edge -> winding++
//   3) downward cross + P right of edge -> winding--
//   4) non-zero winding = andar
int windingNumber(vector<Point> &polygon, Point P)
{
    int n = polygon.size();
    int winding = 0;

    for (int i = 0; i < n; i++)
    {
        Point A = polygon[i];
        Point B = polygon[(i + 1) % n]; // Last vertex → First vertex

        if (A.y <= P.y)
        {
            if (B.y > P.y)
            {
                // Upward crossing — edge neeche se upar gayi
                // Cross product: P, AB ke left mein hai?
                double cp = (B.x - A.x) * (P.y - A.y) -
                            (P.x - A.x) * (B.y - A.y);
                if (cp > 0)
                    winding++; // Left mein → count karo
            }
        }
        else
        {
            if (B.y <= P.y)
            {
                // Downward crossing — edge upar se neeche gayi
                double cp = (B.x - A.x) * (P.y - A.y) -
                            (P.x - A.x) * (B.y - A.y);
                if (cp < 0)
                    winding--; // Right mein → count karo
            }
        }
    }
    return winding; // 0 = outside, non-zero = inside
}

// ── checkPoint: test point print karo ───────────────────────────────────────
void checkPoint(vector<Point> &polygon, Point P, string name)
{
    int w = windingNumber(polygon, P);
    cout << name << " (" << P.x << "," << P.y << ") → ";
    if (w != 0)
        cout << "ANDAR hai ✅ (winding=" << w << ")" << endl;
    else
        cout << "BAHAR hai ❌ (winding=" << w << ")" << endl;
}

int main()
{

    // ------------------------------------------------
    // Test 1: Simple Square
    //
    //   (0,4)-----(4,4)
    //     |         |
    //     |         |
    //   (0,0)-----(4,0)
    // ------------------------------------------------
    cout << "=== Test 1: Square ===" << endl;
    vector<Point> square = {
        {0, 0}, {4, 0}, {4, 4}, {0, 4}};

    checkPoint(square, {2, 2}, "Center     "); // Andar
    checkPoint(square, {5, 5}, "Outside    "); // Bahar
    checkPoint(square, {1, 1}, "Corner near"); // Andar
    checkPoint(square, {4, 4}, "On vertex  "); // Edge case
    cout << endl;

    // ------------------------------------------------
    // Test 2: Triangle
    //
    //       (2,4)
    //      /     \
    //   (0,0)---(4,0)
    // ------------------------------------------------
    cout << "=== Test 2: Triangle ===" << endl;
    vector<Point> triangle = {
        {0, 0}, {4, 0}, {2, 4}};

    checkPoint(triangle, {2, 1}, "Inside     "); // Andar
    checkPoint(triangle, {3, 3}, "Outside    "); // Bahar
    checkPoint(triangle, {2, 2}, "Middle     "); // Andar
    cout << endl;

    // ------------------------------------------------
    // Test 3: L-Shaped Polygon (complex)
    //
    //   *---*
    //   |   |
    //   *-* |
    //     | |
    //     *-*
    // ------------------------------------------------
    cout << "=== Test 3: L-Shape ===" << endl;
    vector<Point> lshape = {
        {0, 0}, {2, 0}, {2, 2}, {4, 2}, {4, 6}, {0, 6}};

    checkPoint(lshape, {1, 1}, "Bottom-left"); // Andar
    checkPoint(lshape, {3, 4}, "Top-right  "); // Andar
    checkPoint(lshape, {1, 4}, "Top-left   "); // Andar
    checkPoint(lshape, {3, 1}, "Gap area   "); // Bahar
    cout << endl;

    // ------------------------------------------------
    // Test 4: Concave Polygon
    //
    //   *-------*
    //   |   *   |
    //   |  / \  |
    //   | /   \ |
    //   |/     \|
    //   *-------*
    //      (star jaisa)
    // ------------------------------------------------
    cout << "=== Test 4: Concave Polygon ===" << endl;
    vector<Point> concave = {
        {0, 0}, {4, 0}, {4, 4}, {2, 2}, // indent — andar ki taraf dhansa
        {0, 4}};

    checkPoint(concave, {1, 1}, "Bottom-left"); // Andar
    checkPoint(concave, {3, 3}, "Near indent"); // Bahar (concave part)
    checkPoint(concave, {2, 1}, "Bottom-mid "); // Andar

    return 0;
}