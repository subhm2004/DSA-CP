/*
 * ============================================================================
 * TOPIC    : Persistent Segment Tree
 * FILE     : persistent_segment_tree.cpp
 * PROBLEM  : Versioned range sum — update creates new version
 * APPROACH : Path copying — new nodes only on update path
 * COMPLEX  : O(log n) per update/query
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

struct PST {
    struct Node {
        long long sum;
        int left, right;
    };

    vector<Node> nodes;
    vector<int> roots;
    int n;

    int newNode(long long sum, int l, int r) {
        nodes.push_back({sum, l, r});
        return (int)nodes.size() - 1;
    }

    int build(const vector<int> &a, int tl, int tr) {
        if (tl == tr)
            return newNode(a[tl], 0, 0);
        int tm = (tl + tr) / 2;
        int l = build(a, tl, tm);
        int r = build(a, tm + 1, tr);
        return newNode(nodes[l].sum + nodes[r].sum, l, r);
    }

    int update(int prev, int tl, int tr, int pos, int val) {
        if (tl == tr)
            return newNode(val, 0, 0);
        int tm = (tl + tr) / 2;
        if (pos <= tm) {
            int nl = update(nodes[prev].left, tl, tm, pos, val);
            return newNode(nodes[nl].sum + nodes[nodes[prev].right].sum, nl, nodes[prev].right);
        }
        int nr = update(nodes[prev].right, tm + 1, tr, pos, val);
        return newNode(nodes[nodes[prev].left].sum + nodes[nr].sum, nodes[prev].left, nr);
    }

    long long query(int root, int tl, int tr, int l, int r) const {
        if (l > tr || r < tl) return 0;
        if (l <= tl && tr <= r) return nodes[root].sum;
        int tm = (tl + tr) / 2;
        return query(nodes[root].left, tl, tm, l, r) + query(nodes[root].right, tm + 1, tr, l, r);
    }

    PST(const vector<int> &a) {
        n = (int)a.size();
        nodes.reserve(n * 25);
        roots.push_back(build(a, 0, n - 1));
    }

    int updateVersion(int ver, int pos, int val) {
        roots.push_back(update(roots[ver], 0, n - 1, pos, val));
        return (int)roots.size() - 1;
    }

    long long queryVersion(int ver, int l, int r) const {
        return query(roots[ver], 0, n - 1, l, r);
    }
};

int main() {
    vector<int> a = {1, 3, 5, 7, 9, 11};
    PST pst(a);

    cout << "v0 sum [1,3] = " << pst.queryVersion(0, 1, 3) << endl;
    int v1 = pst.updateVersion(0, 2, 100);
    cout << "v0 sum [1,3] = " << pst.queryVersion(0, 1, 3) << endl;
    cout << "v1 sum [1,3] = " << pst.queryVersion(v1, 1, 3) << endl;
    return 0;
}
