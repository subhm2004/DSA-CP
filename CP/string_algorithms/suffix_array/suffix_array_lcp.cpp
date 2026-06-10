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

// buildSuffixArray — doubling + sort se suffix array O(n log^2 n) me banao.
// Step 1: sa[i]=i, rnk[i]=s[i] — shuru me sirf pehla char se rank.
// Step 2: k=1,2,4,... double karte hue 2*k length ke suffix pairs compare sort se.
// Step 3: cmp: pehle rnk[a] vs rnk[b], tie ho to rnk[a+k] vs rnk[b+k] (second half).
// Step 4: Naye ranks assign; sab unique (rnk[sa[n-1]]==n-1) ho to early break.
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

// buildLCPArray — Kasai algorithm: adjacent SA suffixes ka common prefix length.
// Step 1: rank[sa[i]] = i — har original index ka SA me position.
// Step 2: i = 0..n-1 scan; rank[i]==n-1 ho to skip (last suffix ka koi next nahi).
// Step 3: j = SA me agla suffix; k se match extend jab tak s[i+k]==s[j+k].
// Step 4: lcp[rank[i]]=k; k>0 ho to k-- (next i ka LCP kam se shuru — amortized O(n)).
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

// main — "banana" pe SA + LCP build karke har suffix aur uska LCP print karo.
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
