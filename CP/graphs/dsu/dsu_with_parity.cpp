/*
 * ============================================================================
 * TOPIC    : DSU with Parity (XOR Union-Find)
 * FILE     : dsu_with_parity.cpp
 * PROBLEM  : Merge sets with parity constraints — bipartite check, same/different group
 * APPROACH : parity[x] = XOR distance (mod 2) from x to its root; path compression with XOR
 * COMPLEX  : Time: O(E × α(V))  |  Space: O(V)
 * LEETCODE : 785 — Is Graph Bipartite?  |  886 — Possible Bipartition
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// DSU WITH PARITY — XOR Union-Find
// ────────────────────────────────────────────────────────────────────────────
// Normal DSU sirf "same set ya nahi" batata hai.
// Parity DSU batata hai: do nodes ke beech relative color/parity kya hai (0 ya 1).
//
// parity[x] = node x se uske parent tak ka XOR (mod 2)
// find(x) ke baad parity[x] = x se root tak ka XOR
//
// unite(u, v, req): enforce  parity(u) XOR parity(v) = req
//   req = 1 → u aur v OPPOSITE color (bipartite edge)
//   req = 0 → u aur v SAME color (same team)
//
// Applications:
//   • Bipartite graph check
//   • 2-coloring with constraints
//   • "Same group / different group" merge problems
// COMPLEX: O(α(n)) per find/unite
// ════════════════════════════════════════════════════════════════════════════

struct DSUParity
{
    vector<int> parent, rankv, parity;

    // ── DSUParity: n nodes, sab alag components, parity 0 ──
    DSUParity(int n) : parent(n), rankv(n, 0), parity(n, 0)
    {
        iota(parent.begin(), parent.end(), 0);
    }

    // ── find: root + x se root tak ka parity return ──
    //   1) x root hai → {x, 0}
    //   2) recursively parent ka root dhundho
    //   3) path compression: parent[x] = root
    //   4) parity[x] ^= p — parent chain ka XOR accumulate
    //   Returns: {root, parity(x → root)}
    pair<int, int> find(int x)
    {
        if (parent[x] == x)
            return {x, 0};

        pair<int, int> res = find(parent[x]);
        int root = res.first;
        int p = res.second;

        parent[x] = root;
        parity[x] ^= p;

        return {parent[x], parity[x]};
    }

    // ── unite: parity(u) XOR parity(v) = req enforce karo ──
    //   1) dono ke roots + parities nikalo
    //   2) same root → check existing constraint: (xu XOR xv) == req?
    //   3) alag root → merge, child ki parity set: xu XOR xv XOR req
    //   4) union by rank se attach karo
    //   Returns false agar constraint violate ho (already same set me galat parity)
    bool unite(int u, int v, int req = 1)
    {
        pair<int, int> fu = find(u);
        pair<int, int> fv = find(v);
        int pu = fu.first, xu = fu.second;
        int pv = fv.first, xv = fv.second;

        if (pu == pv)
            return ((xu ^ xv) == req);

        if (rankv[pu] < rankv[pv])
        {
            parent[pu] = pv;
            parity[pu] = xu ^ xv ^ req;
        }
        else if (rankv[pu] > rankv[pv])
        {
            parent[pv] = pu;
            parity[pv] = xu ^ xv ^ req;
        }
        else
        {
            parent[pv] = pu;
            parity[pv] = xu ^ xv ^ req;
            rankv[pu]++;
        }
        return true;
    }

    // ── sameSet: u aur v same component me? ──
    bool sameSet(int u, int v)
    {
        return find(u).first == find(v).first;
    }

    // ── getParity: u aur v ke beech XOR parity (same component me) ──
    //   different components → -1
    //   same component → parity(u) XOR parity(v)  (0 = same color, 1 = opposite)
    int getParity(int u, int v)
    {
        pair<int, int> fu = find(u);
        pair<int, int> fv = find(v);
        if (fu.first != fv.first)
            return -1;
        return fu.second ^ fv.second;
    }
};

// ── isBipartite: har edge pe unite(u,v,1) — adjacent opposite hone chahiye ──
bool isBipartite(int n, const vector<pair<int, int>> &edges)
{
    DSUParity dsu(n);
    for (auto &e : edges)
    {
        if (!dsu.unite(e.first, e.second, 1))
            return false;
    }
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Test 1: Bipartite graph ===\n";
    // 0 — 1
    // |   |
    // 3 — 2   (square, bipartite)
    vector<pair<int, int>> edges1 = {{0, 1}, {1, 2}, {2, 3}, {3, 0}};
    cout << "Square graph bipartite? " << (isBipartite(4, edges1) ? "Yes" : "No") << "\n";

    cout << "\n=== Test 2: NOT bipartite (triangle) ===\n";
    vector<pair<int, int>> edges2 = {{0, 1}, {1, 2}, {0, 2}};
    cout << "Triangle bipartite? " << (isBipartite(3, edges2) ? "Yes" : "No") << "\n";

    cout << "\n=== Test 3: Same group constraint (req=0) ===\n";
    DSUParity dsu(4);
    // 0 and 1 same team, 1 and 2 same team → 0 and 2 same team
    dsu.unite(0, 1, 0);
    dsu.unite(1, 2, 0);
    cout << "parity(0,2) = " << dsu.getParity(0, 2) << " (expect 0 = same)\n";
    cout << "unite(0,3,1) ok? " << (dsu.unite(0, 3, 1) ? "Yes" : "No") << "\n";
    cout << "parity(2,3) = " << dsu.getParity(2, 3) << " (expect 1 = opposite)\n";

    cout << "\n=== Test 4: Constraint violation ===\n";
    DSUParity dsu2(2);
    dsu2.unite(0, 1, 1); // opposite
    cout << "unite(0,1,0) again (same color)? " << (dsu2.unite(0, 1, 0) ? "Yes" : "No")
         << " (expect No — already opposite)\n";

    return 0;
}

/*
 * ════════════════════════════════════════════════════════════════════════════
 * DSU WITH PARITY — QUICK GUIDE (Hinglish)
 * ════════════════════════════════════════════════════════════════════════════
 *
 * SOCH KAISE KAREIN?
 *   Har node ka ek "color" hai: 0 ya 1.
 *   Edge (u,v) ka matlab: parity(u) XOR parity(v) = req
 *     req=1 → alag color (bipartite)
 *     req=0 → same color (same team)
 *
 * FIND ME KYA HOTA HAI?
 *   Normal DSU jaisa root dhundho, PLUS path compression ke saath
 *   parity[x] update — x se root tak kitne "flips" (XOR) hue.
 *
 * UNITE ME FORMULA:
 *   pu, pv alag roots hain. Child root ki parity set:
 *     parity[child_root] = xu XOR xv XOR req
 *   Taaki merge ke baad bhi constraint satisfy ho.
 *
 * KAB USE KARO?
 *   ✅ Graph bipartite hai ya nahi
 *   ✅ 2-coloring with edge constraints
 *   ✅ "Enemy/friend" relation — same or opposite group
 *   ❌ 3+ colors chahiye → DSU parity kaam nahi karega
 *   ❌ Sirf connected hai ya nahi → normal DSU kaafi
 *
 * COMMON MISTAKES:
 *   ❌ req=1 bhool jana bipartite me (default 1 hai is file me)
 *   ❌ Edge do baar process karna without check — usually OK, unite idempotent
 *   ❌ getParity alag components pe -1 aata hai — handle karo
 *
 * ════════════════════════════════════════════════════════════════════════════
 */
