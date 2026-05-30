#include <bits/stdc++.h>
using namespace std;

const double EPS = 1E-9;

int compute_rank(vector<vector<double>> A)
{
    int n = A.size(), m = A[0].size();
    int rank = 0;
    vector<bool> row_selected(n, false);

    for (int col = 0; col < m; ++col)
    {
        int pivot_row = -1;

        // Find a pivot row
        for (int row = 0; row < n; ++row)
        {
            if (!row_selected[row] && abs(A[row][col]) > EPS)
            {
                pivot_row = row;
                break;
            }
        }

        if (pivot_row == -1)
            continue; // No valid pivot in this column

        row_selected[pivot_row] = true;
        rank++;

        // Normalize pivot row
        for (int j = col + 1; j < m; ++j)
            A[pivot_row][j] /= A[pivot_row][col];

        // Eliminate current column from all other rows
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

    cout << "Rank of the matrix: " << compute_rank(matrix) << endl;
    return 0;
}
