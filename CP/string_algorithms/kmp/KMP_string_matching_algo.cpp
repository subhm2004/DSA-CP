#include <bits/stdc++.h>
using namespace std;

// Knuth-Morris-Pratt (KMP) String Matching Algorithm
// Time Complexity: O(n + m)
// Space Complexity: O(m)
// where n is the length of text and m is the length of pattern
// This algorithm finds all occurrences of a pattern in a given text efficiently.
// It preprocesses the pattern to create an LPS (Longest Prefix Suffix) array that is used to skip unnecessary comparisons.

class Solution
{
public:
    // 🔹 Step 1: Build LPS (Longest Prefix Suffix) array
    void compute_LPS(const string &pattern, vector<int> &lps)
    {
        int length = 0;
        lps[0] = 0;

        int i = 1;
        while (i < pattern.size())
        {
            if (pattern[i] == pattern[length])
            {
                length++;
                lps[i] = length;
                i++;
            }
            else
            {
                if (length != 0)
                {
                    length = lps[length - 1];
                }
                else
                {
                    lps[i] = 0;
                    i++;
                }
            }
        }
    }

    // 🔹 Step 2: Find all occurrences using KMP
    vector<int> KMP(const string &text, const string &pattern)
    {
        vector<int> ans;
        if (pattern.empty())
            return ans;

        int n = text.length();
        int m = pattern.length();
        vector<int> lps(m, 0);
        compute_LPS(pattern, lps);

        int i = 0, j = 0;
        while (i < n)
        {
            if (text[i] == pattern[j])
            {
                i++;
                j++;
            }

            if (j == m)
            {
                ans.push_back(i - j); // Match found
                j = lps[j - 1];
            }
            else if (i < n && text[i] != pattern[j])
            {
                if (j != 0)
                    j = lps[j - 1];
                else
                    i++;
            }
        }
        return ans;
    }

    // 🔹 Step 3: Return first match index (like strStr)
    int KMP_first(const string &text, const string &pattern)
    {
        vector<int> matches = KMP(text, pattern);
        if (matches.empty())
            return -1;
        return matches[0];
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
        int index = sol.KMP_first(text, pattern);
        cout << "Text: " << text << "\n";
        cout << "Pattern: " << pattern << "\n";
        if (index == -1)
            cout << "Pattern not found.\n";
        else
            cout << "Pattern found at index: " << index << "\n";
        cout << "------------------------\n";
    }

    return 0;
}
