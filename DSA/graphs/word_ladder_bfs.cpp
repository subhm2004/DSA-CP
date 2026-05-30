/*
 * ============================================================================
 * TOPIC    : Graphs — Word Ladder (BFS shortest path)
 * FILE     : word_ladder_bfs.cpp
 * PROBLEM  : Min transforms begin → end changing one letter
 * LEETCODE : 127 — Word Ladder
 * APPROACH : BFS on implicit graph; wildcard neighbors via map
 * COMPLEX  : Time: O(N * L^2)  |  Space: O(N)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

int ladderLength(string begin, string end, vector<string> &wordList) {
    unordered_set<string> dict(wordList.begin(), wordList.end());
    if (!dict.count(end)) return 0;

    queue<pair<string,int>> q;
    q.push({begin, 1});
    dict.erase(begin);

    while (!q.empty()) {
        auto [word, steps] = q.front(); q.pop();
        if (word == end) return steps;
        for (int i = 0; i < (int)word.size(); i++) {
            string nxt = word;
            for (char c = 'a'; c <= 'z'; c++) {
                nxt[i] = c;
                if (dict.count(nxt)) {
                    dict.erase(nxt);
                    q.push({nxt, steps + 1});
                }
            }
        }
    }
    return 0;
}

int main() {
    vector<string> words = {"hot","dot","dog","lot","log","cog"};
    cout << ladderLength("hit", "cog", words) << endl; // 5
    return 0;
}
