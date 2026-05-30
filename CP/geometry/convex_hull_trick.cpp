/*
 * ============================================================================
 * TOPIC    : Computational Geometry — Convex Hull Trick
 * FILE     : convex_hull_trick.cpp
 * PROBLEM  : Minimize m*x + b queries with increasing x (DP optimization)
 * APPROACH : Maintain lower hull of lines, binary search best line
 * COMPLEX  : Insert amortized O(1), Query O(log n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

struct Line {
    long long m, b;
    long long eval(long long x) const { return m * x + b; }
};

struct ConvexHullTrick {
    deque<Line> hull;

    bool bad(const Line &l1, const Line &l2, const Line &l3) {
        // Intersection(l1,l2) >= intersection(l2,l3)
        return (l3.b - l1.b) * (l1.m - l2.m) >= (l2.b - l1.b) * (l1.m - l3.m);
    }

    void add(long long m, long long b) {
        Line nl{m, b};
        while (hull.size() >= 2 && bad(hull[hull.size() - 2], hull.back(), nl))
            hull.pop_back();
        hull.push_back(nl);
    }

    long long query(long long x) {
        while (hull.size() >= 2 && hull[0].eval(x) >= hull[1].eval(x))
            hull.pop_front();
        return hull.front().eval(x);
    }
};

int main() {
    ConvexHullTrick cht;
    cht.add(2, 3);  // y = 2x + 3
    cht.add(0, 10); // y = 10
    cht.add(4, -5); // y = 4x - 5

    cout << "Min at x=5: " << cht.query(5) << endl;
    cout << "Min at x=1: " << cht.query(1) << endl;
    return 0;
}
