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

struct Point {
    double x, y;
};

bool pointInPolygon(vector<Point> &polygon, Point P) {
    int n = polygon.size();
    int crossings = 0;

    for (int i = 0; i < n; i++) {
        Point A = polygon[i];
        Point B = polygon[(i + 1) % n];

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
