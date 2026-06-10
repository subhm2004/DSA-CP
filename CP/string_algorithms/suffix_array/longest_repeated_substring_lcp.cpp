/*
 * ============================================================================
 * TOPIC    : Suffix Array + LCP
 * FILE     : longest_repeated_substring_lcp.cpp
 * PROBLEM  : Longest repeated substring using LCP array
 * APPROACH : max(LCP[i]) gives length; reconstruct from SA
 * COMPLEX  : Time: O(n log^2 n)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// buildSuffixArray — doubling + sort se suffix array O(n log^2 n) me banao.
// Step 1: sa[i]=i, rnk[i]=s[i] — shuru me sirf pehla char se rank.
// Step 2: k=1,2,4,... double karte hue 2*k length ke suffix pairs compare sort se.
// Step 3: cmp: pehle rnk[a] vs rnk[b], tie ho to rnk[a+k] vs rnk[b+k].
// Step 4: Naye ranks assign; sab unique ho to early break.
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
// Step 1: rank array banao — original index se SA position map.
// Step 2: Har i ke liye SA me agla suffix j se char-by-char match extend (k pointer).
// Step 3: lcp[rank[i]] = k store; k>0 pe k-- (next comparison thoda aage se).
// Step 4: Poora scan O(n) — repeated substring length LCP me hidden hoti hai.
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

// longestRepeatedSubstring — LCP array ka maximum = sabse lamba repeated substring.
// Step 1: SA aur LCP build karo — sorted suffixes ke beech common prefix.
// Step 2: LCP[i] scan karke max length aur uska SA index (bestIdx) track karo.
// Step 3: s.substr(bestIdx, bestLen) return — wahi substring do jagah repeat hoti hai.
string longestRepeatedSubstring(string s) {
    if (s.empty())
        return "";
    vector<int> sa = buildSuffixArray(s);
    vector<int> lcp = buildLCPArray(s, sa);

    int bestLen = 0, bestIdx = 0;
    for (int i = 0; i < (int)lcp.size(); i++) {
        if (lcp[i] > bestLen) {
            bestLen = lcp[i];
            bestIdx = sa[i];
        }
    }
    return s.substr(bestIdx, bestLen);
}

// main — sample string pe longest repeated substring find karke print karo.
int main() {
    string s = "abracadabra";
    string ans = longestRepeatedSubstring(s);
    cout << "Longest repeated substring in \"" << s << "\": \"" << ans << "\"\n";
    return 0;
}
