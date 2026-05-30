#include <bits/stdc++.h>
using namespace std;

// Rabin–Karp Algorithm (Double Hashing)
// Time Complexity: O(n + m)
// Space Complexity: O(1)

// mathematically double hashing to reduce collision probability (i.e spurious hits) to a negligible level (10^-10) times.
// Two different hash functions are used to compute two hash values for the pattern and the text windows.
// A match is declared only if both hash values match.

typedef long long ll;

class Solution
{
public:
    const ll RADIX_1 = 26;
    const ll MOD_1 = 1e9 + 7;
    const ll RADIX_2 = 27;
    const ll MOD_2 = 1e9 + 33;

    // 🔹 Compute hash pair for a string of length m
    pair<ll, ll> compute_hash(const string &str, ll m)
    {
        ll hash_1 = 0, hash_2 = 0;
        ll factor_1 = 1, factor_2 = 1;

        for (ll i = m - 1; i >= 0; i--)
        {
            hash_1 = (hash_1 + ((str[i] - 'a') * factor_1) % MOD_1) % MOD_1;
            factor_1 = (factor_1 * RADIX_1) % MOD_1;

            hash_2 = (hash_2 + ((str[i] - 'a') * factor_2) % MOD_2) % MOD_2;
            factor_2 = (factor_2 * RADIX_2) % MOD_2;
        }
        return {hash_1, hash_2};
    }

    // 🔹 Rabin–Karp function to find first occurrence of pattern in text
    int Rabin_karp(string text, string pattern)
    {
        ll n = text.size();
        ll m = pattern.size();
        if (n < m)
            return -1;

        ll MAX_WEIGHT_1 = 1, MAX_WEIGHT_2 = 1;
        for (ll i = 0; i < m; i++)
        {
            MAX_WEIGHT_1 = (MAX_WEIGHT_1 * RADIX_1) % MOD_1;
            MAX_WEIGHT_2 = (MAX_WEIGHT_2 * RADIX_2) % MOD_2;
        }

        pair<ll, ll> hash_pattern = compute_hash(pattern, m);
        pair<ll, ll> hash_window = {0, 0};

        for (ll i = 0; i <= n - m; i++)
        {
            if (i == 0)
            {
                hash_window = compute_hash(text, m);
            }
            else
            {
                hash_window.first = ((hash_window.first * RADIX_1) % MOD_1 - ((text[i - 1] - 'a') * MAX_WEIGHT_1) % MOD_1 + (text[i + m - 1] - 'a') + MOD_1) % MOD_1;

                hash_window.second = ((hash_window.second * RADIX_2) % MOD_2 - ((text[i - 1] - 'a') * MAX_WEIGHT_2) % MOD_2 + (text[i + m - 1] - 'a') + MOD_2) % MOD_2;
            }

            if (hash_pattern.first == hash_window.first &&
                hash_pattern.second == hash_window.second)
            {
                return i;
            }
        }
        return -1;
    }
};

// 🧪 Driver Code with multiple test cases
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution sol;

    vector<pair<string, string>> test_cases = {
        {"sadbutsad", "sad"},
        {"leetcode", "leeto"},
        {"aaaaa", "bba"},
        {"abcabcabc", "abc"},
        {"mississippi", "issi"},
        {"hello", "ll"},
        {"abracadabra", "cad"}};

    for (auto &[text, pattern] : test_cases)
    {
        int idx = sol.Rabin_karp(text, pattern);
        cout << "Text: " << text << "\n";
        cout << "Pattern: " << pattern << "\n";
        if (idx == -1)
            cout << "Pattern not found.\n";
        else
            cout << "Pattern found at idx: " << idx << "\n";
        cout << "------------------------\n";
    }

    return 0;
}
