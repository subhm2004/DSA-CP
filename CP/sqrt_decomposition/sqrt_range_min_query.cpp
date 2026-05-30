/*
 * ============================================================================
 * TOPIC    : Square Root Decomposition
 * FILE     : sqrt_range_min_query.cpp
 * PROBLEM  : Range minimum query with point updates
 * APPROACH : Blocks of size sqrt(n) — lazy block recompute
 * COMPLEX  : Query/Update O(sqrt n)  |  Build O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

struct SqrtRMQ {
    vector<int> a, blockMin;
    int n, blockSize, numBlocks;

    SqrtRMQ(const vector<int> &arr) : a(arr) {
        n = a.size();
        blockSize = max(1, (int)sqrt(n));
        numBlocks = (n + blockSize - 1) / blockSize;
        blockMin.assign(numBlocks, INT_MAX);
        for (int i = 0; i < n; i++)
            blockMin[i / blockSize] = min(blockMin[i / blockSize], a[i]);
    }

    void update(int idx, int val) {
        a[idx] = val;
        int b = idx / blockSize;
        blockMin[b] = INT_MAX;
        for (int i = b * blockSize; i < min(n, (b + 1) * blockSize); i++)
            blockMin[b] = min(blockMin[b], a[i]);
    }

    int query(int l, int r) {
        int ans = INT_MAX;
        while (l <= r && l % blockSize != 0)
            ans = min(ans, a[l++]);
        while (l + blockSize - 1 <= r) {
            ans = min(ans, blockMin[l / blockSize]);
            l += blockSize;
        }
        while (l <= r)
            ans = min(ans, a[l++]);
        return ans;
    }
};

int main() {
    vector<int> a = {7, 2, 3, 0, 5, 10, 3, 12};
    SqrtRMQ st(a);
    cout << "RMQ [1,4] = " << st.query(1, 4) << endl;
    st.update(3, 8);
    cout << "After update idx 3 -> 8, RMQ [1,4] = " << st.query(1, 4) << endl;
    return 0;
}
