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

class LRUCache {
    int cap;
    list<pair<int,int>> order; // front = most recent
    unordered_map<int, list<pair<int,int>>::iterator> mp;

    void touch(list<pair<int,int>>::iterator it) {
        order.splice(order.begin(), order, it);
    }

public:
    LRUCache(int capacity) : cap(capacity) {}

    int get(int key) {
        if (!mp.count(key)) return -1;
        touch(mp[key]);
        return mp[key]->second;
    }

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
