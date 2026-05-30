#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/* -------- BIT -------- */
class BIT
{
public:
    int n;
    vector<ll> bit;

    BIT(int n)
    {
        this->n = n;
        bit.resize(n + 1, 0);
    }

    void update(int i, ll x)
    {
        for (; i <= n; i += (i & -i))
            bit[i] += x;
    }

    ll sum_query(int i)
    {
        ll total = 0;
        for (; i > 0; i -= (i & -i))
            total += bit[i];
        return total;
    }

    ll rangeSum_query(int l, int r)
    {
        return sum_query(r) - sum_query(l - 1);
    }
};

/* -------- Euler Tour class -------- */
class Euler_Tour
{
public:
    unordered_map<int, list<pair<int, int>>> adjList;

    vector<int> start, end;
    vector<ll> value, linear_tree;
    int timer, n;

    Euler_Tour(int n) : n(n)
    {
        start.assign(n + 1, 0);
        end.assign(n + 1, 0);
        value.assign(n + 1, 0);
        linear_tree.assign(n + 5, 0);
        timer = 0;
    }

    // Pre-order Euler Tour
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

        end[node] = timer - 1;
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
            int s;
            ll x;
            cin >> s >> x;

            ll diff = x - et.value[s];
            et.value[s] = x;
            bit.update(et.start[s] + 1, diff);
        }
        else
        {
            int s;
            cin >> s;

            cout << bit.rangeSum_query(et.start[s] + 1, et.end[s] + 1) << '\n';
        }
    }

    return 0;
}