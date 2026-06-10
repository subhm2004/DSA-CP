#include <bits/stdc++.h> // LC 3932 — Kth root of a number
using namespace std;
typedef long long ll;

// ════════════════════════════════════════════════════════════════════════════
// K-th ROOT — Newton-Raphson + Binary Search (LeetCode 3932 style)
// ────────────────────────────────────────────────────────────────────────────
// Goal: floor(n^(1/k)) exactly nikalo
// Newton: x_next = [(k-1)*x + n/x^(k-1)] / k
// Phase 2/3: float error fix — root up/down nudge via fastPower check
// Count kth powers in [l,r]: floor(r^(1/k)) - floor((l-1)^(1/k))
// ════════════════════════════════════════════════════════════════════════════

// ── mul: safe multiply — overflow pe limit+1 return ───────────────────────
ll mul(ll a, ll b, ll limit)
{
    if (a == 0 || b == 0)
        return 0;
    if (a > limit / b) // overflow would occur
        return limit + 1;
    return a * b;
}

// ── fastPower: base^exp with overflow guard (returns limit+1 if exceeds) ────
ll fastPower(ll base, int exp, ll limit)
{
    ll ans = 1;
    while (exp)
    {
        if (exp & 1)
            ans = mul(ans, base, limit);
        base = mul(base, base, limit);
        exp >>= 1;
    }
    return ans;
}

// ── kthRoot_Newton: floor(n^(1/k)) via Newton + precision fix ───────────────
//   1) Newton float iterations: x_next = [(k-1)*x + n/x^(k-1)] / k
//   2) truncate to ll, phir while (root+1)^k <= n -> root++ (nudge up)
//   3) while root^k > n -> root-- (nudge down)
//   4) exact floor return
ll kthRoot_Newton(ll n, int k)
{
    if (n < 0)
        return -1; // negative has no real kth root in this context
    if (n == 0 || n == 1)
        return n;

    // ── Phase 1: Newton-Raphson float iterations ──
    long double x = (long double)n;
    const long double eps = 1e-15;
    for (int iter = 0; iter < 300; iter++)
    {
        // x_next = [(k-1)*x + n/x^(k-1)] / k
        long double xpow_km1 = powl(x, (long double)(k - 1));
        long double x_next = ((long double)(k - 1) * x + (long double)n / xpow_km1) / (long double)k;

        if (abs(x - x_next) < eps)
            break;

        x = x_next;
    }

    ll root = (ll)x; // truncate → may be off by 1 due to float error

    // ── Phase 2: Precision fix — nudge UP ──
    //
    //  Problem: float gave root=2 but true answer is 3
    //           (Newton converged to 2.9999998, truncated to 2)
    //
    //  Fix: while (root+1)^k still fits (≤ n), increment root
    //
    //  Example: n=27, k=3
    //    root=2, fastPower(3,3,27)=27 ≤ 27 → root=3
    //    fastPower(4,3,27)=64 > 27 → stop
    //    root=3 (correct)
    //
    while (fastPower(root + 1, k, n) <= n)
        root++;

    // ── Phase 3: Precision fix — nudge DOWN ──
    //
    //  Problem: float gave root=4 but true answer is 3
    //           (rare, but possible for large n)
    //
    //  Fix: while root^k > n, decrement root
    //
    //  Example: root=4, fastPower(4,3,27)=64 > 27 → root=3
    //           fastPower(3,3,27)=27 ≤ 27 → stop
    //
    while (root > 0 && fastPower(root, k, n) > n)
        root--;

    // Now: root^k <= n  AND  (root+1)^k > n
    // i.e., root = floor(n^(1/k))  EXACTLY
    return root;
}

// ── kthRoot_BinarySearch: floor(n^(1/k)) via BS on x ────────────────────────
//   1) x^k monotonic increasing -> BS for largest x with x^k <= n
//   2) fastPower(mid,k,n) overflow-safe compare
ll kthRoot_BinarySearch(ll n, int k)
{
    if (n < 0)
        return -1;
    if (n == 0 || n == 1)
        return n;

    ll lo = 1, hi = n, ans = 0;

    while (lo <= hi)
    {
        ll mid = lo + (hi - lo) / 2; // avoids (lo+hi) overflow

        ll pw = fastPower(mid, k, n); // mid^k, capped at n+1 on overflow

        if (pw <= n)
        {
            ans = mid; // mid valid, try larger
            lo = mid + 1;
        }
        else
        {
            hi = mid - 1; // mid^k too large
        }
    }
    return ans;
}

// ── countKthPowers_Newton: [l,r] me kitne perfect k-th powers ───────────────
//   count = floor(r^(1/k)) - floor((l-1)^(1/k))
int countKthPowers_Newton(int l, int r, int k)
{
    ll right = kthRoot_Newton((ll)r, k);
    ll left = kthRoot_Newton((ll)l - 1, k);

    return (int)(right - left);
}

// ── countKthPowers_BinarySearch: same count, BS approach se ─────────────────
int countKthPowers_BinarySearch(int l, int r, int k)
{
    ll right = kthRoot_BinarySearch((ll)r, k);
    ll left = kthRoot_BinarySearch((ll)l - 1, k);

    return (int)(right - left);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Test cases: {l, r, k, expected_answer}
    struct TC
    {
        int l, r, k, exp;
    };
    vector<TC> tests = {
        {1, 9, 3, 2},
        {8, 30, 2, 3},
        {0, 0, 5, 1}, // 0 = 0^5 → answer 1
        {1, 1, 1, 1},
        {27, 27, 3, 1},            // exactly 3^3
        {26, 28, 3, 1},            // only 27
        {1, 1000000000, 3, 1000},  // floor(cbrt(1e9)) = 1000
        {1, 1000000000, 2, 31622}, // floor(sqrt(1e9)) = 31622
        {1, 1000000000, 30, 1},    // 2^30 = 1073741824 > 1e9, only x=1
        {1, 1000000000, 1, 1000000000},
        {4, 8, 2, 1}, // only 4=2^2, (not 8 since sqrt(8)~2.8)
        {4, 9, 2, 2}, // 4=2^2, 9=3^2
    };

    printf("%-6s %-12s %-4s %-5s %-7s %-7s\n",
           "l", "r", "k", "exp", "Newton", "BinSch");
    printf("%s\n", string(50, '-').c_str());

    bool all_ok = true;
    for (auto &t : tests)
    {
        int nr = countKthPowers_Newton(t.l, t.r, t.k);
        int bs = countKthPowers_BinarySearch(t.l, t.r, t.k);
        bool ok = (nr == t.exp && bs == t.exp);
        if (!ok)
            all_ok = false;

        printf("%-6d %-12d %-4d %-5d %-7d %-7d %s\n",
               t.l, t.r, t.k, t.exp, nr, bs,
               ok ? "PASS" : "FAIL <<");
    }
    printf("%s\n", string(50, '-').c_str());
    printf("%s\n", all_ok ? "All tests PASSED" : "Some FAILED");

    return 0;
}
