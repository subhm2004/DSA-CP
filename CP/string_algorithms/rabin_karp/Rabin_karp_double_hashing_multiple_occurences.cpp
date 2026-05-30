#include <bits/stdc++.h>
using namespace std;

// Rabin–Karp Algorithm (Double Hashing)
// Time Complexity: O(n + m) worst-case
// Space Complexity: O(k) for occurrences storage
// For double-hash, the probability of a spurious hit is negligible (like 10^-10), so verification is usually skipped.
// where n is the length of text and m is the length of pattern
// This algorithm finds all occurrences of a pattern in a given text efficiently using double hashing to minimize collisions.
// It computes two different hash values for the pattern and text windows, declaring a match only if both hash values match.
// Double hashing drastically reduces collisions, so character verification is usually unnecessary.

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
        ll hash1 = 0, hash2 = 0;
        ll factor1 = 1, factor2 = 1;

        for (ll i = m - 1; i >= 0; i--)
        {
            hash1 = (hash1 + ((str[i] - 'a') * factor1) % MOD_1) % MOD_1;
            factor1 = (factor1 * RADIX_1) % MOD_1;

            hash2 = (hash2 + ((str[i] - 'a') * factor2) % MOD_2) % MOD_2;
            factor2 = (factor2 * RADIX_2) % MOD_2;
        }
        return {hash1, hash2};
    }

    // 🔹 Rabin–Karp function to find all occurrences using double hashing
    vector<int> Rabin_karp_all(string text, string pattern)
    {
        vector<int> occurrences;
        ll n = text.size();
        ll m = pattern.size();
        if (n < m)
            return occurrences;

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

            if (hash_window == hash_pattern)
            {
                occurrences.push_back(i); // match found
            }
        }

        return occurrences;
    }
};

// 🧪 Driver Code
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution sol;

    vector<pair<string, string>> test_cases = {
        {"sadbutsad", "sad"},
        {"leetcode", "leeto"},
        {"aaaaa", "aa"},
        {"abcabcabc", "abc"},
        {"mississippi", "issi"},
        {"hello", "ll"},
        {"abracadabra", "abra"}};

    for (auto &[text, pattern] : test_cases)
    {
        vector<int> indices = sol.Rabin_karp_all(text, pattern);
        cout << "Text: " << text << "\n";
        cout << "Pattern: " << pattern << "\n";
        if (indices.empty())
            cout << "Pattern not found.\n";
        else
        {
            cout << "Pattern found at indices: ";
            for (int idx : indices)
                cout << idx << " ";
            cout << "\n";
        }
        cout << "------------------------\n";
    }

    return 0;
}
