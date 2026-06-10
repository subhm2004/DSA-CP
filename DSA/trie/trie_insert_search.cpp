/*
 * ============================================================================
 * TOPIC    : Trie — Insert & Search
 * FILE     : trie_insert_search.cpp
 * PROBLEM  : Implement trie with insert, search, startsWith
 * LEETCODE : 208 — Implement Trie (Prefix Tree)
 * APPROACH : Array of 26 children per node + isEnd flag
 * COMPLEX  : Time: O(L) per op  |  Space: O(total chars)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// TRIE (PREFIX TREE) — words insert, search, prefix check
// ────────────────────────────────────────────────────────────────────────────
// Har node: 26 children (a-z) + isEnd flag
// Insert: har char ke liye child banao/traverse, last pe isEnd=true
// Search: path follow + isEnd check (poora word hona chahiye)
// startsWith: sirf path exist karta hai ya nahi
// find(): shared helper — prefix/word tak node return
// ════════════════════════════════════════════════════════════════════════════

struct TrieNode {
    TrieNode *child[26]{};
    bool isEnd = false;
};

class Trie {
    TrieNode *root;

public:
    // ── Trie: empty root node create karo ───────────────────────────────────
    //   1) root = new TrieNode() — sab children null, isEnd false
    Trie() { root = new TrieNode(); }

    // ── insert: word trie mein add karo ─────────────────────────────────────
    //   1) cur = root se start
    //   2) har char c: index = c-'a'
    //   3) child[i] nahi hai to naya TrieNode banao
    //   4) cur = child[i] pe aage badho
    //   5) last char ke baad isEnd = true
    void insert(string word) {
        TrieNode *cur = root;
        for (char c : word) {
            int i = c - 'a';
            if (!cur->child[i]) cur->child[i] = new TrieNode();
            cur = cur->child[i];
        }
        cur->isEnd = true;
    }

    // ── search: poora word trie mein hai? ───────────────────────────────────
    //   1) find(word) se node lo
    //   2) node exist + isEnd true -> word mila
    //   3) warna false (sirf prefix hai ya nahi hai)
    bool search(string word) {
        TrieNode *node = find(word);
        return node && node->isEnd;
    }

    // ── startsWith: prefix exist karta hai? ─────────────────────────────────
    //   1) find(prefix) call karo
    //   2) nullptr nahi -> prefix valid
    //   3) isEnd check nahi — sirf path chahiye
    bool startsWith(string prefix) {
        return find(prefix) != nullptr;
    }

private:
    // ── find: string s tak trie mein traverse karo ──────────────────────────
    //   1) cur = root
    //   2) har char: child[i] missing -> nullptr
    //   3) cur = child[i] pe move
    //   4) end tak pahunche -> cur return (prefix/word node)
    TrieNode *find(const string &s) {
        TrieNode *cur = root;
        for (char c : s) {
            int i = c - 'a';
            if (!cur->child[i]) return nullptr;
            cur = cur->child[i];
        }
        return cur;
    }
};

int main() {
    Trie t;
    t.insert("apple");
    cout << t.search("apple") << " " << t.search("app") << " " << t.startsWith("app") << endl;
    return 0;
}
