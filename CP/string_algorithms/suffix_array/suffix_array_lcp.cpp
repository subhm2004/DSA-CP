/*
 * ============================================================================
 * TOPIC    : Suffix Array + LCP
 * FILE     : suffix_array_lcp.cpp
 * PROBLEM  : Build suffix array and LCP array for string s
 * APPROACH : SA — doubling sort O(n log^2 n); LCP — Kasai O(n)
 * COMPLEX  : Time: O(n log^2 n)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

vector<int> buildSuffixArray(const string &s) {
    int n = s.size();
    vector<int> sa(n), rnk(n), tmp(n);

    for (int i = 0; i < n; i++)
        sa[i] = i, rnk[i] = s[i];

    for (int k = 1; k < n; k <<= 1) {
        auto cmp = [&](int a, int b) {
            if (rnk[a] != rnk[b])
                return rnk[a] < rnk[b];
            int ra = a + k < n ? rnk[a + k] : -1;
            int rb = b + k < n ? rnk[b + k] : -1;
            return ra < rb;
        };
        sort(sa.begin(), sa.end(), cmp);

        tmp[sa[0]] = 0;
        for (int i = 1; i < n; i++)
            tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
        rnk = tmp;
        if (rnk[sa[n - 1]] == n - 1)
            break;
    }
    return sa;
}

vector<int> buildLCPArray(const string &s, const vector<int> &sa) {
    int n = s.size();
    vector<int> rank(n), lcp(max(0, n - 1));
    for (int i = 0; i < n; i++)
        rank[sa[i]] = i;

    int k = 0;
    for (int i = 0; i < n; i++) {
        if (rank[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = sa[rank[i] + 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k])
            k++;
        lcp[rank[i]] = k;
        if (k > 0)
            k--;
    }
    return lcp;
}

int main() {
    string s = "banana";
    vector<int> sa = buildSuffixArray(s);
    vector<int> lcp = buildLCPArray(s, sa);

    cout << "String: " << s << "\nSuffix Array:\n";
    for (int i = 0; i < (int)sa.size(); i++)
        cout << i << ": " << s.substr(sa[i]) << " (LCP with prev: "
             << (i ? lcp[i - 1] : 0) << ")\n";
    return 0;
}
