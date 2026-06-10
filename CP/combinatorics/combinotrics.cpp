#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// COMBINATORICS — nCr, nPr, factorial, distinct permutations, lexicographic rank
// ────────────────────────────────────────────────────────────────────────────
// Mod = 1e9+7 (prime) → Fermat se inverse: a^(-1) ≡ a^(M-2) (mod M)
// fact[i] aur invFact[i] precompute → har nCr/nPr O(1)
// COMPLEX: precalc O(N)  |  query O(1)  |  find_rank O(n * alphabet)
// ════════════════════════════════════════════════════════════════════════════

class Combinatorics
{
public:
    typedef long long ll;
    const int M = 1e9 + 7; // prime modulo — Fermat inverse ke liye zaroori
    const int N = 2e5 + 2; // max n jahan tak fact precompute hoga
    vector<ll> fact, invFact;

    // ── mod: negative handle karke [0, M) me lao ──
    ll mod(ll x) { return ((x % M + M) % M); }
    ll add(ll a, ll b) { return mod(a + b); }
    ll mul(ll a, ll b) { return mod(a * b); }

    // ── modPow: binary exponentiation — a^b mod M ──
    //   1) ans = 1, jab tak b > 0
    //   2) agar b ka LSB 1 hai → ans *= a
    //   3) a *= a, b >>= 1
    ll modPow(ll a, ll b)
    {
        ll ans = 1;
        while (b)
        {
            if (b & 1)
                ans = mul(ans, a);
            a = mul(a, a);
            b >>= 1;
        }
        return ans;
    }

    // ── inv: modular inverse — Fermat: x^(M-2) mod M (M prime) ──
    ll inv(ll x) { return modPow(x, M - 2); }
    ll modSub(ll a, ll b) { return mod(a - b); }
    ll modDiv(ll a, ll b) { return mul(a, inv(b)); }

    // ── Combinatorics: constructor me fact + invFact precompute ──
    Combinatorics()
    {
        fact.resize(N, 1);
        invFact.resize(N, 1);
        precalc();
    }

    // ── precalc: factorial aur inverse factorial tables banao ──
    //   1) fact[i] = i! mod M — forward loop
    //   2) invFact[N-1] = (N-1)! ka inverse — ek baar modPow
    //   3) backward: invFact[i] = invFact[i+1] * (i+1) — O(N) total inverse
    void precalc()
    {
        for (int i = 1; i < N; i++)
            fact[i] = mul(fact[i - 1], i);

        invFact[N - 1] = inv(fact[N - 1]);
        for (int i = N - 2; i >= 0; i--)
            invFact[i] = mul(invFact[i + 1], i + 1);
    }

    // ── nCr: "n me se r choose" — order matter nahi ──
    //   Formula: n! / (r! * (n-r)!)  →  fact[n] * invFact[r] * invFact[n-r]
    ll nCr(ll n, ll r)
    {
        if (r > n || r < 0)
            return 0;
        return mul(fact[n], mul(invFact[r], invFact[n - r]));
    }

    // ── nPr: "n me se r permute" — order matter karta hai ──
    //   Formula: n! / (n-r)!
    ll nPr(ll n, ll r)
    {
        if (r > n || r < 0)
            return 0;
        return mul(fact[n], invFact[n - r]);
    }

    ll factorial(ll r)
    {
        if (r < 0)
            return 0;
        return fact[r];
    }

    ll inverse_factorial(ll r)
    {
        if (r < 0)
            return 0;
        return invFact[r];
    }

    // ── getDistinctWays: string ke distinct permutations ──
    //   Formula: n! / (f1! * f2! * ...)  jahan fi = char i ki frequency
    //   Example: "aabb" → 4!/(2!*2!) = 6
    ll getDistinctWays(const string &word)
    {
        unordered_map<char, ll> freq;
        for (const auto &c : word)
            freq[c]++;

        ll ways = factorial(word.length());
        for (const auto &entry : freq)
            ways = mul(ways, invFact[entry.second]);
        return ways;
    }

    // ── find_rank: string ka lexicographic rank (1-based) ──
    //   Har position pe chhote characters try karo, unke permutations count jodo
    //   1) freq array banao
    //   2) position i pe har ch < s[i] ke liye contribution add
    //   3) contribution = (n-i-1)! / (remaining freq factorials)
    //   4) current char fix karo, freq--, aage badho
    ll find_rank(const string &s)
    {
        int n = s.size();
        vector<int> freq(256, 0);

        for (char c : s)
            freq[c]++;

        ll rank = 1; // rank 1 se start (1-indexed)

        for (int i = 0; i < n; i++)
        {
            for (int ch = 0; ch < s[i]; ch++)
            {
                if (freq[ch] == 0)
                    continue;

                freq[ch]--; // is position pe 'ch' fix kiya

                ll numerator = factorial(n - i - 1);
                ll denominator = 1;
                for (int c = 0; c < 256; c++)
                    if (freq[c] > 0)
                        denominator = mul(denominator, factorial(freq[c]));

                ll contribution = modDiv(numerator, denominator);
                rank = add(rank, contribution);

                freq[ch]++; // restore — next ch try karne ke liye
            }

            freq[s[i]]--; // current char fix, aage badho
        }

        return rank;
    }
};

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Combinatorics comb;

    cout << "=== nCr & nPr Test Cases ===\n";
    vector<pair<Combinatorics::ll, Combinatorics::ll>> combTests = {{5, 2}, {10, 3}, {100, 50}};

    for (auto &[n, r] : combTests)
    {
        cout << "nCr(" << n << ", " << r << ") = " << comb.nCr(n, r) << "\n";
        cout << "nPr(" << n << ", " << r << ") = " << comb.nPr(n, r) << "\n";
    }

    cout << "\n=== Factorial & Inverse Factorial Test Cases ===\n";
    vector<int> factTests = {0, 1, 5, 10, 20};

    for (int x : factTests)
        cout << x << "! = " << comb.factorial(x) << ", inverse_factorial(" << x << ") = " << comb.inverse_factorial(x) << "\n";

    cout << "\n=== getDistinctWays Test Cases ===\n";
    vector<string> words = {"aabb", "abc", "aabbcc", "aaaa"};

    for (const string &word : words)
        cout << "Distinct ways to arrange \"" << word << "\": " << comb.getDistinctWays(word) << "\n";

    cout << "\n=== findRank Test Cases ===\n";
    vector<string> rankTests = {"CAB", "AAB", "ABA", "BAA", "STRING"};

    for (const string &s : rankTests)
        cout << "Lexicographic rank of \"" << s << "\": " << comb.find_rank(s) << "\n";

    return 0;
}
