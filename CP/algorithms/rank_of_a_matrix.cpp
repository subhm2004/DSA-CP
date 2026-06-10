#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// RANK OF A MATRIX — Gaussian Elimination (Row Echelon Form)
// ────────────────────────────────────────────────────────────────────────────
// Rank = kitni linearly independent rows/columns hain.
// Har column me pivot dhundho, pivot row normalize karo, baaki rows se eliminate.
// EPS se floating point zero check (abs(x) > EPS).
// Complexity: O(n * m * min(n,m))
// ════════════════════════════════════════════════════════════════════════════

const double EPS = 1E-9;

// ── compute_rank: matrix ka rank nikalo ─────────────────────────────────────
//   1) har column col pe pivot row dhundho (abs(A[row][col]) > EPS)
//   2) pivot nahi mila -> column skip (dependent), warna rank++
//   3) pivot row normalize: A[pivot][j] /= A[pivot][col] for j > col
//   4) baaki rows se column col eliminate karo (row reduction)
//   5) pivot row ko row_selected mark karo — dobara use mat karo
int compute_rank(vector<vector<double>> A)
{
    int n = A.size(), m = A[0].size();
    int rank = 0;
    vector<bool> row_selected(n, false);

    for (int col = 0; col < m; ++col)
    {
        int pivot_row = -1;

        // pivot: is column me pehli unused row jisme non-zero entry ho
        for (int row = 0; row < n; ++row)
        {
            if (!row_selected[row] && abs(A[row][col]) > EPS)
            {
                pivot_row = row;
                break;
            }
        }

        if (pivot_row == -1)
            continue; // is column me koi independent direction nahi

        row_selected[pivot_row] = true;
        rank++;

        // pivot row ko 1 banao (leading coefficient normalize)
        for (int j = col + 1; j < m; ++j)
            A[pivot_row][j] /= A[pivot_row][col];

        // baaki rows se is column ko zero karo
        for (int row = 0; row < n; ++row)
        {
            if (row != pivot_row && abs(A[row][col]) > EPS)
            {
                double factor = A[row][col];
                for (int j = col + 1; j < m; ++j)
                    A[row][j] -= factor * A[pivot_row][j];
            }
        }
    }

    return rank;
}

int main()
{
    vector<vector<double>> matrix = {
        {2, 4, 1},
        {1, 2, 1},
        {3, 6, 2}};

    cout << "Rank of the matrix: " << compute_rank(matrix) << endl; // expected: 2
    return 0;
}
