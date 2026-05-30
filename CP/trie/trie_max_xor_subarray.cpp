/*
 * ============================================================================
 * TOPIC    : Trie — Maximum XOR Subarray
 * FILE     : trie_max_xor_subarray.cpp
 * PROBLEM  : Maximum XOR of any contiguous subarray
 * APPROACH : Prefix XOR + trie max query (same as max pair on prefix array)
 * COMPLEX  : Time: O(n * 32)  |  Space: O(n * 32)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
    int child[2];
    TrieNode() { child[0] = child[1] = -1; }
};

class MaxXorTrie {
    vector<TrieNode> t;
    const int BITS = 31;

    int newNode() {
        t.emplace_back();
        return (int)t.size() - 1;
    }

public:
    MaxXorTrie() { newNode(); }

    void insert(int x) {
        int cur = 0;
        for (int i = BITS; i >= 0; i--) {
            int b = (x >> i) & 1;
            if (t[cur].child[b] == -1)
                t[cur].child[b] = newNode();
            cur = t[cur].child[b];
        }
    }

    int maxXor(int x) {
        int cur = 0, ans = 0;
        for (int i = BITS; i >= 0; i--) {
            int b = (x >> i) & 1;
            int want = 1 - b;
            if (t[cur].child[want] != -1) {
                ans |= (1 << i);
                cur = t[cur].child[want];
            } else {
                cur = t[cur].child[b];
            }
        }
        return ans;
    }
};

int maxSubarrayXor(const vector<int> &a) {
    MaxXorTrie trie;
    trie.insert(0);
    int pref = 0, best = 0;
    for (int x : a) {
        pref ^= x;
        best = max(best, trie.maxXor(pref));
        trie.insert(pref);
    }
    return best;
}

int main() {
    vector<int> a = {1, 2, 3, 4};
    cout << "Maximum subarray XOR = " << maxSubarrayXor(a) << endl;
    return 0;
}
