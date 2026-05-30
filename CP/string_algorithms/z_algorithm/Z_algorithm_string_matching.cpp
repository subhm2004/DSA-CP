#include <bits/stdc++.h>
using namespace std;
class Z_Algorithm
{
public:
    /*
        Function: compute_z_array
        Purpose: Computes Z-array for the given string s.
                 z[i] = length of the longest substring starting from i
                        that matches the prefix of s.
    */
    vector<int> compute_z_array(const string &s)
    {
        int n = s.size();
        vector<int> z(n, 0);
        int l = 0, r = 0; // [l, r] → current Z-box window

        for (int i = 1; i < n; i++)
        {
            /* If i lies inside [l, r], reuse previous Z values */
            if (i <= r)
                z[i] = min(r - i + 1, z[i - l]);

            /* Try to extend match beyond the known window */
            while (i + z[i] < n && s[z[i]] == s[i + z[i]])
                z[i]++;

            /* Update [l, r] if extended past r */
            if (i + z[i] - 1 > r)
            {
                l = i;
                r = i + z[i] - 1;
            }
        }
        return z;
    }

    /*
        Function: search
        Purpose: Finds all occurrences of `pattern` inside `text`
                 using Z-algorithm.
        Returns: A vector containing all starting indices (0-based)
                 where pattern is found in text.
    */
    vector<int> search(const string &text, const string &pattern)
    {
        /* Combine pattern and text with a unique separator '$' */
        string combined = pattern + '$' + text;
        vector<int> z = compute_z_array(combined);
        vector<int> positions;

        int pLen = pattern.size();

        for (int i = 0; i < z.size(); i++)
        {
            /*
                If z[i] == pLen, it means:
                - Substring starting at i matches entire pattern.
                - Text part starts from index (pLen + 1) in combined string.
                So, position in text = i - (pLen + 1)
            */
            if (z[i] == pLen)
                positions.push_back(i - pLen - 1);
        }

        return positions;
    }
};

/* ---------------- MAIN FUNCTION ---------------- */
int main()
{
    Z_Algorithm zAlgo; // Create object of class

    /* Test 1 */
    string text1 = "ababbabababa";
    string pattern1 = "aba";
    vector<int> res1 = zAlgo.search(text1, pattern1);
    cout << "Test 1: Text = \"" << text1 << "\", Pattern = \"" << pattern1 << "\"\n";
    cout << "→ Pattern found at indices: ";
    for (int i : res1)
        cout << i << " ";
    cout << "\n\n";

    /* Test 2 */
    string text2 = "aaaaa";
    string pattern2 = "aa";
    vector<int> res2 = zAlgo.search(text2, pattern2);
    cout << "Test 2: Text = \"" << text2 << "\", Pattern = \"" << pattern2 << "\"\n";
    cout << "→ Pattern found at indices: ";
    for (int i : res2)
        cout << i << " ";
    cout << "\n\n";

    /* Test 3 */
    string text3 = "mississippi";
    string pattern3 = "issi";
    vector<int> res3 = zAlgo.search(text3, pattern3);
    cout << "Test 3: Text = \"" << text3 << "\", Pattern = \"" << pattern3 << "\"\n";
    cout << "→ Pattern found at indices: ";
    for (int i : res3)
        cout << i << " ";
    cout << "\n\n";

    /* Test 4 */
    string text4 = "abcdef";
    string pattern4 = "xyz";
    vector<int> res4 = zAlgo.search(text4, pattern4);
    cout << "Test 4: Text = \"" << text4 << "\", Pattern = \"" << pattern4 << "\"\n";
    cout << "→ Pattern found at indices: ";
    if (res4.empty())
        cout << "No match found";
    else
        for (int i : res4)
            cout << i << " ";
    cout << "\n\n";

    /* Test 5 */
    string text5 = "abababababa";
    string pattern5 = "ababa";
    vector<int> res5 = zAlgo.search(text5, pattern5);
    cout << "Test 5: Text = \"" << text5 << "\", Pattern = \"" << pattern5 << "\"\n";
    cout << "→ Pattern found at indices: ";
    for (int i : res5)
        cout << i << " ";
    cout << "\n";

    return 0;
}
