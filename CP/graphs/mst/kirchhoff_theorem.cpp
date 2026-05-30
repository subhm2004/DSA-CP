/*
 * ============================================================================
 * TOPIC    : Kirchhoff's Matrix Tree Theorem
 * FILE     : kirchhoff_theorem.cpp
 * PROBLEM  : Count spanning trees of a connected undirected graph
 * APPROACH : Laplacian L = D − A → delete one row/col → determinant
 * REF      : https://cp-algorithms.com/graph/kirchhoff-theorem.html
 * COMPLEX  : Time: O(n³)  |  Space: O(n²)
 * ============================================================================
 *
 * THEOREM (1847)
 * --------------
 * L = D − A  (Laplacian)
 *   D[u][u] = degree of u (multi-edges + self-loops count)
 *   A[u][v] = number of edges between u and v
 *
 * Any cofactor of L equals # of spanning trees.
 * Practical: remove last row & column → det(minor) = answer.
 *
 * See kirchhoff_theorem.md for theory, circuit law link, when to use.
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

struct Kirchhoff {
    int n;
    vector<vector<long long>> laplacian;

    // Build Laplacian from undirected edge list (multi-edges allowed)
    Kirchhoff(int n_, const vector<pair<int, int>> &edges) : n(n_) {
        vector<vector<long long>> adj(n, vector<long long>(n, 0));
        vector<long long> deg(n, 0);

        for (auto [u, v] : edges) {
            adj[u][v]++;
            if (u != v) adj[v][u]++;
            deg[u]++;
            if (u != v) deg[v]++;
        }

        laplacian.assign(n, vector<long long>(n, 0));
        for (int i = 0; i < n; i++) {
            laplacian[i][i] = deg[i];
            for (int j = 0; j < n; j++)
                laplacian[i][j] -= adj[i][j];
        }
    }

    // Build directly from adjacency matrix (A[u][v] = edge count)
    static Kirchhoff fromAdjacency(const vector<vector<long long>> &adj) {
        int n = (int)adj.size();
        Kirchhoff k(n, {});
        k.laplacian.assign(n, vector<long long>(n, 0));
        for (int i = 0; i < n; i++) {
            long long deg = 0;
            for (int j = 0; j < n; j++) {
                deg += adj[i][j];
                k.laplacian[i][j] -= adj[i][j];
            }
            k.laplacian[i][i] = deg;
        }
        return k;
    }

    // (n−1)×(n−1) minor — delete row/col `skip`
    vector<vector<long long>> minor(int skip = -1) const {
        if (skip < 0) skip = n - 1;
        vector<vector<long long>> m(n - 1, vector<long long>(n - 1));
        for (int i = 0, ri = 0; i < n; i++) {
            if (i == skip) continue;
            for (int j = 0, rj = 0; j < n; j++) {
                if (j == skip) continue;
                m[ri][rj++] = laplacian[i][j];
            }
            ri++;
        }
        return m;
    }

    // Exact integer determinant — Bareiss algorithm (fraction-free), O(n³)
    static long long determinant(vector<vector<long long>> a) {
        int n = (int)a.size();
        if (n == 0) return 1;
        long long prev = 1;
        for (int k = 0; k < n - 1; k++) {
            for (int i = k + 1; i < n; i++) {
                for (int j = k + 1; j < n; j++) {
                    a[i][j] = (a[i][j] * a[k][k] - a[i][k] * a[k][j]) / (k ? prev : 1);
                }
            }
            prev = a[k][k];
        }
        return abs(a[n - 1][n - 1]);
    }

    // Determinant modulo MOD (contest default)
    static long long modPow(long long a, long long e, long long mod) {
        long long r = 1;
        a %= mod;
        while (e) {
            if (e & 1) r = r * a % mod;
            a = a * a % mod;
            e >>= 1;
        }
        return r;
    }

    static long long determinantMod(vector<vector<long long>> a, long long mod) {
        int n = (int)a.size();
        if (n == 0) return 1;
        long long det = 1;
        for (int col = 0; col < n; col++) {
            int row = col;
            while (row < n && a[row][col] % mod == 0) row++;
            if (row == n) return 0;
            if (row != col) {
                swap(a[row], a[col]);
                det = (mod - det) % mod;
            }
            det = det * a[col][col] % mod;
            long long inv = modPow(a[col][col], mod - 2, mod);
            for (int i = col + 1; i < n; i++) {
                long long factor = a[i][col] * inv % mod;
                for (int j = col; j < n; j++) {
                    a[i][j] = (a[i][j] - factor * a[col][j]) % mod;
                    if (a[i][j] < 0) a[i][j] += mod;
                }
            }
        }
        return det;
    }

    long long countSpanningTreesExact() const {
        if (n <= 1) return 0;
        return determinant(minor());
    }

    long long countSpanningTreesMod(long long mod) const {
        if (n <= 1) return 0;
        auto m = minor();
        for (auto &row : m)
            for (auto &x : row) x = ((x % mod) + mod) % mod;
        return determinantMod(m, mod);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Kirchhoff Matrix Tree Theorem ===\n\n";

    // Demo 1: triangle C3 → 3 spanning trees
    {
        int n = 3;
        vector<pair<int, int>> edges = {{0, 1}, {1, 2}, {0, 2}};
        Kirchhoff k(n, edges);
        cout << "Triangle (3-cycle): " << k.countSpanningTreesExact() << " trees  (expected 3)\n";
    }

    // Demo 2: complete graph K4 → 4^(4-2) = 16 (Cayley)
    {
        int n = 4;
        vector<pair<int, int>> edges;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                edges.push_back({i, j});
        Kirchhoff k(n, edges);
        cout << "Complete K4:        " << k.countSpanningTreesExact() << " trees  (expected 16)\n";
    }

    // Demo 3: path 1-2-3-4 → 1 tree only
    {
        int n = 4;
        vector<pair<int, int>> edges = {{0, 1}, {1, 2}, {2, 3}};
        Kirchhoff k(n, edges);
        cout << "Path P4:            " << k.countSpanningTreesExact() << " tree   (expected 1)\n";
    }

    // Demo 4: modular count K6 mod 1e9+7
    {
        int n = 6;
        vector<pair<int, int>> edges;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                edges.push_back({i, j});
        Kirchhoff k(n, edges);
        const long long MOD = 1'000'000'007;
        cout << "Complete K6 mod MOD:" << k.countSpanningTreesMod(MOD)
             << "  (6^4 = 1296)\n";

        // Cayley: n^(n-2) for K_n
        long long cayley = 1;
        for (int i = 0; i < n - 2; i++) cayley = cayley * n % MOD;
        cout << "Cayley formula check:" << cayley << "\n";
    }

    return 0;
}
