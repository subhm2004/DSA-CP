/*
 * ============================================================================
 * TOPIC    : Fenwick Tree — Range Update, Point Query
 * FILE     : fenwick_range_update.cpp
 * PROBLEM  : Range add on array, query value at index i
 * APPROACH : Difference array technique on BIT
 * COMPLEX  : O(log n) per update/query
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<long long> bit;

    Fenwick(int n) : n(n), bit(n + 2, 0) {}

    void add(int i, long long v) {
        for (; i <= n; i += i & -i)
            bit[i] += v;
    }

    long long prefix(int i) const {
        long long s = 0;
        for (; i > 0; i -= i & -i)
            s += bit[i];
        return s;
    }

    void rangeAdd(int l, int r, long long v) {
        add(l, v);
        add(r + 1, -v);
    }

    long long pointQuery(int i) const { return prefix(i); }
};

int main() {
    int n = 5;
    Fenwick fw(n);
    fw.rangeAdd(1, 3, 10); // indices 1..3 += 10
    fw.rangeAdd(2, 4, 5);

    for (int i = 1; i <= n; i++)
        cout << "arr[" << i << "] = " << fw.pointQuery(i) << endl;
    return 0;
}
