/*
 * ============================================================================
 * TOPIC    : Trie — Prefix XOR Count
 * FILE     : trie_prefix_xor_count.cpp
 * PROBLEM  : Count subarrays with XOR = K
 * APPROACH : Prefix XOR + trie counts previous prefixes
 * COMPLEX  : Time: O(n * 32)  |  Space: O(n * 32)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

class XorCountTrie {
    struct Node {
        int child[2];
        int freq;
        Node() { child[0] = child[1] = -1; freq = 0; }
    };
    vector<Node> t;
    const int BITS = 31;

    int newNode() {
        t.emplace_back();
        return (int)t.size() - 1;
    }

public:
    XorCountTrie() { newNode(); }

    void add(int x) {
        int cur = 0;
        t[cur].freq++;
        for (int i = BITS; i >= 0; i--) {
            int b = (x >> i) & 1;
            if (t[cur].child[b] == -1)
                t[cur].child[b] = newNode();
            cur = t[cur].child[b];
            t[cur].freq++;
        }
    }

    int countPrefixXor(int x) {
        int cur = 0, ans = 0;
        for (int i = BITS; i >= 0; i--) {
            int b = (x >> i) & 1;
            int need = 1 - b;
            if (t[cur].child[need] != -1)
                ans += t[t[cur].child[need]].freq;
            if (t[cur].child[b] == -1)
                return ans;
            cur = t[cur].child[b];
        }
        return ans;
    }
};

int subarrayXorK(const vector<int> &a, int k) {
    XorCountTrie trie;
    trie.add(0);
    int pref = 0, count = 0;
    for (int x : a) {
        pref ^= x;
        count += trie.countPrefixXor(pref ^ k);
        trie.add(pref);
    }
    return count;
}

int main() {
    vector<int> a = {4, 2, 2, 6, 4};
    int k = 6;
    cout << "Subarrays with XOR " << k << " = " << subarrayXorK(a, k) << endl;
    return 0;
}
