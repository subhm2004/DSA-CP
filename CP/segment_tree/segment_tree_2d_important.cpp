#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// 2D SEGMENT TREE (Important Template — tree-of-trees in 2D array)
// ────────────────────────────────────────────────────────────────────────────
// segTree[nx][ny] = row-tree node nx ke andar column-tree node ny.
//
// Params:
//   nx, sx, ex -> row dimension: node index + row range [sx, ex]
//   ny, sy, ey -> col dimension: node index + col range [sy, ey]
//   qlx,qrx / qly,qry -> query rectangle ke row/col bounds
//
// Build flow: buildX (rows) -> har X-node pe buildY (columns)
// Query flow: queryX (rows 3-case) -> full overlap pe queryY (columns 3-case)
// ════════════════════════════════════════════════════════════════════════════

class Segment_Tree2D {
    int n, m;
    vector<vector<int>> segTree;

    // ── buildY: ek fix row-node ke andar column-tree build karo ──
    //   1) sy==ey pe column leaf — agar row bhi leaf (sx==ex) to mat[sx][sy] copy
    //   2) column leaf par row internal ho to row-bachho ke is column ka sum lo
    //   3) column internal ho to mid split, left/right column subtrees build karo
    //   4) parent column node = left child sum + right child sum
    void buildY(int nx, int sx, int ex,
                int ny, int sy, int ey,
                vector<vector<int>>& mat) {

        if (sy == ey) {  // column leaf
            segTree[nx][ny] = (sx == ex) ? mat[sx][sy]  // row+col dono leaf → exact cell
                                         : segTree[2*nx+1][ny] + segTree[2*nx+2][ny];  // row merge
            return;
        }
        int my = (sy + ey) >> 1;
        buildY(nx, sx, ex, 2*ny+1, sy,   my, mat);   // left column half
        buildY(nx, sx, ex, 2*ny+2, my+1, ey, mat);   // right column half
        segTree[nx][ny] = segTree[nx][2*ny+1] + segTree[nx][2*ny+2];
    }

    // ── queryY: ek row-node ke andar columns [qly,qry] ka sum ──
    //   1) Case 1 NO overlap (qry<sy || ey<qly) — 0 return
    //   2) Case 2 FULL overlap — seedha segTree[nx][ny] return
    //   3) Case 3 PARTIAL — mid split, left+right column query sum jodo
    //   4) inner column dimension query — outer row-node nx already fix hai
    int queryY(int nx,
               int ny, int sy, int ey,
               int qly, int qry) {

        if (qry < sy || ey < qly) return 0;                    // Case 1: NO overlap
        if (qly <= sy && ey <= qry) return segTree[nx][ny];    // Case 2: FULL overlap

        int my = (sy + ey) >> 1;  // Case 3: PARTIAL overlap
        return queryY(nx, 2*ny+1, sy,   my, qly, qry)
             + queryY(nx, 2*ny+2, my+1, ey, qly, qry);
    }

    // ── updateY: ek row-node ke andar column y pe val set karo ──
    //   1) sy==ey pe column leaf — sx==ex ho to val set, warna row-bachho ka sum
    //   2) column internal ho to y <= mid se left/right child choose karo
    //   3) wapas aate waqt parent column sum refresh karo
    //   4) har X-node pe poora Y-tree update hota hai — tree-of-trees pattern
    void updateY(int nx, int sx, int ex,
                 int ny, int sy, int ey,
                 int x, int y, int val) {

        if (sy == ey) {  // column leaf
            segTree[nx][ny] = (sx == ex) ? val  // exact cell overwrite
                                         : segTree[2*nx+1][ny] + segTree[2*nx+2][ny];
            return;
        }
        int my = (sy + ey) >> 1;
        if (y <= my) updateY(nx, sx, ex, 2*ny+1, sy,   my, x, y, val);
        else         updateY(nx, sx, ex, 2*ny+2, my+1, ey, x, y, val);
        segTree[nx][ny] = segTree[nx][2*ny+1] + segTree[nx][2*ny+2];
    }

    // ── buildX: outer row dimension pe tree build karo ──
    //   1) agar sx != ex (row internal) to pehle left/right row children build karo
    //   2) har X-node (chahe leaf ho ya internal) pe buildY se poora column tree banao
    //   3) is template me har row-node apna complete inner Y-tree rakhta hai
    //   4) root nx=0 se start — poora n×m matrix cover ho jaata hai
    void buildX(int nx, int sx, int ex,
                vector<vector<int>>& mat) {
        if (sx != ex) {  // row internal — pehle bachho build karo
            int mx = (sx + ex) >> 1;
            buildX(2*nx+1, sx,   mx, mat);
            buildX(2*nx+2, mx+1, ex, mat);
        }
        buildY(nx, sx, ex, 0, 0, m-1, mat);  // har X-node pe poora Y-tree
    }

    // ── queryX: rectangle rows[qlx..qrx] × cols[qly..qry] ka sum ──
    //   1) Case 1 NO row overlap — 0 return
    //   2) Case 2 FULL row overlap — andar queryY se column range ka sum
    //   3) Case 3 PARTIAL row overlap — left+right row subtrees ka sum jodo
    //   4) nested 3-case: pehle rows filter, phir columns filter
    int queryX(int nx, int sx, int ex,
               int qlx, int qrx,
               int qly, int qry) {

        if (qrx < sx || ex < qlx) return 0;           // Case 1: NO row overlap
        if (qlx <= sx && ex <= qrx) return queryY(nx, 0, 0, m-1, qly, qry);  // Case 2: FULL row overlap

        int mx = (sx + ex) >> 1;  // Case 3: PARTIAL row overlap
        return queryX(2*nx+1, sx,   mx, qlx, qrx, qly, qry)
             + queryX(2*nx+2, mx+1, ex, qlx, qrx, qly, qry);
    }

    // ── updateX: cell (x,y) pe val set karo ──
    //   1) row internal ho (sx!=ex) to x <= mid se left/right row child me jao
    //   2) har visited X-node pe updateY call — us row range ke liye column update
    //   3) multiple X-nodes update hote hain kyunki har node apna Y-tree rakhta hai
    //   4) complexity O(log n * log m) — dono dimensions me descent
    void updateX(int nx, int sx, int ex,
                 int x, int y, int val) {
        if (sx != ex) {  // row internal — pehle sahi row child dhoondo
            int mx = (sx + ex) >> 1;
            if (x <= mx) updateX(2*nx+1, sx,   mx, x, y, val);
            else         updateX(2*nx+2, mx+1, ex, x, y, val);
        }
        updateY(nx, sx, ex, 0, 0, m-1, x, y, val);  // har X-node pe Y-tree update
    }

public:
    // ── Segment_Tree2D: constructor — matrix se 2D tree build ──
    //   1) n rows, m cols store karo
    //   2) segTree ko 4*n × 4*m 2D array allocate karo
    //   3) buildX(0, 0, n-1, mat) se root se poora tree construct karo
    Segment_Tree2D(vector<vector<int>>& mat) {
        n = mat.size();
        m = mat[0].size();
        segTree.assign(4*n, vector<int>(4*m, 0));
        buildX(0, 0, n-1, mat);
    }

    // ── query: public wrapper — submatrix sum ──
    //   1) (x1,y1) se (x2,y2) rectangle bounds lo
    //   2) queryX root (nx=0) se call — nested 3-case query handle hoti hai
    int query(int x1, int y1, int x2, int y2) {
        return queryX(0, 0, n-1, x1, x2, y1, y2);
    }

    // ── update: public wrapper — cell update ──
    //   1) (x,y) coordinates aur val lo
    //   2) updateX root se start — row+col dono me O(log) descent
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
