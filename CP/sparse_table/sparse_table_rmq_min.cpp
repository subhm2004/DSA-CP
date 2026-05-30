/*
 * ============================================================================
 * TOPIC    : Sparse Table — RMQ
 * FILE     : sparse_table_rmq_min.cpp
 * PROBLEM  : Static range minimum query on array
 * APPROACH : Precompute st[j][i] = min on range [i, i+2^j)
 * COMPLEX  : Build O(n log n), Query O(1)  |  Space: O(n log n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

struct SparseTableMin {
    vector<vector<int>> st;
    vector<int> log2;

    SparseTableMin(const vector<int> &a) {
        int n = a.size();
        log2.assign(n + 1, 0);
        for (int i = 2; i <= n; i++)
            log2[i] = log2[i / 2] + 1;

        int K = log2[n] + 1;
        st.assign(K, vector<int>(n));
        st[0] = a;

        for (int j = 1; j < K; j++) {
            for (int i = 0; i + (1 << j) <= n; i++)
                st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
        }
    }

    int query(int l, int r) const {
        int j = log2[r - l + 1];
        return min(st[j][l], st[j][r - (1 << j) + 1]);
    }
};

int main() {
    vector<int> a = {7, 2, 3, 0, 5, 10, 3, 12, 18};
    SparseTableMin st(a);

    cout << "RMQ min [1, 4] = " << st.query(1, 4) << endl;
    cout << "RMQ min [0, 8] = " << st.query(0, 8) << endl;
    return 0;
}
