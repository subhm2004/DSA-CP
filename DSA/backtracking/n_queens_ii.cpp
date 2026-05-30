/*
 * ============================================================================
 * TOPIC    : Backtracking — N-Queens II (count only)
 * FILE     : n_queens_ii.cpp
 * PROBLEM  : Count distinct solutions for n-queens
 * LEETCODE : 52 — N-Queens II
 * APPROACH : Same as N-Queens; count instead of store boards
 * COMPLEX  : Time: O(n!)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
    int ans = 0;
    vector<bool> col, diag1, diag2;

    void solve(int row, int n) {
        if (row == n) {
            ans++;
            return;
        }
        for (int c = 0; c < n; c++) {
            int d1 = row - c + n - 1, d2 = row + c;
            if (col[c] || diag1[d1] || diag2[d2]) continue;
            col[c] = diag1[d1] = diag2[d2] = true;
            solve(row + 1, n);
            col[c] = diag1[d1] = diag2[d2] = false;
        }
    }

public:
    int totalNQueens(int n) {
        col.assign(n, false);
        diag1.assign(2 * n - 1, false);
        diag2.assign(2 * n - 1, false);
        solve(0, n);
        return ans;
    }
};

int main() {
    Solution s;
    cout << s.totalNQueens(4) << endl; // 2
    return 0;
}
