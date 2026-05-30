/*
 * ============================================================================
 * TOPIC    : Segment Tree — 2D (Segment tree of segment trees)
 * FILE     : segment_tree_2d.cpp
 * PROBLEM  : 2D grid point update + submatrix sum
 * APPROACH : Outer segtree on rows, inner segtree on columns
 * COMPLEX  : O(log n * log m)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

struct SegTree2D {
    int n, m;
    vector<vector<long long>> st; // st[row_node][col_node]

    SegTree2D(const vector<vector<int>> &a) {
        n = a.size();
        m = a[0].size();
        st.assign(4 * max(n, 1), vector<long long>(4 * max(m, 1), 0));
        buildX(1, 0, n - 1, a);
    }

    void buildY(int vx, int vy, int ty, int tyy, const vector<vector<int>> &a, int x) {
        if (ty == tyy) {
            st[vx][vy] = a[x][ty];
            return;
        }
        int tmy = (ty + tyy) / 2;
        buildY(vx, vy * 2, ty, tmy, a, x);
        buildY(vx, vy * 2 + 1, tmy + 1, tyy, a, x);
        st[vx][vy] = st[vx][vy * 2] + st[vx][vy * 2 + 1];
    }

    void buildX(int vx, int tx, int txx, const vector<vector<int>> &a) {
        if (tx == txx) {
            buildY(vx, 1, 0, m - 1, a, tx);
            return;
        }
        int tmx = (tx + txx) / 2;
        buildX(vx * 2, tx, tmx, a);
        buildX(vx * 2 + 1, tmx + 1, txx, a);
        for (int vy = 1; vy < 4 * m; vy++)
            st[vx][vy] = st[vx * 2][vy] + st[vx * 2 + 1][vy];
    }

    void updateY(int vx, int vy, int ty, int tyy, int y, long long val) {
        if (ty == tyy) {
            st[vx][vy] = val;
            return;
        }
        int tmy = (ty + tyy) / 2;
        if (y <= tmy) updateY(vx, vy * 2, ty, tmy, y, val);
        else updateY(vx, vy * 2 + 1, tmy + 1, tyy, y, val);
        st[vx][vy] = st[vx][vy * 2] + st[vx][vy * 2 + 1];
    }

    void updateX(int vx, int tx, int txx, int x, int y, long long val) {
        if (tx == txx) {
            updateY(vx, 1, 0, m - 1, y, val);
            return;
        }
        int tmx = (tx + txx) / 2;
        if (x <= tmx) updateX(vx * 2, tx, tmx, x, y, val);
        else updateX(vx * 2 + 1, tmx + 1, txx, x, y, val);
        for (int vy = 1; vy < 4 * m; vy++)
            st[vx][vy] = st[vx * 2][vy] + st[vx * 2 + 1][vy];
    }

    long long queryY(int vx, int vy, int ty, int tyy, int yl, int yr) const {
        if (yl > tyy || yr < ty) return 0;
        if (yl <= ty && tyy <= yr) return st[vx][vy];
        int tmy = (ty + tyy) / 2;
        return queryY(vx, vy * 2, ty, tmy, yl, yr) + queryY(vx, vy * 2 + 1, tmy + 1, tyy, yl, yr);
    }

    long long queryX(int vx, int tx, int txx, int xl, int xr, int yl, int yr) const {
        if (xl > txx || xr < tx) return 0;
        if (xl <= tx && txx <= xr) return queryY(vx, 1, 0, m - 1, yl, yr);
        int tmx = (tx + txx) / 2;
        return queryX(vx * 2, tx, tmx, xl, xr, yl, yr) + queryX(vx * 2 + 1, tmx + 1, txx, xl, xr, yl, yr);
    }

    void update(int x, int y, long long val) { updateX(1, 0, n - 1, x, y, val); }
    long long rectSum(int x1, int y1, int x2, int y2) {
        return queryX(1, 0, n - 1, x1, x2, y1, y2);
    }
};

int main() {
    vector<vector<int>> a = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    SegTree2D st(a);
    cout << "Sum (0,0)-(1,1) = " << st.rectSum(0, 0, 1, 1) << endl;
    st.update(1, 1, 100);
    cout << "After update: " << st.rectSum(0, 0, 2, 2) << endl;
    return 0;
}
