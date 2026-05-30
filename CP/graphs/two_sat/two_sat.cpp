/*
 * ============================================================================
 * TOPIC    : Two-SAT
 * FILE     : two_sat.cpp
 * PROBLEM  : Satisfy 2-CNF formula with implications (a OR b)
 * APPROACH : Implication graph + Kosaraju SCC — xi and !xi in different SCC
 * COMPLEX  : Time: O(V + E)  |  Space: O(V + E)
 * ============================================================================
 *
 * Variable i: node 2*i = false, 2*i+1 = true
 * (a OR b)  => (!a -> b) and (!b -> a)
 */

#include <bits/stdc++.h>
using namespace std;

struct TwoSAT {
    int n;
    vector<vector<int>> g, rg;
    vector<int> order, comp, assignment;
    vector<bool> used;

    TwoSAT(int vars) : n(vars), g(2 * vars), rg(2 * vars), comp(2 * vars, -1), assignment(vars), used(2 * vars) {}

    int neg(int x) { return x ^ 1; }

    void addEdge(int u, int v) {
        g[u].push_back(v);
        rg[v].push_back(u);
    }

    // Clause: (a is true form aVar) OR (b is true form bVar)
    void addClause(int aVar, bool aVal, int bVar, bool bVal) {
        int a = 2 * aVar + aVal;
        int b = 2 * bVar + bVal;
        addEdge(neg(a), b);
        addEdge(neg(b), a);
    }

    void dfs1(int v) {
        used[v] = true;
        for (int u : g[v])
            if (!used[u])
                dfs1(u);
        order.push_back(v);
    }

    void dfs2(int v, int c) {
        comp[v] = c;
        for (int u : rg[v])
            if (comp[u] == -1)
                dfs2(u, c);
    }

    bool solve() {
        for (int i = 0; i < 2 * n; i++)
            if (!used[i])
                dfs1(i);

        reverse(order.begin(), order.end());
        int j = 0;
        for (int v : order)
            if (comp[v] == -1)
                dfs2(v, j++);

        for (int i = 0; i < n; i++) {
            if (comp[2 * i] == comp[2 * i + 1])
                return false;
            assignment[i] = comp[2 * i] < comp[2 * i + 1];
        }
        return true;
    }
};

int main() {
    // (x0 OR x1) AND (!x0 OR x1) AND (x0 OR !x1)
    TwoSAT sat(2);
    sat.addClause(0, true, 1, true);
    sat.addClause(0, false, 1, true);
    sat.addClause(0, true, 1, false);

    if (sat.solve()) {
        cout << "SATISFIABLE: x0=" << sat.assignment[0] << " x1=" << sat.assignment[1] << endl;
    } else {
        cout << "UNSATISFIABLE" << endl;
    }
    return 0;
}
