#include <bits/stdc++.h>
using namespace std;

class Segment_Tree2D {
    int n, m;
    vector<vector<int>> segTree;

    // ─── Build Y ─────────────────────────────────────────────────
    void buildY(int nx, int sx, int ex,
                int ny, int sy, int ey,
                vector<vector<int>>& mat) {

        if (sy == ey) {
            segTree[nx][ny] = (sx == ex) ? mat[sx][sy]
                                         : segTree[2*nx+1][ny] + segTree[2*nx+2][ny];
            return;
        }
        int my = (sy + ey) >> 1;
        buildY(nx, sx, ex, 2*ny+1, sy,   my, mat);
        buildY(nx, sx, ex, 2*ny+2, my+1, ey, mat);
        segTree[nx][ny] = segTree[nx][2*ny+1] + segTree[nx][2*ny+2];
    }

    // ─── Query Y ─────────────────────────────────────────────────
    int queryY(int nx,
               int ny, int sy, int ey,
               int qly, int qry) {

        if (qry < sy || ey < qly) return 0;
        if (qly <= sy && ey <= qry) return segTree[nx][ny];

        int my = (sy + ey) >> 1;
        return queryY(nx, 2*ny+1, sy,   my, qly, qry)
             + queryY(nx, 2*ny+2, my+1, ey, qly, qry);
    }

    // ─── Update Y ────────────────────────────────────────────────
    void updateY(int nx, int sx, int ex,
                 int ny, int sy, int ey,
                 int x, int y, int val) {

        if (sy == ey) {
            segTree[nx][ny] = (sx == ex) ? val
                                         : segTree[2*nx+1][ny] + segTree[2*nx+2][ny];
            return;
        }
        int my = (sy + ey) >> 1;
        if (y <= my) updateY(nx, sx, ex, 2*ny+1, sy,   my, x, y, val);
        else         updateY(nx, sx, ex, 2*ny+2, my+1, ey, x, y, val);
        segTree[nx][ny] = segTree[nx][2*ny+1] + segTree[nx][2*ny+2];
    }

    // ─── Build X ─────────────────────────────────────────────────
    void buildX(int nx, int sx, int ex,
                vector<vector<int>>& mat) {
        if (sx != ex) {
            int mx = (sx + ex) >> 1;
            buildX(2*nx+1, sx,   mx, mat);
            buildX(2*nx+2, mx+1, ex, mat);
        }
        buildY(nx, sx, ex, 0, 0, m-1, mat);
    }

    // ─── Query X ─────────────────────────────────────────────────
    int queryX(int nx, int sx, int ex,
               int qlx, int qrx,
               int qly, int qry) {

        if (qrx < sx || ex < qlx) return 0;
        if (qlx <= sx && ex <= qrx) return queryY(nx, 0, 0, m-1, qly, qry);

        int mx = (sx + ex) >> 1;
        return queryX(2*nx+1, sx,   mx, qlx, qrx, qly, qry)
             + queryX(2*nx+2, mx+1, ex, qlx, qrx, qly, qry);
    }

    // ─── Update X ────────────────────────────────────────────────
    void updateX(int nx, int sx, int ex,
                 int x, int y, int val) {
        if (sx != ex) {
            int mx = (sx + ex) >> 1;
            if (x <= mx) updateX(2*nx+1, sx,   mx, x, y, val);
            else         updateX(2*nx+2, mx+1, ex, x, y, val);
        }
        updateY(nx, sx, ex, 0, 0, m-1, x, y, val);
    }

public:
  Segment_Tree2D(vector<vector<int>>& mat) {
    n = mat.size();
    m = mat[0].size();
    segTree.assign(4*n, vector<int>(4*m, 0));
    buildX(0, 0, n-1, mat);
}

    int query(int x1, int y1, int x2, int y2) {
        return queryX(0, 0, n-1, x1, x2, y1, y2);
    }

    void update(int x, int y, int val) {
        updateX(0, 0, n-1, x, y, val);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    vector<vector<int>> mat = {
        { 1,  2,  3,  4},
        { 5,  6,  7,  8},
        { 9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    Segment_Tree2D seg(mat);

    cout << seg.query(0, 0, 3, 3) << "\n";  // 136
    cout << seg.query(1, 1, 2, 2) << "\n";  // 34
    seg.update(1, 1, 100);
    cout << seg.query(1, 1, 2, 2) << "\n";  // 128

    return 0;
}
