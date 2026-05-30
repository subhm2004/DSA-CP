#include <bits/stdc++.h>
using namespace std;

class Combinatorics
{
public:
    typedef long long ll;
    const int M = 1e9 + 7; // Prime Modulo
    const int N = 2e5 + 2; // Factorial limit
    vector<ll> fact, invFact;

    ll mod(ll x) { return ((x % M + M) % M); }
    ll add(ll a, ll b) { return mod(a + b); }
    ll mul(ll a, ll b) { return mod(a * b); }

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

    ll inv(ll x) { return modPow(x, M - 2); }
    ll modSub(ll a, ll b) { return mod(a - b); }
    ll modDiv(ll a, ll b) { return mul(a, inv(b)); }

    Combinatorics()
    {
        fact.resize(N, 1);
        invFact.resize(N, 1);
        precalc();
    }

    void precalc()
    {
        // Precompute factorials
        for (int i = 1; i < N; i++)
        {
            fact[i] = mul(fact[i - 1], i);
        }

        // Precompute inverse factorials using Fermat's little theorem
        invFact[N - 1] = inv(fact[N - 1]);
        for (int i = N - 2; i >= 0; i--)
        {
            invFact[i] = mul(invFact[i + 1], i + 1);
        }
    }

    ll nCr(ll n, ll r)
    {
        if (r > n || r < 0)
            return 0;
        return mul(fact[n], mul(invFact[r], invFact[n - r]));
    }

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

    // Generic function to compute the number of distinct arrangements
    // of the characters in the given word.
    ll getDistinctWays(const string &word)
    {
        unordered_map<char, ll> freq;
        for (const auto &c : word)
        {
            freq[c]++;
        }

        ll ways = factorial(word.length());
        for (const auto &entry : freq)
        {
            ll count = entry.second;
            ways = mul(ways, invFact[count]); // use precomputed inverse factorial
        }
        return ways;
    }
    ll find_rank(const string &s)
    {
        int n = s.size();
        vector<int> freq(256, 0);

        // 🔹 Step 1: Har character ka frequency count lo
        for (char c : s)
            freq[c]++;

        ll rank = 1; // Rank 1 se start hota hai (lexicographic order me)

        // 🔹 Step 2: Har position pe check karo kitne smaller characters pehle aa sakte hain
        for (int i = 0; i < n; i++)
        {
            // Har character 's[i]' se chhote characters ke liye
            for (int ch = 0; ch < s[i]; ch++)
            {
                if (freq[ch] == 0)
                    continue; // Agar 'ch' already khatam ho gaya, skip karo

                // 🔸 Step 2.1: Agar hum 'ch' ko current position i pe fix karte hain
                // toh 'ch' ka frequency temporarily 1 kam kar do
                freq[ch]--;

                // 🔸 Step 2.2: Baaki ke (n - i - 1) characters ke permutations count karo
                // Formula: (n - i - 1)! / (freq[a]! * freq[b]! * ...)
                ll numerator = factorial(n - i - 1);
                ll denominator = 1;

                // Har character ka factorial multiply karo denominator me
                for (int c = 0; c < 256; c++)
                {
                    if (freq[c] > 0)
                        denominator = mul(denominator, factorial(freq[c]));
                }

                // 🔸 Step 2.3: Total possible strings starting with 'ch'
                // = numerator / denominator (mod ke sath)
                ll contribution = modDiv(numerator, denominator);

                // Rank me in permutations ka count add kar do
                rank = add(rank, contribution);

                // 🔸 Step 2.4: Frequency wapas restore karo
                freq[ch]++;
            }

            // 🔹 Step 3: Ab current character fix kar lo aur aage badho
            freq[s[i]]--;
        }

        // 🔹 Final rank return karo (1-based)
        return rank;
    }
};

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Combinatorics comb;

    // =======================
    // nCr & nPr Test Cases
    // =======================
    cout << "=== nCr & nPr Test Cases ===\n";
    vector<pair<Combinatorics::ll, Combinatorics::ll>> combTests = {{5, 2}, {10, 3}, {100, 50}};

    for (auto &[n, r] : combTests)
    {
        cout << "nCr(" << n << ", " << r << ") = " << comb.nCr(n, r) << "\n";
        cout << "nPr(" << n << ", " << r << ") = " << comb.nPr(n, r) << "\n";
    }

    // =======================
    // Factorial & Inverse Factorial Test Cases
    // =======================
    cout << "\n=== Factorial & Inverse Factorial Test Cases ===\n";
    vector<int> factTests = {0, 1, 5, 10, 20};

    for (int x : factTests)
    {
        cout << x << "! = " << comb.factorial(x) << ", inverse_factorial(" << x << ") = " << comb.inverse_factorial(x) << "\n";
    }

    // =======================
    // getDistinctWays Test Cases
    // =======================
    cout << "\n=== getDistinctWays Test Cases ===\n";
    vector<string> words = {"aabb", "abc", "aabbcc", "aaaa"};

    for (const string &word : words)
    {
        cout << "Distinct ways to arrange \"" << word << "\": " << comb.getDistinctWays(word) << "\n";
    }

    // =======================
    // findRank Test Cases
    // =======================
    cout << "\n=== findRank Test Cases ===\n";
    vector<string> rankTests = {"CAB", "AAB", "ABA", "BAA", "STRING"};

    for (const string &s : rankTests)
    {
        cout << "Lexicographic rank of \"" << s << "\": " << comb.find_rank(s) << "\n";
    }

    return 0;
}
