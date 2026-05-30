/*
 * ============================================================================
 * TOPIC    : Fenwick Tree — 2D
 * FILE     : fenwick_tree_2d.cpp
 * PROBLEM  : 2D grid — point update + submatrix sum query
 * APPROACH : 2D BIT — update/add at (x,y), query prefix sum
 * COMPLEX  : Update/Query O(log n * log m)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

struct Fenwick2D {
    int n, m;
    vector<vector<long long>> bit;

    Fenwick2D(int n, int m) : n(n), m(m), bit(n + 1, vector<long long>(m + 1, 0)) {}

    void add(int x, int y, long long val) {
        for (int i = x; i <= n; i += i & -i)
            for (int j = y; j <= m; j += j & -j)
                bit[i][j] += val;
    }

    long long sum(int x, int y) const {
        long long res = 0;
        for (int i = x; i > 0; i -= i & -i)
            for (int j = y; j > 0; j -= j & -j)
                res += bit[i][j];
        return res;
    }

    // submatrix sum [1,x1]x[1,y1] to [x2,y2] (1-indexed)
    long long rectSum(int x1, int y1, int x2, int y2) const {
        return sum(x2, y2) - sum(x1 - 1, y2) - sum(x2, y1 - 1) + sum(x1 - 1, y1 - 1);
    }

    void setValue(int x, int y, long long val) {
        add(x, y, val); // use diff if replacing: add(x,y, val - current)
    }
};

int main() {
    int n = 4, m = 4;
    Fenwick2D fw(n, m);

    vector<vector<int>> grid = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            fw.add(i, j, grid[i - 1][j - 1]);

    cout << "Submatrix sum (2,2) to (3,3) = " << fw.rectSum(2, 2, 3, 3) << endl;

    fw.add(2, 2, 5); // +5 at (2,2)
    cout << "After +5 at (2,2): " << fw.rectSum(2, 2, 3, 3) << endl;
    return 0;
}
