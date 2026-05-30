/*
 * ============================================================================
 * TOPIC    : String Algorithms — Aho-Corasick
 * FILE     : aho_corasick.cpp
 * PROBLEM  : Match many patterns in one text stream
 * APPROACH : Trie + failure links (KMP-style fallback)
 * COMPLEX  : Build O(sum|pattern|), scan O(|text| + matches)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

struct AhoCorasick {
    static const int ALPH = 26;
    struct Node {
        int next[ALPH];
        int link = 0;
        int out = 0;
        vector<int> patIds;
        Node() { fill(next, next + ALPH, -1); }
    };
    vector<Node> tr;
    vector<string> patterns;

    AhoCorasick() { tr.emplace_back(); }

    void insert(const string &s, int id) {
        int v = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (tr[v].next[c] == -1) {
                tr[v].next[c] = (int)tr.size();
                tr.emplace_back();
            }
            v = tr[v].next[c];
        }
        tr[v].patIds.push_back(id);
    }

    void build() {
        queue<int> q;
        for (int c = 0; c < ALPH; c++) {
            if (tr[0].next[c] != -1) {
                tr[tr[0].next[c]].link = 0;
                q.push(tr[0].next[c]);
            } else {
                tr[0].next[c] = 0;
            }
        }
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int c = 0; c < ALPH; c++) {
                if (tr[v].next[c] != -1) {
                    int u = tr[v].next[c];
                    tr[u].link = tr[tr[v].link].next[c];
                    auto &out = tr[tr[u].link].patIds;
                    tr[u].patIds.insert(tr[u].patIds.end(), out.begin(), out.end());
                    q.push(u);
                } else {
                    tr[v].next[c] = tr[tr[v].link].next[c];
                }
            }
        }
    }

    vector<pair<int, int>> search(const string &text) {
        vector<pair<int, int>> hits; // (end_index, pattern_id)
        int v = 0;
        for (int i = 0; i < (int)text.size(); i++) {
            v = tr[v].next[text[i] - 'a'];
            for (int id : tr[v].patIds)
                hits.push_back({i, id});
        }
        return hits;
    }
};

int main() {
    AhoCorasick ac;
    vector<string> pats = {"he", "she", "his", "hers"};
    for (int i = 0; i < (int)pats.size(); i++)
        ac.insert(pats[i], i);
    ac.build();

    string text = "ushers";
    auto hits = ac.search(text);
    for (auto [pos, id] : hits)
        cout << "pattern " << pats[id] << " ends at " << pos << endl;
    return 0;
}
