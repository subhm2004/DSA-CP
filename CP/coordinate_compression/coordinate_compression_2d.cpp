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

// ════════════════════════════════════════════════════════════════════════════
// 2D COORDINATE COMPRESSION
// ────────────────────────────────────────────────────────────────────────────
// X aur Y alag-alag compress hote hain (unique sort + rank).
// cx(x), cy(y) -> 1-indexed ranks (2D BIT ke liye convenient).
// Grid size = unique x count x unique y count (bahut chhota ho jaata hai).
// ════════════════════════════════════════════════════════════════════════════

struct Compress2D {
    vector<int> xs, ys;  // unique sorted x aur y values

    // ── Constructor: saare points se unique x,y nikaal ke sort karo ─────────
    //   1) har point ka x aur y alag vectors me collect karo
    //   2) dono vectors ko sort karo (rank ke liye order chahiye)
    //   3) unique() se duplicate coordinates hatao
    //   4) ab xs/ys me sirf distinct coordinates hain — 2D grid chhota ban jaata hai
    Compress2D(const vector<pair<int, int>> &pts) {
        for (auto [x, y] : pts)
            xs.push_back(x), ys.push_back(y);
        sort(xs.begin(), xs.end());
        sort(ys.begin(), ys.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());
    }

    // ── cx: x ko compressed 1-indexed rank me convert karo ──────────────────
    //   1) sorted xs me lower_bound se x ki position dhoondo
    //   2) index 0-based hai, isliye +1 karke 1-indexed rank banao
    //   3) 2D BIT me index 1 se shuru karna convenient hota hai
    int cx(int x) const {
        return (int)(lower_bound(xs.begin(), xs.end(), x) - xs.begin()) + 1;
    }

    // ── cy: y ko compressed 1-indexed rank me convert karo ──────────────────
    //   1) sorted ys me lower_bound se y ki position dhoondo
    //   2) index + 1 = compressed y rank (1-indexed)
    //   3) x aur y alag compress hote hain — grid size = |xs| x |ys|
    int cy(int y) const {
        return (int)(lower_bound(ys.begin(), ys.end(), y) - ys.begin()) + 1;
    }

    // ── compress: (x,y) point ko (cx, cy) ranks me convert karo ─────────────
    //   1) cx(x) se x ka rank nikalo
    //   2) cy(y) se y ka rank nikalo
    //   3) pair {cx, cy} return karo — ab 2D BIT pe update/query kar sakte ho
    pair<int, int> compress(int x, int y) const {
        return {cx(x), cy(y)};
    }

    // ── xCount: kitne unique x coordinates compress hue ─────────────────────
    //   1) xs vector ka size = compressed x dimension
    //   2) 2D BIT ki width yahi decide karti hai
    int xCount() const { return (int)xs.size(); }

    // ── yCount: kitne unique y coordinates compress hue ─────────────────────
    //   1) ys vector ka size = compressed y dimension
    //   2) 2D BIT ki height yahi decide karti hai
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
