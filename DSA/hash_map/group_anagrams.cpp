/*
 * ============================================================================
 * TOPIC    : Hash Map — Group Anagrams
 * FILE     : group_anagrams.cpp
 * PROBLEM  : Group strings that are anagrams
 * LEETCODE : 49 — Group Anagrams
 * APPROACH : Sorted string or freq signature as hash key
 * COMPLEX  : Time: O(n*k log k)  |  Space: O(n*k)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// GROUP ANAGRAMS — Sorted string ko hash key banao
// ────────────────────────────────────────────────────────────────────────────
// Anagrams sort karne pe same string bante hain
// mp[key] = saari original strings jinki sorted key same hai
// "eat","tea","ate" -> key "aet"
// Alternative: 26-char frequency signature bhi key ban sakti hai
// ════════════════════════════════════════════════════════════════════════════

// ── groupAnagrams: anagram groups return karo ───────────────────────────────
//   1) har string s ki sorted copy key banao
//   2) mp[key].push_back(s) — same key wale ek group
//   3) mp ke values ko ans vector me daalo
//   4) grouped vectors return
vector<vector<string>> groupAnagrams(vector<string> &strs) {
    unordered_map<string, vector<string>> mp;
    for (string &s : strs) {
        string key = s;
        sort(key.begin(), key.end()); // anagram signature
        mp[key].push_back(s);
    }
    vector<vector<string>> ans;
    for (auto &[k, v] : mp) ans.push_back(move(v));
    return ans;
}

// ── main: 6 strings -> 3 groups print ───────────────────────────────────────
int main() {
    vector<string> strs = {"eat","tea","tan","ate","nat","bat"};
    for (auto &g : groupAnagrams(strs)) {
        for (string &s : g) cout << s << " ";
        cout << "| ";
    }
    cout << endl;
    return 0;
}
