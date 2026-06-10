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
    // compute_LPS — pattern ka Longest Proper Prefix which is also Suffix array banao.
    // Step 1: lps[0] = 0 (single char ka koi proper prefix nahi).
    // Step 2: Agar pattern[i] == pattern[length] to length++ aur lps[i] = length.
    // Step 3: Mismatch pe length = lps[length-1] se fallback (KMP jaisa backtrack).
    // Step 4: length 0 ho to lps[i] = 0 aur i aage badhao — O(m) me poora array fill.
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

    // KMP — text me pattern ke saare occurrences dhundho (LPS se skip).
    // Step 1: Pehle compute_LPS se pattern ka fallback array banao.
    // Step 2: i = text pointer, j = pattern pointer — dono aage badhte hain match pe.
    // Step 3: j == m pe match mila → ans me i-j push, j = lps[j-1] (overlap handle).
    // Step 4: Mismatch pe j != 0 ho to j = lps[j-1], warna i++ — brute force se fast.
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

    // KMP_first — sirf pehla match index chahiye ho to (LeetCode strStr jaisa).
    // Step 1: KMP() se saare indices nikalo.
    // Step 2: Empty ho to -1, warna matches[0] return — baaki matches ignore.
    int KMP_first(const string &text, const string &pattern)
    {
        vector<int> matches = KMP(text, pattern);
        if (matches.empty())
            return -1;
        return matches[0];
    }
};

// main — multiple test cases pe KMP_first run karke first match index print karo.
// Har case me text, pattern aur result dikhao — pattern na mile to "not found".
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
