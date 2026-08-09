#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// 2D PREFIX SUM (0-INDEXED) — matrix pe O(1) sub-rectangle sum
// ────────────────────────────────────────────────────────────────────────────
// prefix[i][j] = rectangle (0,0) se (i,j) tak ka sum — INCLUSIVE
//                yaani i-th row aur j-th col dono andar hain
//
// Inclusion-exclusion query:
//   getSum(r1,c1,r2,c2) = P[r2][c2] - P[r1-1][c2] - P[r2][c1-1] + P[r1-1][c1-1]
//
// NOTE: 0-indexed rakhne ka cost = i-1 / j-1 "-1" ban sakta hai, isliye
//       har term pe ternary guard lagta hai (out of bound → 0 maan lo).
//       Padded (n+1)x(m+1) version me guard nahi lagta par index shift
//       yaad rakhna padta hai. Trade-off hai, dono theek hain.
//
// Kab use: static grid, bahut saari submatrix sum queries
// Mat use: updates zyada → 2D Fenwick / 2D seg tree
// COMPLEX: build O(n*m)  |  query O(1)  |  space O(n*m)
// ════════════════════════════════════════════════════════════════════════════

class PrefixSum2D
{
public:
    int n, m;
    vector<vector<int>> prefix;   // size n x m — arr jitna hi, koi padding nahi

    // ── Build: 2D prefix table (0-indexed) ──
    //   Har cell pe: current + upar ka block + left ka block - double counted corner
    //
    //   Diagram (current cell X = arr[i][j]):
    //          j-1    j
    //        +-----+-----+
    //   i-1  | TL  |  T  |     prefix[i-1][j]   = TL + T   (upar ka pura block)
    //        +-----+-----+     prefix[i][j-1]   = TL + L   (left ka pura block)
    //    i   |  L  |  X  |     dono ke andar TL hai → ek baar minus karo
    //        +-----+-----+
    //
    //   prefix[i][j] = arr[i][j] + prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1]
    //
    //   i == 0  → upar kuch nahi   → us term ko 0 maano
    //   j == 0  → left kuch nahi   → us term ko 0 maano
    PrefixSum2D(vector<vector<int>> &arr)
    {
        n = arr.size();
        m = arr[0].size();
        prefix.assign(n, vector<int>(m, 0));

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                prefix[i][j] = arr[i][j]
                             + (i > 0            ? prefix[i - 1][j]     : 0)   // T  strip
                             + (j > 0            ? prefix[i][j - 1]     : 0)   // L  strip
                             - (i > 0 && j > 0   ? prefix[i - 1][j - 1] : 0);  // TL overlap
            }
        }
    }

    // ── getSum: (r1,c1) top-left se (r2,c2) bottom-right — 0-indexed, INCLUSIVE ──
    //
    //   Diagram (X = jo chahiye):
    //        0          c1-1  c1        c2
    //      0 +-----------+------------+
    //        |    TL     |     T      |    TL = prefix[r1-1][c1-1]
    //   r1-1 +-----------+------------+    T  = upar ki unwanted strip
    //   r1   |    L      |     X      |    L  = left ki unwanted strip
    //   r2   +-----------+------------+
    //
    //   prefix[r2][c2]      = TL + T + L + X   (poora block)
    //   - prefix[r1-1][c2]  = TL + T hataya
    //   - prefix[r2][c1-1]  = TL + L hataya
    //   + prefix[r1-1][c1-1]= TL do baar kat gaya tha, wapas jodo
    //   ────────────────────────────────────────
    //   = X                                          ✓
    //
    //   r1 == 0 → upar koi strip hi nahi  → term 0
    //   c1 == 0 → left koi strip hi nahi  → term 0
    int getSum(int r1, int c1, int r2, int c2)
    {
        return prefix[r2][c2]
             - (r1 > 0            ? prefix[r1 - 1][c2]     : 0)
             - (c1 > 0            ? prefix[r2][c1 - 1]     : 0)
             + (r1 > 0 && c1 > 0  ? prefix[r1 - 1][c1 - 1] : 0);
    }
};

int main()
{
    vector<vector<int>> arr = {
        { 1,  2,  3,  4,  5},
        { 6,  7,  8,  9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20},
        {21, 22, 23, 24, 25}};

    PrefixSum2D ps(arr);

    // middle 3x3 → 7+8+9 + 12+13+14 + 17+18+19
    cout << "Sum (1,1) to (3,3) = " << ps.getSum(1, 1, 3, 3) << "\n";   // 117

    // poora grid → 1+2+...+25
    cout << "Sum (0,0) to (4,4) = " << ps.getSum(0, 0, 4, 4) << "\n";   // 325

    // bottom-right 3x3 → 13+14+15 + 18+19+20 + 23+24+25
    cout << "Sum (2,2) to (4,4) = " << ps.getSum(2, 2, 4, 4) << "\n";   // 171

    // ── edge cases: boundary guards kaam kar rahe hain ya nahi ──
    cout << "Sum (0,0) to (0,0) = " << ps.getSum(0, 0, 0, 0) << "\n";   // 1   (single cell, corner)
    cout << "Sum (4,4) to (4,4) = " << ps.getSum(4, 4, 4, 4) << "\n";   // 25  (single cell, last)
    cout << "Sum (0,2) to (2,2) = " << ps.getSum(0, 2, 2, 2) << "\n";   // 24  (r1=0, ek column strip: 3+8+13)

    return 0;
}
