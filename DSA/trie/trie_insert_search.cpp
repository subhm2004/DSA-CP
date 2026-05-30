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

struct TrieNode {
    TrieNode *child[26]{};
    bool isEnd = false;
};

class Trie {
    TrieNode *root;

public:
    Trie() { root = new TrieNode(); }

    void insert(string word) {
        TrieNode *cur = root;
        for (char c : word) {
            int i = c - 'a';
            if (!cur->child[i]) cur->child[i] = new TrieNode();
            cur = cur->child[i];
        }
        cur->isEnd = true;
    }

    bool search(string word) {
        TrieNode *node = find(word);
        return node && node->isEnd;
    }

    bool startsWith(string prefix) {
        return find(prefix) != nullptr;
    }

private:
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
