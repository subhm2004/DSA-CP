#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// 2D PREFIX SUM — matrix pe O(1) sub-rectangle sum
// ────────────────────────────────────────────────────────────────────────────
// prefix[i][j] = sum of rectangle (1,1) to (i,j) — 1-indexed
// Inclusion-exclusion formula:
//   sum(a,b,c,d) = P[c][d] - P[a-1][d] - P[c][b-1] + P[a-1][b-1]
//
// Kab use: static grid, bahut saari submatrix sum queries
// Mat use: updates zyada → 2D Fenwick / 2D seg tree
// COMPLEX: build O(n*m)  |  query O(1)
// ════════════════════════════════════════════════════════════════════════════

class PrefixSum2D
{
public:
    int n, m;
    vector<vector<int>> prefix;

    // ── PrefixSum2D: 2D prefix table build (1-indexed) ──
    //   1) prefix size (n+1) x (m+1), sab 0
    //   2) prefix[i][j] = arr[i-1][j-1] + up + left - overlap (top-left)
    //   Diagram:
    //        +-------+
    //        | TL | T |
    //        +----+---+
    //        | L  | X |   X = current cell
    //        +----+---+
    //   prefix[i][j] = X + prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1]
    PrefixSum2D(vector<vector<int>> &arr)
    {
        n = arr.size();
        m = arr[0].size();
        prefix.assign(n + 1, vector<int>(m + 1, 0));

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                prefix[i][j] = arr[i - 1][j - 1] + prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1];
            }
        }
    }

    // ── getSum: rectangle (a,b) top-left se (c,d) bottom-right — 1-indexed, inclusive ──
    //   Inclusion-exclusion: poora - up strip - left strip + double-subtracted corner
    int getSum(int a, int b, int c, int d)
    {
        return prefix[c][d] - prefix[a - 1][d] - prefix[c][b - 1] + prefix[a - 1][b - 1];
    }
};

int main()
{
    vector<vector<int>> arr = {
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20},
        {21, 22, 23, 24, 25}};

    PrefixSum2D ps(arr);

    cout << "Sum (2,2) to (4,4) = " << ps.getSum(2, 2, 4, 4) << "\n"; // 7+8+9+12+13+14+17+18+19
    cout << "Sum (1,1) to (5,5) = " << ps.getSum(1, 1, 5, 5) << "\n"; // poora grid
    cout << "Sum (3,3) to (5,5) = " << ps.getSum(3, 3, 5, 5) << "\n"; // bottom-right 3x3

    return 0;
}
