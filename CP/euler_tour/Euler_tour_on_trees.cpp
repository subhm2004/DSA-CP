#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// ════════════════════════════════════════════════════════════════════════════
// EULER TOUR ON TREE + FENWICK TREE — Subtree Sum Query / Point Update
// ────────────────────────────────────────────────────────────────────────────
// Tree ko flat array me badalte hain DFS se:
//   start[node] = entry time (in_time)
//   end[node]   = subtree ka last index
//   node ka poora subtree = linear array me [start, end] continuous range
//
// Ab subtree sum = BIT pe range query [start+1, end+1] (1-indexed BIT)
// Point update = BIT pe diff add at start[node]+1
// ════════════════════════════════════════════════════════════════════════════

class BIT
{
public:
    int n;
    vector<ll> bit;

    // ── BIT: n-size ka fenwick tree initialize karo ─────────────────────────
    //   1) n store, bit size n+1 (1-indexed)
    //   2) sab zero — euler tour values baad me update() se aayengi
    BIT(int n)
    {
        this->n = n;
        bit.resize(n + 1, 0);
    }

    // ── update: index 'i' pe 'x' add karo ────────────────────────────────────
    //   1) bit[i] += x, phir i += i & -i
    //   2) responsible parent indices tak propagate
    //   3) point update O(log n)
    void update(int i, ll x)
    {
        for (; i <= n; i += (i & -i))
            bit[i] += x;
    }

    // ── sum_query: [1, i] prefix sum nikalo ─────────────────────────────────
    //   1) total = 0, i se shuru
    //   2) total += bit[i], i -= i & -i
    //   3) i > 0 tak — prefix mil gaya
    ll sum_query(int i)
    {
        ll total = 0;
        for (; i > 0; i -= (i & -i))
            total += bit[i];
        return total;
    }

    // ── rangeSum_query: [l, r] ka sum nikalo ────────────────────────────────
    //   1) sum_query(r) - sum_query(l-1)
    //   2) beech ka range sum — subtree query ke liye use hota hai
    ll rangeSum_query(int l, int r)
    {
        return sum_query(r) - sum_query(l - 1);
    }
};

class Euler_Tour
{
public:
    unordered_map<int, list<pair<int, int>>> adjList;

    vector<int> start, end;     // har node ka subtree range [start, end]
    vector<ll> value, linear_tree;
    int timer, n;

    // ── Euler_Tour: n nodes ke arrays aur timer initialize karo ─────────────
    //   1) start/end = subtree range boundaries, value = node values
    //   2) linear_tree = euler order me flat array
    //   3) timer = 0 — dfs me entry time badhega
    Euler_Tour(int n) : n(n)
    {
        start.assign(n + 1, 0);
        end.assign(n + 1, 0);
        value.assign(n + 1, 0);
        linear_tree.assign(n + 5, 0);
        timer = 0;
    }

    // ── dfs: pre-order euler tour — entry time pe value store, exit pe end set ─
    //   1) start[node] = timer, linear_tree[timer] = value[node], timer++
    //   2) har neighbor pe dfs (parent skip)
    //   3) wapas aate waqt end[node] = timer-1 — subtree ka last index
    //   4) subtree = linear array me [start, end] continuous range
    void dfs(int node, int parent)
    {
        start[node] = timer;
        linear_tree[timer] = value[node];
        timer++;

        for (auto &p : adjList[node])
        {
            int nbr = p.first;
            if (nbr == parent)
                continue;
            dfs(nbr, node);
        }

        end[node] = timer - 1;   // last index jahan is subtree ki nodes hain
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    Euler_Tour et(n);

    for (int i = 1; i <= n; i++)
        cin >> et.value[i];

    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        et.adjList[a].push_back({b, 0});
        et.adjList[b].push_back({a, 0});
    }

    et.dfs(1, 0);

    BIT bit(n);

    for (int i = 0; i < n; i++)
        bit.update(i + 1, et.linear_tree[i]);

    while (q--)
    {
        int type;
        cin >> type;

        if (type == 1)
        {
            // point update: node s ki value x set karo
            int s;
            ll x;
            cin >> s >> x;

            ll diff = x - et.value[s];
            et.value[s] = x;
            bit.update(et.start[s] + 1, diff);
        }
        else
        {
            // subtree sum query at node s
            int s;
            cin >> s;

            cout << bit.rangeSum_query(et.start[s] + 1, et.end[s] + 1) << '\n';
        }
    }

    return 0;
}
