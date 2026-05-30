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

vector<vector<string>> groupAnagrams(vector<string> &strs) {
    unordered_map<string, vector<string>> mp;
    for (string &s : strs) {
        string key = s;
        sort(key.begin(), key.end());
        mp[key].push_back(s);
    }
    vector<vector<string>> ans;
    for (auto &[k, v] : mp) ans.push_back(move(v));
    return ans;
}

int main() {
    vector<string> strs = {"eat","tea","tan","ate","nat","bat"};
    for (auto &g : groupAnagrams(strs)) {
        for (string &s : g) cout << s << " ";
        cout << "| ";
    }
    cout << endl;
    return 0;
}
