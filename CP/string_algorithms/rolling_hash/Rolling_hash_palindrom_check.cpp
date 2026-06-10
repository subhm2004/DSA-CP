#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Palindrome_Check
{
public:
    const ll RADIX_1 = 26, MOD_1 = 1e9 + 7;
    const ll RADIX_2 = 27, MOD_2 = 1e9 + 33;

    string s;
    ll n;
    vector<ll> pref_1, pref_2, r_pref_1, r_pref_2, pow_1, pow_2;

    // Constructor — string ke liye prefix + reverse-prefix hash tables precompute karo.
    // Step 1: pow_1/pow_2 me RADIX^i store karo (substring hash formula ke liye).
    // Step 2: Left→right scan: pref[i+1] = pref[i]*RADIX + s[i] (forward hash).
    // Step 3: Same scan me reverse string ka r_pref bhi build (palindrome compare ke liye).
    Palindrome_Check(const string &str)
    {
        s = str;
        n = s.size();
        pref_1.assign(n + 1, 0);
        pref_2.assign(n + 1, 0);
        r_pref_1.assign(n + 1, 0);
        r_pref_2.assign(n + 1, 0);
        pow_1.assign(n + 1, 1);
        pow_2.assign(n + 1, 1);

        for (int i = 1; i <= n; i++)
        {
            pow_1[i] = (pow_1[i - 1] * RADIX_1) % MOD_1;
            pow_2[i] = (pow_2[i - 1] * RADIX_2) % MOD_2;
        }

        for (int i = 0; i < n; i++)
        {
            ll val = s[i] - 'a';

            pref_1[i + 1] = (pref_1[i] * RADIX_1 + val) % MOD_1;
            pref_2[i + 1] = (pref_2[i] * RADIX_2 + val) % MOD_2;

            ll r_val = s[n - 1 - i] - 'a';
            r_pref_1[i + 1] = (r_pref_1[i] * RADIX_1 + r_val) % MOD_1;
            r_pref_2[i + 1] = (r_pref_2[i] * RADIX_2 + r_val) % MOD_2;
        }
    }

    // get_Hash — substring s[l..r] ka double hash pair O(1) me nikalo.
    // Step 1: pref[r+1] me [0..r] ka hash hai; pref[l] me [0..l-1] ka.
    // Step 2: pref[l] * pow[r-l+1] se prefix portion "shift out" karo.
    // Step 3: Subtract karke [l..r] isolate karo; MOD add karke negative fix.
    pair<ll, ll> get_Hash(int l, int r)
    {
        ll hash_1 = (pref_1[r + 1] - pref_1[l] * pow_1[r - l + 1] % MOD_1 + MOD_1) % MOD_1;
        ll hash_2 = (pref_2[r + 1] - pref_2[l] * pow_2[r - l + 1] % MOD_2 + MOD_2) % MOD_2;
        return {hash_1 % MOD_1, hash_2 % MOD_2};
    }

    // get_Reverse_Hash — s[l..r] ke reverse direction ka hash (mirror mapping).
    // Step 1: Original [l..r] reverse me s_rev indices: rl = n-1-r, rr = n-1-l.
    // Step 2: r_pref arrays se reversed substring ka hash same formula se nikalo.
    // Step 3: Forward aur reverse hash compare se palindrome check fast hota hai.
    pair<ll, ll> get_Reverse_Hash(int l, int r)
    {
        int rl = n - 1 - r;
        int rr = n - 1 - l;
        ll hash_1 = (r_pref_1[rr + 1] - r_pref_1[rl] * pow_1[rr - rl + 1] % MOD_1 + MOD_1) % MOD_1;
        ll hash_2 = (r_pref_2[rr + 1] - r_pref_2[rl] * pow_2[rr - rl + 1] % MOD_2 + MOD_2) % MOD_2;
        return {hash_1 % MOD_1, hash_2 % MOD_2};
    }

    // is_Palindrome — [l..r] palindrome hai ya nahi (double hash equality se).
    // Step 1: get_Hash(l,r) se forward substring hash lo.
    // Step 2: get_Reverse_Hash(l,r) se usi range ka reversed hash lo.
    // Step 3: Dono pairs equal ho to true — char-by-char compare ki zarurat nahi.
    bool is_Palindrome(int l, int r)
    {
        return get_Hash(l, r) == get_Reverse_Hash(l, r);
    }
};

// main — "abacaba" pe alag-alag ranges ka palindrome check demo.
int main()
{
    string s = "abacaba";
    Palindrome_Check sh(s);

    cout << sh.is_Palindrome(0, 6) << "\n"; // 1
    cout << sh.is_Palindrome(1, 3) << "\n"; // 0
    cout << sh.is_Palindrome(2, 4) << "\n"; // 1
}
