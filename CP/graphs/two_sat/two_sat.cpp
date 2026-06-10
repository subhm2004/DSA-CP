// ════════════════════════════════════════════════════════════════════════════
// 2-SAT (Two Satisfiability) — 2-CNF Formula Solve karo
// ────────────────────────────────────────────────────────────────────────────
// Har clause (a OR b) ko implications me badlo:
//   !a -> b  aur  !b -> a
//
// Variable encoding:
//   node 2*i     = variable i is FALSE
//   node 2*i + 1 = variable i is TRUE
//   neg(x) = x ^ 1  (true <-> false flip)
//
// Satisfiable iff kisi variable ke liye true aur false nodes alag SCC me hon
// Approach: Kosaraju SCC on implication graph
// Complexity: O(V + E)
// ════════════════════════════════════════════════════════════════════════════

#include <bits/stdc++.h>
using namespace std;

struct TwoSAT {
    int n;
    vector<vector<int>> g, rg;   // g = forward graph, rg = reverse (Kosaraju)
    vector<int> order, comp, assignment;
    vector<bool> used;

    TwoSAT(int vars) : n(vars), g(2 * vars), rg(2 * vars), comp(2 * vars, -1), assignment(vars), used(2 * vars) {}

    // ── neg: literal ka opposite node (true <-> false) ─────────────────────
    int neg(int x) { return x ^ 1; }

    // ── addEdge: implication u -> v ────────────────────────────────────────
    void addEdge(int u, int v) {
        g[u].push_back(v);
        rg[v].push_back(u);
    }

    // ── addClause: (aVar with aVal) OR (bVar with bVal) ────────────────────
    // Dono implications add: !a -> b, !b -> a
    void addClause(int aVar, bool aVal, int bVar, bool bVal) {
        // Step 1: variable encoding — 2*i=false, 2*i+1=true literal node
        int a = 2 * aVar + aVal;
        int b = 2 * bVar + bVal;
        // Step 2: (a OR b) => !a->b aur !b->a dono implications add karo
        addEdge(neg(a), b);
        addEdge(neg(b), a);
    }

    // ── dfs1: Kosaraju step 1 — finish order me nodes daalo ──────────────────
    void dfs1(int v) {
        used[v] = true;
        for (int u : g[v])
            if (!used[u])
                dfs1(u);
        order.push_back(v);
    }

    // ── dfs2: Kosaraju step 2 — reverse graph pe SCC assign karo ───────────
    void dfs2(int v, int c) {
        comp[v] = c;
        for (int u : rg[v])
            if (comp[u] == -1)
                dfs2(u, c);
    }

    // ── solve: SCC check — true/false same component me to UNSAT ───────────
    bool solve() {
        // Step 1: Kosaraju pass 1 — finish order me nodes stack karo
        for (int i = 0; i < 2 * n; i++)
            if (!used[i])
                dfs1(i);

        // Step 2: reverse order me reverse graph pe SCC assign karo
        reverse(order.begin(), order.end());
        int j = 0;
        for (int v : order)
            if (comp[v] == -1)
                dfs2(v, j++);

        // Step 3: har variable ke true/false nodes alag SCC me hon to SAT
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
