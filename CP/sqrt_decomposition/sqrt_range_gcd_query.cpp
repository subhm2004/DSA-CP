#include <bits/stdc++.h>
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * SQRT — Range GCD Query + Point Update
 * ════════════════════════════════════════════════════════════════════════════
 *
 * PROBLEM:
 *   Non-invertible GCD — Fenwick nahi chalega.
 *   Point update + range GCD query — sqrt decomposition se O(sqrt n).
 *
 * APPROACH:
 *   Har block ka precomputed GCD store.
 *   Query: partial scan + merge full block GCDs + partial scan.
 *   Update: arr[i] change → us block ka GCD rebuild O(sqrt n).
 *
 * Time: query O(sqrt n) | update O(sqrt n)
 * ════════════════════════════════════════════════════════════════════════════
 */

int gcdInt(int a, int b) {
    while (b) { int t = a % b; a = b; b = t; }
    return a;
}

class SqrtGCD {
private:
    vector<int> arr;
    vector<int> blockGcd;
    int n, blockSize, numBlocks;

    void rebuild(int b) {
        int g = 0;
        int s = b * blockSize;
        int e = min(n, (b + 1) * blockSize);
        for (int i = s; i < e; i++)
            g = gcdInt(g, arr[i]);
        blockGcd[b] = g;
    }

public:
    SqrtGCD(const vector<int>& a) : arr(a) {
        n = (int)arr.size();
        blockSize = max(1, (int)sqrt(n));
        numBlocks = (n + blockSize - 1) / blockSize;
        blockGcd.assign(numBlocks, 0);
        for (int b = 0; b < numBlocks; b++)
            rebuild(b);
    }

    void update(int idx, int val) {
        arr[idx] = val;
        rebuild(idx / blockSize);
    }

    int query(int l, int r) {
        int ans = 0;
        while (l <= r && l % blockSize != 0)
            ans = gcdInt(ans, arr[l++]);

        while (l + blockSize - 1 <= r) {
            ans = gcdInt(ans, blockGcd[l / blockSize]);
            l += blockSize;
        }

        while (l <= r)
            ans = gcdInt(ans, arr[l++]);

        return ans;
    }
};

int main() {
    vector<int> a = {12, 18, 24, 36, 48, 60};
    SqrtGCD st(a);

    cout << "Array: ";
    for (int x : a) cout << x << " ";
    cout << "\nGCD(0,5) = " << st.query(0, 5) << " (6)\n";
    cout << "GCD(1,3) = " << st.query(1, 3) << " (6)\n";

    st.update(2, 10);
    cout << "After arr[2]=10: GCD(0,5) = " << st.query(0, 5) << "\n";

    return 0;
}
