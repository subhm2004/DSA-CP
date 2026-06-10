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

// ════════════════════════════════════════════════════════════════════════════
// LEETCODE 127 — Word Ladder
// ────────────────────────────────────────────────────────────────────────────
// Problem: beginWord se endWord tak pahuncho — har step me exactly ek letter
//          change karo. Sirf wordList me words valid hain. Minimum steps?
//          Impossible ho to 0 return.
//
// Approach: BFS Shortest Path on Implicit Graph
//   - Har word = node; ek letter change = edge (dict me ho to valid)
//   - BFS se shortest path — pehli baar endWord mile = minimum steps
//   - dict se word erase karo visit ke baad — dobara queue me na aaye
//   - endWord dict me nahi ho to seedha 0
//
// Complexity: Time O(N × L² × 26)  |  Space O(N) for dict + queue
// ════════════════════════════════════════════════════════════════════════════

// ── ladderLength: begin se end tak minimum transformation steps ──
//   1) wordList ko unordered_set me convert — O(1) lookup
//   2) endWord dict me nahi → 0 return (impossible)
//   3) BFS: {word, steps} queue me, beginWord steps=1 se start
//   4) Har word ke har position pe a-z try — dict me ho to push steps+1
//   5) endWord mile → steps return; queue khatam → 0
int ladderLength(string begin, string end, vector<string> &wordList) {
    unordered_set<string> dict(wordList.begin(), wordList.end());
    if (!dict.count(end)) return 0;  // end reachable nahi — no path

    queue<pair<string,int>> q;
    q.push({begin, 1});
    dict.erase(begin);  // visited — dobara process na ho

    while (!q.empty()) {
        auto [word, steps] = q.front(); q.pop();
        if (word == end) return steps;  // shortest path — BFS first hit
        for (int i = 0; i < (int)word.size(); i++) {
            string nxt = word;
            for (char c = 'a'; c <= 'z'; c++) {
                nxt[i] = c;  // i-th position pe ek letter change
                if (dict.count(nxt)) {
                    dict.erase(nxt);  // mark visited before push
                    q.push({nxt, steps + 1});  // ek transformation aur
                }
            }
        }
    }
    return 0;  // end tak koi path nahi
}

int main() {
    vector<string> words = {"hot","dot","dog","lot","log","cog"};
    cout << ladderLength("hit", "cog", words) << endl; // 5
    return 0;
}
