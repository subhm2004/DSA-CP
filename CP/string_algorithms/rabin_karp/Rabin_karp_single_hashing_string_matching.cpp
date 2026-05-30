#include <bits/stdc++.h>
using namespace std;

// Rabin–Karp Algorithm (Single Hash) with character verification
// Time Complexity: O(n + m) on average
// worst-case time complexity: O(n * m) due to spurious hits
// Space Complexity: O(1)

// in competitive programming:
// For single-hash, we often add the character verification loop after hash matches (as we did above).
// For double-hash, the probability of a spurious hit is negligible (like 10^-10), so verification is usually skipped.

typedef long long ll;

class Solution
{
public:
    const ll RADIX = 26;
    const ll MOD = 1e9 + 7;

    // 🔹 Compute hash for a string of length m
    ll compute_hash(const string &str, ll m)
    {
        ll hash_val = 0;
        ll factor = 1;

        for (ll i = m - 1; i >= 0; i--)
        {
            hash_val = (hash_val + ((str[i] - 'a') * factor) % MOD) % MOD;
            factor = (factor * RADIX) % MOD;
        }
        return hash_val;
    }

    // 🔹 Rabin–Karp function to find first occurrence of pattern in text
    int Rabin_karp(string text, string pattern)
    {
        ll n = text.size();
        ll m = pattern.size();
        if (n < m)
            return -1;

        // Compute RADIX^m % MOD
        ll MAX_WEIGHT = 1;
        for (ll i = 0; i < m; i++)
            MAX_WEIGHT = (MAX_WEIGHT * RADIX) % MOD;

        ll hash_pattern = compute_hash(pattern, m);
        ll hash_window = 0;

        for (ll i = 0; i <= n - m; i++)
        {
            if (i == 0)
            {
                hash_window = compute_hash(text, m);
            }
            else
            {
                hash_window = ((hash_window * RADIX) % MOD - ((text[i - 1] - 'a') * MAX_WEIGHT) % MOD + (text[i + m - 1] - 'a') + MOD) % MOD;
            }

            // Verify characters to avoid spurious hits
            if (hash_pattern == hash_window)
            {
                bool match = true;
                for (ll j = 0; j < m; j++)
                {
                    if (text[i + j] != pattern[j])
                    {
                        match = false;
                        break;
                    }
                }
                if (match)
                    return i; // first match found
            }
        }

        return -1; // no match
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
        {"aaaaa", "bba"},
        {"abcabcabc", "abc"},
        {"mississippi", "issi"},
        {"hello", "ll"},
        {"abracadabra", "cad"},
        {"cadbbca", "fghivbt"} // edge case with potential spurious hit
    };

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
