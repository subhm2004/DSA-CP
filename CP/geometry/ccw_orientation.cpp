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

struct Point {
    long long x, y;
};

int orientation(const Point &a, const Point &b, const Point &c) {
    long long val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
    if (val == 0)
        return 0;  // collinear
    return (val > 0) ? 1 : 2; // 1=clockwise, 2=counter-clockwise
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
