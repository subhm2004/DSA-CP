#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// BINARY LIFTING — K-th Ancestor (Basic)
// ────────────────────────────────────────────────────────────────────────────
// up[i][j] = node i ka 2^j-th ancestor (j=0 -> direct parent)
// Fill: up[i][j] = up[ up[i][j-1] ][j-1]  (jump double karo)
//
// K-th ancestor: K ke binary bits check karo, j-th bit set ho to
//               node = up[node][j]
// Complexity: preprocess O(n log n), query O(log n)
// ════════════════════════════════════════════════════════════════════════════

class BinaryLifting
{
    int n, maxLog;
    vector<vector<int>> up; // up[i][j] -> 2^j-th ancestor of node i

public:
    // ── Constructor: parent array se up[][] table banao ─────────────────────
    //   1) maxLog = log2(n)+1 — kitne jump levels
    //   2) up[i][0] = parent[i] — direct parent (2^0 ancestor)
    //   3) j=1..maxLog-1: up[i][j] = up[ up[i][j-1] ][j-1]
    //   4) DP se har node ka 2^j-th ancestor precompute — query O(log n)
    BinaryLifting(int n, vector<int> &parent)
    {
        this->n = n;
        maxLog = log2(n) + 1;
        up.assign(n, vector<int>(maxLog, -1));

        // 2^0-th ancestor = direct parent
        for (int i = 0; i < n; i++)
        {
            up[i][0] = parent[i];
        }

        // DP: har power of 2 ke liye ancestor precompute
        for (int j = 1; j < maxLog; j++)
        {
            for (int i = 0; i < n; i++)
            {
                if (up[i][j - 1] != -1)
                {
                    up[i][j] = up[up[i][j - 1]][j - 1];  // do 2^(j-1) jumps = 2^j jump
                }
            }
        }
    }

    // ── getKthAncestor: node ka K-th ancestor (root se upar) ────────────────
    //   1) K ke har set bit j ke liye: node = up[node][j]
    //   2) -1 mila to ancestor exist nahi — return -1
    //   3) binary representation se exactly K steps upar pahunch jaate ho
    int getKthAncestor(int node, int k)
    {
        for (int j = 0; j < maxLog; j++)
        {
            if (k & (1 << j))
            {
                node = up[node][j];
                if (node == -1)
                    return -1;
            }
        }
        return node;
    }
};

int main()
{
    int n = 10;
    vector<int> parent = {-1, 0, 0, 1, 1, 2, 2, 3, 3, 4};

    BinaryLifting bl(n, parent);

    cout << "3rd ancestor of node 9: " << bl.getKthAncestor(9, 3) << endl;
    cout << "2nd ancestor of node 6: " << bl.getKthAncestor(6, 2) << endl;
    cout << "1st ancestor of node 8: " << bl.getKthAncestor(8, 1) << endl;

    return 0;
}
