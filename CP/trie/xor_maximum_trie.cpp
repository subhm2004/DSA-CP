/*
 * ============================================================================
 * TOPIC    : Trie
 * FILE     : xor_maximum_trie.cpp
 * PROBLEM  : Maximum XOR of any pair in array (or max XOR with given x)
 * APPROACH : Binary trie (0/1 children) — greedily pick opposite bit
 * COMPLEX  : Time: O(n * 32)  |  Space: O(n * 32)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
    TrieNode *child[2];
    TrieNode() { child[0] = child[1] = nullptr; }
};

class XorTrie {
    TrieNode *root;
    const int BITS = 31;

public:
    XorTrie() { root = new TrieNode(); }

    void insert(int num) {
        TrieNode *node = root;
        for (int i = BITS; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (!node->child[bit])
                node->child[bit] = new TrieNode();
            node = node->child[bit];
        }
    }

    int maxXorWith(int num) {
        TrieNode *node = root;
        int result = 0;

        for (int i = BITS; i >= 0; i--) {
            int bit = (num >> i) & 1;
            int want = 1 - bit; // opposite bit maximizes XOR

            if (node->child[want]) {
                result |= (1 << i);
                node = node->child[want];
            } else {
                node = node->child[bit];
            }
        }
        return result;
    }
};

int maxPairXor(vector<int> &arr) {
    XorTrie trie;
    int best = 0;
    for (int x : arr) {
        best = max(best, trie.maxXorWith(x));
        trie.insert(x);
    }
    return best;
}

int main() {
    vector<int> arr = {3, 10, 8, 15, 2};
    cout << "Maximum XOR pair: " << maxPairXor(arr) << endl; // 15 ^ 2 = 13 or 15^10 etc.

    return 0;
}
