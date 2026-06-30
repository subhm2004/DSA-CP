// ════════════════════════════════════════════════════════════════════════════
// UNION-FIND (DISJOINT SET UNION) — Path Compression + Union by RANK
// ────────────────────────────────────────────────────────────────────────────
// Disjoint sets ko efficiently handle karta hai
// FIND = element ka representative dhundho  |  UNION = do sets merge karo
// Applications: cycle detection, Kruskal MST, connected components
// Time: O(α(n)) per op  |  Space: O(n)
// ════════════════════════════════════════════════════════════════════════════

#include <bits/stdc++.h>
using namespace std;

class UnionFindByRank
{
    vector<int> parent; // Parent array - har element ka representative/root store karta hai
    vector<int> rank_;  // Rank array - tree ki APPROXIMATE height track karta hai

public:
    // Step 1: parent, rank arrays ko n size ka resize karo.
    // Step 2: rank[i] = 0 — har node ek single-node tree hai (height 0).
    // Step 3: parent[i] = i for all i — shuru mein n alag disjoint sets.
    UnionFindByRank(int n)
    {
        parent.resize(n);
        rank_.resize(n, 0);

        for (int i = 0; i < n; i++)
            parent[i] = i; // Har node apna khud ka representative
    }

    // Step 1: Agar x == parent[x] hai to x khud root hai — return x.
    // Step 2: Warna recursively parent chain follow karo.
    // Step 3: PATH COMPRESSION: return parent[x] = find(parent[x]) — direct root point.
    int find(int x)
    {
        if (x == parent[x])
            return x;

        return parent[x] = find(parent[x]); // path compression
    }

    // Step 1: find(x), find(y) se roots nikalo.
    // Step 2: Same root ho to already same set — return.
    // Step 3: Chhoti RANK (height) wale tree ko badi rank wale ke neeche attach karo.
    // Step 4: Equal rank ho to koi ek root banao aur uska rank++ kar do.
    void UNION_BY_RANK(int x, int y)
    {
        int x_parent = find(x);
        int y_parent = find(y);

        if (x_parent == y_parent)
            return; // already same set mein hain

        if (rank_[x_parent] < rank_[y_parent])
        {
            parent[x_parent] = y_parent; // chhoti height wala bade ke neeche
        }
        else if (rank_[x_parent] > rank_[y_parent])
        {
            parent[y_parent] = x_parent; // chhoti height wala bade ke neeche
        }
        else
        {
            parent[y_parent] = x_parent; // dono equal, ek ko root banao
            rank_[x_parent]++;           // height ek level badh gayi
        }
    }

    // x aur y same set mein hain ya nahi check karo
    bool connected(int x, int y)
    {
        return find(x) == find(y);
    }

    // Total disjoint components count karo
    int countComponents()
    {
        int components = 0;
        for (int i = 0; i < (int)parent.size(); ++i)
            if (parent[i] == i)
                components++;
        return components;
    }
};

int main()
{
    UnionFindByRank dsu(6); // 6 elements: 0 to 5

    /* INITIAL: {0},{1},{2},{3},{4},{5} -> 6 components */

    dsu.UNION_BY_RANK(0, 1); // {0,1},{2},{3},{4},{5}
    dsu.UNION_BY_RANK(0, 2); // {0,1,2},{3},{4},{5}
    dsu.UNION_BY_RANK(3, 4); // {0,1,2},{3,4},{5}
    dsu.UNION_BY_RANK(1, 3); // {0,1,2,3,4},{5}

    cout << "0 and 3 same set? " << (dsu.connected(0, 3) ? "Yes" : "No") << "\n";
    cout << "0 and 5 same set? " << (dsu.connected(0, 5) ? "Yes" : "No") << "\n";
    cout << "Total components: " << dsu.countComponents() << "\n";

    return 0;
}

/*
NOTES:
- Union by RANK: hamesha CHHOTI height wala tree BADI height wale ke neeche attach hota hai.
- Rank sirf TREE HEIGHT (upper bound) ko approximate karta hai, set size nahi.
- Equal rank merge hone par hi rank++ hota hai, otherwise rank same rehta hai.
- Path compression ke sath combine karke amortized O(α(n)) per operation milta hai.
- Use case: Kruskal MST, cycle detection, connected components, redundant connection.
*/