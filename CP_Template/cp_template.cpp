/*
 * cp_template.cpp — copy karo, solve() me logic likho
 *
 * Compile (local test):
 *   g++ -std=c++17 -O2 -DLOCAL cp_template.cpp -o sol && ./sol
 *
 * Heavy DS (segtree, lazy, FFT, flows…) → CP/ folder se copy karo
 */

#include <bits/stdc++.h>
using namespace std;

// ── types & macros ──────────────────────────────────────────────────────────
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = (a); i < (b); ++i)
#define sz(x) (int)(x).size()

const ll INF = (ll)4e18;
const ll MOD = 1e9 + 7;

#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << '\n'
#else
#define dbg(x)
#endif

// ── mod (jab problem me MOD ho) ─────────────────────────────────────────────
ll modMul(ll a, ll b, ll m = MOD) { return (a % m) * (b % m) % m; }

ll modPow(ll a, ll b, ll m = MOD) {
    ll res = 1;
    a %= m;
    while (b > 0) {
        if (b & 1) res = modMul(res, a, m);
        a = modMul(a, a, m);
        b >>= 1;
    }
    return res;
}

ll modInv(ll a, ll m = MOD) { return modPow(a, m - 2, m); }

// nCr — sirf tab banao jab chahiye: Comb C(nmax);
struct Comb {
    vi fact, inv;
    Comb(int n, ll m = MOD) : fact(n + 1), inv(n + 1) {
        fact[0] = 1;
        rep(i, 1, n + 1) fact[i] = (ll)fact[i - 1] * i % m;
        inv[n] = modPow(fact[n], m - 2, m);
        for (int i = n; i > 0; --i) inv[i - 1] = (ll)inv[i] * i % m;
    }
    ll C(int n, int r, ll m = MOD) const {
        if (r < 0 || r > n) return 0;
        return (ll)fact[n] * inv[r] % m * inv[n - r] % m;
    }
};

// ── DSU ─────────────────────────────────────────────────────────────────────
struct DSU {
    vi par, sub;
    DSU(int n) : par(n), sub(n, 1) { iota(all(par), 0); }
    int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }
    bool unite(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (sub[a] < sub[b]) swap(a, b);
        par[b] = a;
        sub[a] += sub[b];
        return true;
    }
};

// ── Fenwick (point update, prefix / range sum) ───────────────────────────────
struct Fenwick {
    int n;
    vector<ll> f;
    Fenwick(int n) : n(n), f(n + 1) {}
    void add(int i, ll v) {
        for (++i; i <= n; i += i & -i) f[i] += v;
    }
    ll sum(int i) const {
        ll s = 0;
        for (++i; i > 0; i -= i & -i) s += f[i];
        return s;
    }
    ll range(int l, int r) const { return sum(r) - (l ? sum(l - 1) : 0); }
};

// ── dijkstra (weighted graph, 0-indexed) ─────────────────────────────────────
vector<ll> dijkstra(int n, const vector<vector<pii>> &g, int s) {
    vector<ll> dist(n, INF);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
    dist[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : g[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

// ── binary search on answer ─────────────────────────────────────────────────
template <class F>
ll bsMin(ll lo, ll hi, F ok) {
    while (lo < hi) {
        ll mid = lo + (hi - lo) / 2;
        if (ok(mid)) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

template <class F>
ll bsMax(ll lo, ll hi, F ok) {
    while (lo < hi) {
        ll mid = lo + (hi - lo + 1) / 2;
        if (ok(mid)) lo = mid;
        else hi = mid - 1;
    }
    return lo;
}

// ── solve ───────────────────────────────────────────────────────────────────
void solve() {
    int n;
    cin >> n;
    // ...
}

// ── main ────────────────────────────────────────────────────────────────────
int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--) solve();
    return 0;
}

/*
 * Paste when needed (full code in CP/):
 *
 *   SegTree / Lazy SegTree  → CP/segment_tree/
 *   Sparse Table            → CP/sparse_table/
 *   0-1 BFS                 → CP/graphs/shortest_path/zero_one_bfs.cpp
 *   Mo's, HLD, flows        → CP/graphs/
 *   FFT / NTT               → CP/math/fft_ntt.cpp
 *   ModInt                  → CP/number_theory/mod_int.cpp
 *   Treap                   → CP/data_structures/treap.cpp
 *   Aho-Corasick            → CP/string_algorithms/aho_corasick.cpp
 *   Ternary search          → CP/binary_search/ternary_search.cpp
 */