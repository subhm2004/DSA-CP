#include <bits/stdc++.h> // Prefix hashing and Suffix hashing dono kr rhe hai taaki palindrome check kr ske
using namespace std;
typedef long long ll;
// Double Hashing for Substring Hashing with Palindrome Check
//
class Sub_String_Hash
{
public:
    const ll RADIX_1 = 26, MOD_1 = 1e9 + 7;
    const ll RADIX_2 = 27, MOD_2 = 1e9 + 33;

    string s;
    ll n;
    vector<ll> pref_1, pref_2, r_pref_1, r_pref_2, pow_1, pow_2;

    Sub_String_Hash(const string &str)
    {
        s = str;
        n = s.size();
        pref_1.assign(n + 1, 0);
        pref_2.assign(n + 1, 0);
        r_pref_1.assign(n + 1, 0);
        r_pref_2.assign(n + 1, 0);
        pow_1.assign(n + 1, 1);
        pow_2.assign(n + 1, 1);

        // precompute powers
        for (int i = 1; i <= n; i++)
        {
            pow_1[i] = (pow_1[i - 1] * RADIX_1) % MOD_1;
            pow_2[i] = (pow_2[i - 1] * RADIX_2) % MOD_2;
        }

        for (int i = 0; i < n; i++)
        {
            ll val = s[i] - 'a'; // mapping 0-25

            // prefix hashing formula (0-based indexing):
            /*
               pref[i+1] = hash of substring s[0..i]
               pref[0] = 0 (empty string)

               Hash of substring s[l..r] (0-based) is:
               hash(s[l..r]) = (pref[r+1] - pref[l]*RADIX^(r-l+1) % MOD + MOD) % MOD

               Explanation:
               - pref[r+1] → hash of first r+1 characters
               - pref[l] → hash of first l characters
               - Multiply by RADIX^(r-l+1) to "shift out" the prefix
            */

            // prefix hashing formula:
            /*
             pref[i+1] = hash of first i+1 characters using polynomial rolling hash formula:

             hash(s[0..i]) = s[0] * RADIX^i + s[1] * RADIX^(i-1) + ... + s[i] * RADIX^0

             This is prefix hashing.

             Why i+1?
             Because pref[0] = 0 for the empty string,
             so pref[i+1] stores the hash of the first i+1 characters.
             */

            pref_1[i + 1] = (pref_1[i] * RADIX_1 + val) % MOD_1;
            pref_2[i + 1] = (pref_2[i] * RADIX_2 + val) % MOD_2;

            ll r_val = s[n - 1 - i] - 'a'; // reverse
            r_pref_1[i + 1] = (r_pref_1[i] * RADIX_1 + r_val) % MOD_1;
            r_pref_2[i + 1] = (r_pref_2[i] * RADIX_2 + r_val) % MOD_2;
        }
    }

    /*
   Derivation of substring hash formula:

   Let pref[i+1] = hash of substring s[0..i] using RADIX-based polynomial hash:
       pref[i+1] = s[0]*RADIX^i + s[1]*RADIX^(i-1) + ... + s[i]*RADIX^0

   Example:
       s = "abcd", RADIX = 10
       pref[4] = a*10^3 + b*10^2 + c*10^1 + d*10^0

   Goal: compute hash(s[l..r]), 0-based indexing

       hash(s[l..r]) = s[l]*RADIX^(r-l) + s[l+1]*RADIX^(r-l-1) + ... + s[r]*RADIX^0

   Observation:
       pref[r+1] contains hash of s[0..r]:
           pref[r+1] = s[0]*RADIX^r + s[1]*RADIX^(r-1) + ... + s[r]*RADIX^0

       pref[l] contains hash of s[0..l-1]:
           pref[l] = s[0]*RADIX^(l-1) + s[1]*RADIX^(l-2) + ... + s[l-1]*RADIX^0

   To isolate s[l..r], shift pref[l] to align with pref[r+1]:
       pref[l] * RADIX^(r-l+1)
         = (s[0]*RADIX^(l-1) + ... + s[l-1]*RADIX^0) * RADIX^(r-l+1)
         = s[0]*RADIX^r + ... + s[l-1]*RADIX^(r-l+1)

   Subtract shifted prefix from pref[r+1]:
       pref[r+1] - pref[l]*RADIX^(r-l+1)
       = (s[0]*RADIX^r + ... + s[r]*RADIX^0)
         - (s[0]*RADIX^r + ... + s[l-1]*RADIX^(r-l+1))
       = s[l]*RADIX^(r-l) + ... + s[r]*RADIX^0
       = hash(s[l..r])

   Finally, handle modulo correctly:
       hash(s[l..r]) = (pref[r+1] - pref[l]*RADIX^(r-l+1) % MOD + MOD) % MOD

   Summary:
   - pref[r+1] → hash of first r+1 characters
   - pref[l] → hash of first l characters
   - Multiply pref[l] by RADIX^(r-l+1) to "shift out" the prefix
   - Add MOD before modulo to avoid negative numbers
    */

    pair<ll, ll> get_Hash(int l, int r)
    {
        ll hash_1 = (pref_1[r + 1] - pref_1[l] * pow_1[r - l + 1] % MOD_1 + MOD_1) % MOD_1;
        ll hash_2 = (pref_2[r + 1] - pref_2[l] * pow_2[r - l + 1] % MOD_2 + MOD_2) % MOD_2;
        return {hash_1 % MOD_1, hash_2 % MOD_2};
    }
    /**
     * We have:
     *   Original string: s[0 ... n-1]
     *   Reversed string: s_rev[i] = s[n-1 - i]
     *
     * Suppose we want the hash of reversed substring s[l..r].
     * That is, we want hash(s[r] s[r-1] ... s[l]).
     *
     * We already precomputed prefix hashes for s_rev.
     * So we just need to find the substring in s_rev that corresponds
     * to this reversed segment.
     *
     * Mathematical mapping:
     *   s_rev[i] = s[n-1 - i]
     *
     * We need to find indices (rl, rr) in s_rev
     * such that s_rev[rl..rr] = reverse(s[l..r]).
     *
     * Step 1: Find where s[r] appears in s_rev
     *   s_rev[rl] = s[r]
     *   => n - 1 - rl = r
     *   => rl = n - 1 - r
     *
     * Step 2: Find where s[l] appears in s_rev
     *   s_rev[rr] = s[l]
     *   => n - 1 - rr = l
     *   => rr = n - 1 - l
     *
     * Therefore:
     *   The reversed substring [l..r] in s
     *   corresponds to substring [rl..rr] in s_rev,
     *   where rl = n-1-r and rr = n-1-l.
     */
    pair<ll, ll> get_Reverse_Hash(int l, int r)
    {
        int rl = n - 1 - r; // reversed substring start
        int rr = n - 1 - l; // reversed substring end
        ll hash_1 = (r_pref_1[rr + 1] - r_pref_1[rl] * pow_1[rr - rl + 1] % MOD_1 + MOD_1) % MOD_1;
        ll hash_2 = (r_pref_2[rr + 1] - r_pref_2[rl] * pow_2[rr - rl + 1] % MOD_2 + MOD_2) % MOD_2;
        return {hash_1 % MOD_1, hash_2 % MOD_2};
    }

    bool is_Palindrome(int l, int r)
    {
        auto h_f = get_Hash(l, r);
        auto h_r = get_Reverse_Hash(l, r);
        return h_f == h_r;
    }
};

int main()
{
    string s = "abacaba";
    Sub_String_Hash sh(s);

    cout << sh.is_Palindrome(0, 6) << "\n"; // 1
    cout << sh.is_Palindrome(1, 3) << "\n"; // 0
    cout << sh.is_Palindrome(2, 4) << "\n"; // 1
}
