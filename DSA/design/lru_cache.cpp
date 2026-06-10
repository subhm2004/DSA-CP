/*
 * ============================================================================
 * TOPIC    : Design — LRU Cache
 * FILE     : lru_cache.cpp
 * PROBLEM  : O(1) get and put with capacity eviction
 * LEETCODE : 146 — LRU Cache
 * APPROACH : Hash map + doubly linked list (list + iterator)
 * COMPLEX  : Time: O(1) get/put  |  Space: O(capacity)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// LRU CACHE — Least Recently Used eviction, O(1) get/put
// ────────────────────────────────────────────────────────────────────────────
// list: front = most recent, back = least recent
// unordered_map: key -> list iterator (O(1) node dhundhna)
// get/put pe node front pe splice (touch) — recently used mark
// Capacity full + naya key -> back (LRU) hatao, front pe add
// ════════════════════════════════════════════════════════════════════════════

class LRUCache {
    int cap;
    list<pair<int,int>> order; // front = most recent
    unordered_map<int, list<pair<int,int>>::iterator> mp;

    // ── touch: node ko list ke front pe lao (recently used) ───────────────
    //   1) splice: iterator it ko order.begin() pe move
    //   2) list order maintain — front = MRU
    //   3) map iterator same rehta hai — valid after splice
    void touch(list<pair<int,int>>::iterator it) {
        order.splice(order.begin(), order, it);
    }

public:
    // ── LRUCache: capacity set karo, empty cache ────────────────────────────
    //   1) cap = capacity store
    //   2) order aur mp empty — naya cache ready
    LRUCache(int capacity) : cap(capacity) {}

    // ── get: key ki value lo, -1 agar missing ───────────────────────────────
    //   1) mp mein key nahi -> -1 return
    //   2) touch(mp[key]) — recently used mark
    //   3) mp[key]->second return — value
    int get(int key) {
        if (!mp.count(key)) return -1;
        touch(mp[key]);
        return mp[key]->second;
    }

    // ── put: key-value insert/update, LRU evict if full ─────────────────────
    //   1) key exist -> value update, touch, return
    //   2) size == cap -> back (LRU) erase from map + pop_back
    //   3) push_front {key, value}, mp[key] = begin()
    //   4) O(1) insert/update complete
    void put(int key, int value) {
        if (mp.count(key)) {
            mp[key]->second = value;
            touch(mp[key]);
            return;
        }
        if ((int)order.size() == cap) {
            mp.erase(order.back().first);
            order.pop_back();
        }
        order.push_front({key, value});
        mp[key] = order.begin();
    }
};

int main() {
    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    cout << cache.get(1) << endl; // 1
    cache.put(3, 3);
    cout << cache.get(2) << endl; // -1
    return 0;
}
