/*
 * ============================================================================
 * TOPIC    : Trie
 * FILE     : trie_basic_insert_search.cpp
 * PROBLEM  : Insert words, search exact word, search prefix
 * APPROACH : 26-child array per node; mark end of word
 * COMPLEX  : Time: O(L) per op  |  Space: O(total chars)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
    TrieNode *child[26];
    bool isEnd;

    TrieNode() {
        isEnd = false;
        for (int i = 0; i < 26; i++)
            child[i] = nullptr;
    }
};

class Trie {
    TrieNode *root;

public:
    Trie() { root = new TrieNode(); }

    void insert(const string &word) {
        TrieNode *node = root;
        for (char ch : word) {
            int idx = ch - 'a';
            if (!node->child[idx])
                node->child[idx] = new TrieNode();
            node = node->child[idx];
        }
        node->isEnd = true;
    }

    bool searchWord(const string &word) {
        TrieNode *node = root;
        for (char ch : word) {
            int idx = ch - 'a';
            if (!node->child[idx])
                return false;
            node = node->child[idx];
        }
        return node->isEnd;
    }

    bool startsWith(const string &prefix) {
        TrieNode *node = root;
        for (char ch : prefix) {
            int idx = ch - 'a';
            if (!node->child[idx])
                return false;
            node = node->child[idx];
        }
        return true;
    }
};

int main() {
    Trie trie;
    trie.insert("apple");
    trie.insert("app");
    trie.insert("bat");

    cout << boolalpha;
    cout << "search apple: " << trie.searchWord("apple") << endl;   // true
    cout << "search app:  " << trie.searchWord("app") << endl;      // true
    cout << "search ap:   " << trie.searchWord("ap") << endl;       // false
    cout << "prefix ap:   " << trie.startsWith("ap") << endl;       // true
    cout << "prefix ba:   " << trie.startsWith("ba") << endl;       // true

    return 0;
}
