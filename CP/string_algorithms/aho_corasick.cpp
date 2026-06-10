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

// ════════════════════════════════════════════════════════════════════════════
// AHO-CORASICK — Multiple pattern matching ek text me
// ────────────────────────────────────────────────────────────────────────────
// Step 1: Saare patterns ka trie banao (insert)
// Step 2: Har node pe failure link (KMP jaisa fallback) — build()
// Step 3: Text scan karo, match pe patIds check karo — search()
//
// link[v] = jis node pe jana hai jab current char match fail ho
// ════════════════════════════════════════════════════════════════════════════

struct AhoCorasick {
    static const int ALPH = 26;
    struct Node {
        int next[ALPH];
        int link = 0;
        int out = 0;
        vector<int> patIds;  // is node pe khatam hone wale pattern ids
        Node() { fill(next, next + ALPH, -1); }
    };
    vector<Node> tr;
    vector<string> patterns;

    // Constructor: root node (index 0) ke saath empty trie shuru karo.
    // tr[0] sab patterns ka starting point hai — yahan se har pattern insert hoga.
    // Ek hi root se multiple patterns share kar sakte hain (prefix overlap).
    AhoCorasick() { tr.emplace_back(); }

    // insert — pattern 's' ko trie me character-by-character daalo.
    // Step 1: Root se shuru karke har char ke liye next[] edge dekho/banao.
    // Step 2: Agar edge nahi hai to naya node create karo aur link karo.
    // Step 3: Pattern ke end node pe patIds me is pattern ka id store karo.
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

    // build — failure links (KMP jaisa fallback) BFS se banao.
    // Step 1: Root ke depth-1 children ka link = 0; missing edges bhi 0 pe point karo.
    // Step 2: BFS me har node v ke liye: u = v.next[c] ka link = link[v].next[c].
    // Step 3: u pe link node ke patIds bhi merge karo (suffix pattern bhi match ho).
    // Step 4: Missing edge pe link[v].next[c] se shortcut (goto) set karo.
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

    // search — text ek baar scan karke saare pattern matches nikalo.
    // Step 1: v = 0 (root) se shuru; har char pe v = tr[v].next[char] (goto).
    // Step 2: Fail links pe manually jump nahi — build() ne edges pe shortcut daal diya.
    // Step 3: Har step pe tr[v].patIds check karo — end index i ke saath record karo.
    // Returns: (end_index, pattern_id) pairs
    vector<pair<int, int>> search(const string &text) {
        vector<pair<int, int>> hits;
        int v = 0;
        for (int i = 0; i < (int)text.size(); i++) {
            v = tr[v].next[text[i] - 'a'];
            for (int id : tr[v].patIds)
                hits.push_back({i, id});
        }
        return hits;
    }
};

// main — demo: patterns insert → build failure links → text pe search.
// Har hit me pattern name aur end position print hoti hai.
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
