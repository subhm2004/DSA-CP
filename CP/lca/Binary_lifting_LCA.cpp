#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// BINARY LIFTING — K-th Ancestor + LCA
// ────────────────────────────────────────────────────────────────────────────
// up[i][j] = 2^j-th ancestor. depth[i] = root se kitni door.
//
// LCA(u, v):
//   1) deeper node ko upar lao (same depth)
//   2) dono ko saath-saath 2^j jumps se upar le jao jab tak parent same na ho
//   3) direct parent = LCA
// ════════════════════════════════════════════════════════════════════════════

class BinaryLifting
{
private:
    int n, LOG;
    vector<vector<int>> up;
    vector<int> depth;

public:
    // ── Constructor: up table + depth[] build karo ──────────────────────────
    //   1) LOG = log2(n)+1 — kitne binary jump levels chahiye
    //   2) up[i][0] = direct parent[i] for all nodes
    //   3) root se dfs chalao depth[] bharno
    //   4) j=1..LOG-1: up[i][j] = up[ up[i][j-1] ][j-1] (2^j ancestor DP)
    BinaryLifting(int n, const vector<int> &parent)
    {
        this->n = n;
        LOG = ceil(log2(n)) + 1;
        up.assign(n, vector<int>(LOG, -1));
        depth.assign(n, 0);

        for (int i = 0; i < n; ++i)
        {
            up[i][0] = parent[i];
        }

        for (int i = 0; i < n; ++i)
        {
            if (parent[i] == -1)
                dfs(i, 0, parent);
        }

        for (int j = 1; j < LOG; ++j)
        {
            for (int i = 0; i < n; ++i)
            {
                int prev = up[i][j - 1];
                if (prev != -1)
                    up[i][j] = up[prev][j - 1];  // 2^(j-1) jump do baar = 2^j jump
            }
        }
    }

    // ── dfs: depth[] bharno (root se distance) ───────────────────────────────
    //   1) depth[node] = d set karo
    //   2) saare nodes jinka parent[i]==node, unpe dfs(i, d+1)
    //   3) poori tree traverse — har node ki depth mil jaati hai
    void dfs(int node, int d, const vector<int> &parent)
    {
        depth[node] = d;
        for (int i = 0; i < n; ++i)
        {
            if (parent[i] == node)
            {
                dfs(i, d + 1, parent);
            }
        }
    }

    // ── getKthAncestor: K-th ancestor via binary lifting ─────────────────────
    //   1) K ke har set bit i ke liye check karo
    //   2) bit set ho to node = up[node][i] (2^i jump ek saath)
    //   3) node -1 ho gaya to ancestor exist nahi — return -1
    //   4) sab bits process -> exactly K-th ancestor mil gaya
    int getKthAncestor(int node, int k)
    {
        for (int i = 0; i < LOG; ++i)
        {
            if (k & (1 << i))
            {
                node = up[node][i];
                if (node == -1)
                    return -1;
            }
        }
        return node;
    }

    // ── getLCA: lowest common ancestor of u and v ───────────────────────────
    //   1) deeper node ko upar lao — depth equal karo (getKthAncestor se)
    //   2) agar u==v ho gaya to wahi LCA
    //   3) bade jumps se (LOG-1 se 0) dono ko saath upar le jao jab tak parent same na ho
    //   4) up[u][0] = direct parent = LCA
    int getLCA(int u, int v)
    {
        if (depth[u] < depth[v])
            swap(u, v);
        u = getKthAncestor(u, depth[u] - depth[v]);  // u ko v ke level pe lao
        if (u == v)
            return u;

        for (int i = LOG - 1; i >= 0; --i)
        {
            if (up[u][i] != -1 && up[u][i] != up[v][i])  // abhi LCA se upar ho
            {
                u = up[u][i];
                v = up[v][i];
            }
        }
        return up[u][0];
    }
};

int main()
{
    int n = 11;
    vector<int> parent = {-1, 0, 0, 0, 1, 1, 2, 2, 4, 6, 6};

    BinaryLifting bl(n, parent);

    cout << "2nd ancestor of 8: " << bl.getKthAncestor(8, 2) << endl;
    cout << "3rd ancestor of 9: " << bl.getKthAncestor(9, 3) << endl;
    cout << "1st ancestor of 10: " << bl.getKthAncestor(10, 1) << endl;

    cout << "LCA of 5 and 8: " << bl.getLCA(5, 8) << endl;
    cout << "LCA of 8 and 10: " << bl.getLCA(8, 10) << endl;
    cout << "LCA of 9 and 10: " << bl.getLCA(9, 10) << endl;
    cout << "LCA of 7 and 10: " << bl.getLCA(7, 10) << endl;
    cout << "LCA of 3 and 10: " << bl.getLCA(3, 10) << endl;

    return 0;
}
