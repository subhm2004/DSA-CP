/*
 * ============================================================================
 * TOPIC    : Coordinate Compression — 2D
 * FILE     : coordinate_compression_2d.cpp
 * PROBLEM  : Compress (x,y) pairs for 2D BIT / grid problems
 * APPROACH : Sort unique x and y separately, map to ranks
 * COMPLEX  : Time: O(n log n)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

struct Compress2D {
    vector<int> xs, ys;

    Compress2D(const vector<pair<int, int>> &pts) {
        for (auto [x, y] : pts)
            xs.push_back(x), ys.push_back(y);
        sort(xs.begin(), xs.end());
        sort(ys.begin(), ys.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());
    }

    int cx(int x) const {
        return (int)(lower_bound(xs.begin(), xs.end(), x) - xs.begin()) + 1;
    }

    int cy(int y) const {
        return (int)(lower_bound(ys.begin(), ys.end(), y) - ys.begin()) + 1;
    }

    pair<int, int> compress(int x, int y) const {
        return {cx(x), cy(y)};
    }

    int xCount() const { return (int)xs.size(); }
    int yCount() const { return (int)ys.size(); }
};

int main() {
    vector<pair<int, int>> pts = {{100, 500}, {50, 500}, {100, 200}, {50, 200}};
    Compress2D cc(pts);

    cout << "2D compressed points (1-indexed ranks):\n";
    for (auto [x, y] : pts) {
        auto [cx, cy] = cc.compress(x, y);
        cout << "(" << x << "," << y << ") -> (" << cx << "," << cy << ")\n";
    }
    cout << "Grid size: " << cc.xCount() << " x " << cc.yCount() << endl;
    return 0;
}
