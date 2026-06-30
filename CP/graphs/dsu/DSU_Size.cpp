// ════════════════════════════════════════════════════════════════════════════
// UNION-FIND (DISJOINT SET UNION) — Path Compression + Union by SIZE
// ────────────────────────────────────────────────────────────────────────────
// Disjoint sets ko efficiently handle karta hai
// FIND = element ka representative dhundho  |  UNION = do sets merge karo
// Applications: cycle detection, Kruskal MST, connected components
// Time: O(α(n)) per op  |  Space: O(n)
// ════════════════════════════════════════════════════════════════════════════

#include <bits/stdc++.h>
using namespace std;

class UnionFindBySize
{
    vector<int> parent; // Parent array - har element ka representative/root store karta hai
    vector<int> size;   // Size array - har set ka size store karta hai (merging decide karne ke liye)

public:
    // Step 1: parent, size arrays ko n size ka resize karo.
    // Step 2: size[i] = 1 — har node apne aap ek set hai.
    // Step 3: parent[i] = i for all i — shuru mein n alag disjoint sets.
    UnionFindBySize(int n)
    {
        parent.resize(n);
        size.resize(n, 1);

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
    // Step 3: Chhota set bade set ke andar attach karo (size ke basis pe).
    // Step 4: size[root] += size[other] — total size update.
    // Step 1: find(x), find(y) se roots nikalo.
    // Step 2: Same root ho to already same set — return.
    // Step 3: Bada size wale root ke neeche chhota attach karo (bina swap ke, if-else se).
    // Step 4: Merge ke baad size[root] += size[other] — total size update.
    void UNION_BY_SIZE(int x, int y)
    {
        int x_parent = find(x);
        int y_parent = find(y);

        if (x_parent == y_parent)
            return; // already same set mein hain

        if (size[x_parent] >= size[y_parent])
        {
            // x_parent ka set bada (ya equal) hai, y_parent ko x_parent mein merge karo
            parent[y_parent] = x_parent;
            size[x_parent] += size[y_parent]; // total size update
        }
        else
        {
            // y_parent ka set bada hai, x_parent ko y_parent mein merge karo
            parent[x_parent] = y_parent;
            size[y_parent] += size[x_parent]; // total size update
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
    UnionFindBySize dsu(6); // 6 elements: 0 to 5

    /* INITIAL: {0},{1},{2},{3},{4},{5} -> 6 components */

    dsu.UNION_BY_SIZE(0, 1); // {0,1},{2},{3},{4},{5}
    dsu.UNION_BY_SIZE(0, 2); // {0,1,2},{3},{4},{5}
    dsu.UNION_BY_SIZE(3, 4); // {0,1,2},{3,4},{5}
    dsu.UNION_BY_SIZE(1, 3); // {0,1,2,3,4},{5}

    cout << "0 and 3 same set? " << (dsu.connected(0, 3) ? "Yes" : "No") << "\n";
    cout << "0 and 5 same set? " << (dsu.connected(0, 5) ? "Yes" : "No") << "\n";
    cout << "Total components: " << dsu.countComponents() << "\n";

    return 0;
}

/*
NOTES:
- Union by SIZE: hamesha CHHOTA set BADE set ke andar attach hota hai.
- Path compression ke sath combine karke amortized O(α(n)) per operation milta hai.
- α(n) practically constant hai (≤4 for all practical n).
- Use case: Kruskal MST, cycle detection, connected components, redundant connection.
*/