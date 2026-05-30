/*
 * ============================================================================
 * TOPIC    : Sparse Table — RMQ
 * FILE     : sparse_table_rmq_gcd.cpp
 * PROBLEM  : Static range GCD query
 * APPROACH : Sparse table with __gcd (idempotent — query is exact)
 * COMPLEX  : Build O(n log n), Query O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
#include <numeric>
using namespace std;

struct SparseTableGCD {
    vector<vector<int>> st;
    vector<int> log2;

    SparseTableGCD(const vector<int> &a) {
        int n = a.size();
        log2.assign(n + 1, 0);
        for (int i = 2; i <= n; i++)
            log2[i] = log2[i / 2] + 1;

        int K = log2[n] + 1;
        st.assign(K, vector<int>(n));
        st[0] = a;

        for (int j = 1; j < K; j++) {
            for (int i = 0; i + (1 << j) <= n; i++)
                st[j][i] = gcd(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
        }
    }

    int query(int l, int r) const {
        int j = log2[r - l + 1];
        return gcd(st[j][l], st[j][r - (1 << j) + 1]);
    }
};

int main() {
    vector<int> a = {12, 18, 6, 24, 36};
    SparseTableGCD st(a);
    cout << "GCD [1, 3] = " << st.query(1, 3) << endl;
    return 0;
}
