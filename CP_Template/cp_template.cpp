/*
 * ============================================================================
 * TOPIC    : CP Template — contest starter
 * FILE     : cp_template.cpp
 * PROBLEM  : Single-file boilerplate — copy this, likho sirf solve()
 * APPROACH : Fast I/O + LOCAL-only file redirect + dbg() macro + common aliases
 * COMPLEX  : Boilerplate O(1); actual complexity solve() par depend karti hai
 * ============================================================================
 *
 * CONTEST MODE:
 *   cp CP_Template/cp_template.cpp sol.cpp
 *   g++ -std=c++17 -O2 -DLOCAL sol.cpp -o sol && ./sol
 *
 * -DLOCAL kya karta hai:
 *   1) input.txt se read + output.txt me write (stdin type karne ki zarurat nahi)
 *   2) dbg(...) macro on — variables stderr pe print, judge output kharab nahi hota
 *   3) Judge pe submit karte waqt -DLOCAL mat do → dono cheezein apne aap band
 *
 * MULTI-TEST:
 *   Default me T testcases padhta hai. Single-test problem ho to main() me
 *   MULTITEST wali line comment kar do (neeche marked hai).
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// ALIASES & MACROS
// ────────────────────────────────────────────────────────────────────────────
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vll = vector<ll>;

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((int)(x).size())
#define pb push_back
#define eb emplace_back

const ll MOD = 1'000'000'007LL;
const ll INF = 4e18;          // ll ke liye "infinity" — overflow se safe
const int IINF = 1e9 + 7;     // int ke liye
const ld PI = acosl(-1.0L);

// ════════════════════════════════════════════════════════════════════════════
// dbg() — sirf LOCAL pe. stderr pe jaata hai, judge output untouched.
// Use: dbg(n, k, a);  →  [n, k, a] = 5, 3, [1, 2, 3]
// ────────────────────────────────────────────────────────────────────────────
#ifdef LOCAL
template <class T>
auto _print(ostream &os, const T &x) -> decltype(os << x, void()) { os << x; }

template <class T, class... Rest>
void _print(ostream &os, const pair<T, Rest...> &p);

// Har container (vector/set/map) ke liye ek hi generic printer
template <class C, class = typename C::const_iterator>
void _print(ostream &os, const C &c) {
    os << '[';
    for (auto it = c.begin(); it != c.end(); ++it) {
        if (it != c.begin()) os << ", ";
        _print(os, *it);
    }
    os << ']';
}
template <class A, class B>
void _print(ostream &os, const pair<A, B> &p) {
    os << '(';
    _print(os, p.first);
    os << ", ";
    _print(os, p.second);
    os << ')';
}
inline void _dbg(ostream &) {}
template <class T, class... Rest>
void _dbg(ostream &os, const T &x, const Rest &...rest) {
    _print(os, x);
    if constexpr (sizeof...(rest)) os << ", ";
    _dbg(os, rest...);
}
#define dbg(...)                                     \
    do {                                             \
        cerr << "[" << #__VA_ARGS__ << "] = ";       \
        _dbg(cerr, __VA_ARGS__);                     \
        cerr << '\n';                                \
    } while (0)
#else
#define dbg(...) ((void)0)
#endif

// ════════════════════════════════════════════════════════════════════════════
// CHOTE HELPERS
// ────────────────────────────────────────────────────────────────────────────
template <class T> bool ckmin(T &a, const T &b) { return b < a ? a = b, true : false; }
template <class T> bool ckmax(T &a, const T &b) { return a < b ? a = b, true : false; }

ll power(ll b, ll e, ll m = MOD) {  // (b^e) % m — binary exponentiation
    ll r = 1 % m;
    b %= m;
    while (e > 0) {
        if (e & 1) r = (__int128)r * b % m;
        b = (__int128)b * b % m;
        e >>= 1;
    }
    return r;
}

// unordered_map ko CF pe anti-hash test se bachata hai.
// Use: unordered_map<ll, int, custom_hash> mp;
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t SEED =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + SEED);
    }
};

// ════════════════════════════════════════════════════════════════════════════
// SOLVE — poora logic yahin likho. Ek testcase handle karta hai.
// ────────────────────────────────────────────────────────────────────────────
void solve() {
    int n;
    cin >> n;

    vector<ll> a(n);
    for (auto &x : a) cin >> x;

    ll sum = accumulate(all(a), 0LL);
    dbg(n, a, sum);  // LOCAL pe hi dikhega

    cout << sum << '\n';
}

// ════════════════════════════════════════════════════════════════════════════
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    auto _start = chrono::high_resolution_clock::now();
#endif

    int T = 1;
    cin >> T;  // ── MULTITEST: single-test problem ho to ye line comment karo
    while (T--) solve();

#ifdef LOCAL
    auto _ms = chrono::duration_cast<chrono::milliseconds>(
                   chrono::high_resolution_clock::now() - _start)
                   .count();
    cerr << "\n[time] " << _ms << " ms\n";
#endif
    return 0;
}
