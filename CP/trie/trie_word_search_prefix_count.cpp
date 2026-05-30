/*
 * ============================================================================
 * TOPIC    : Trie
 * FILE     : trie_word_search_prefix_count.cpp
 * PROBLEM  : Count words sharing a prefix (autocomplete use case)
 * APPROACH : Store count at each node; decrement on delete optional
 * COMPLEX  : Time: O(L)  |  Space: O(total chars)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
    TrieNode *child[26];
    int prefixCount; // how many words pass through this node

    TrieNode() : prefixCount(0) {
        for (int i = 0; i < 26; i++)
            child[i] = nullptr;
    }
};

class PrefixTrie {
    TrieNode *root;

public:
    PrefixTrie() { root = new TrieNode(); }

    void insert(const string &word) {
        TrieNode *node = root;
        for (char ch : word) {
            int idx = ch - 'a';
            if (!node->child[idx])
                node->child[idx] = new TrieNode();
            node = node->child[idx];
            node->prefixCount++;
        }
    }

    int countPrefix(const string &prefix) {
        TrieNode *node = root;
        for (char ch : prefix) {
            int idx = ch - 'a';
            if (!node->child[idx])
                return 0;
            node = node->child[idx];
        }
        return node->prefixCount;
    }
};

int main() {
    PrefixTrie trie;
    trie.insert("apple");
    trie.insert("app");
    trie.insert("application");
    trie.insert("bat");

    cout << "Words with prefix 'app': " << trie.countPrefix("app") << endl; // 3
    cout << "Words with prefix 'ba':  " << trie.countPrefix("ba") << endl;   // 1
    cout << "Words with prefix 'xyz':" << trie.countPrefix("xyz") << endl;  // 0

    return 0;
}
