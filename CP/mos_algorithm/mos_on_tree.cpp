/*
 * ============================================================================
 * TOPIC    : Mo's Algorithm on Tree
 * FILE     : mos_on_tree.cpp
 * PROBLEM  : Offline subtree/path frequency queries on tree
 * APPROACH : Euler tour flatten + Mo's with block sorting
 * COMPLEX  : O((n + q) * sqrt(n))
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

struct MoOnTree {
    int n, timer = 0, blockSize;
    vector<vector<int>> adj;
    vector<int> euler, first, last, depth, parent, value;
    vector<int> freq;
    long long curAns = 0;

    MoOnTree(int n) : n(n), adj(n), first(n), last(n), depth(n), parent(n, -1), value(n) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int u, int p) {
        first[u] = timer;
        euler.push_back(u);
        timer++;
        for (int v : adj[u]) {
            if (v == p) continue;
            depth[v] = depth[u] + 1;
            parent[v] = u;
            dfs(v, u);
        }
        last[u] = timer - 1;
    }

    struct Query {
        int l, r, idx;
    };

    void addRemove(int node, vector<long long> &answers, const vector<Query> &queries, int qidx, bool add) {
        int v = value[node];
        if (add) {
            if (freq[v] == 0) curAns++;
            freq[v]++;
        } else {
            freq[v]--;
            if (freq[v] == 0) curAns--;
        }
    }

    vector<long long> subtreeQueries(const vector<pair<int, int>> &queriesIn) {
        blockSize = max(1, (int)sqrt(n));
        dfs(0, -1);

        int maxVal = *max_element(value.begin(), value.end());
        freq.assign(maxVal + 1, 0);

        vector<Query> qs;
        for (int i = 0; i < (int)queriesIn.size(); i++) {
            int u = queriesIn[i].first;
            qs.push_back({first[u], last[u], i});
        }

        sort(qs.begin(), qs.end(), [&](const Query &a, const Query &b) {
            int ba = a.l / blockSize, bb = b.l / blockSize;
            if (ba != bb) return ba < bb;
            return (ba & 1) ? a.r > b.r : a.r < b.r;
        });

        vector<long long> ans(queriesIn.size());
        int curL = 0, curR = -1;
        curAns = 0;

        auto expand = [&](int pos) { addRemove(euler[pos], ans, qs, 0, true); };
        auto shrink = [&](int pos) { addRemove(euler[pos], ans, qs, 0, false); };

        for (auto &q : qs) {
            while (curL > q.l) expand(--curL);
            while (curR < q.r) expand(++curR);
            while (curL < q.l) shrink(curL++);
            while (curR > q.r) shrink(curR--);
            ans[q.idx] = curAns;
        }
        return ans;
    }
};

int main() {
    // Tree: 0-1-3, 0-2-4
    MoOnTree mo(5);
    mo.value = {1, 2, 2, 3, 3};
    mo.addEdge(0, 1);
    mo.addEdge(0, 2);
    mo.addEdge(1, 3);
    mo.addEdge(2, 4);

    auto ans = mo.subtreeQueries({{0, 0}, {1, 0}, {2, 0}});
    cout << "Distinct in subtree(0) = " << ans[0] << endl;
    cout << "Distinct in subtree(1) = " << ans[1] << endl;
    cout << "Distinct in subtree(2) = " << ans[2] << endl;
    return 0;
}
