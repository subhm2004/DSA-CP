/*
 * ============================================================================
 * TOPIC    : Hash Map — Top K Frequent Elements
 * FILE     : top_k_frequent_elements.cpp
 * PROBLEM  : k most frequent numbers
 * LEETCODE : 347 — Top K Frequent Elements
 * APPROACH : Frequency map + min-heap of size k
 * COMPLEX  : Time: O(n log k)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

vector<int> topKFrequent(vector<int> &nums, int k) {
    unordered_map<int, int> freq;
    for (int x : nums) freq[x]++;

    using P = pair<int,int>;
    priority_queue<P, vector<P>, greater<P>> pq;
    for (auto &[val, f] : freq) {
        pq.push({f, val});
        if ((int)pq.size() > k) pq.pop();
    }
    vector<int> ans;
    while (!pq.empty()) {
        ans.push_back(pq.top().second);
        pq.pop();
    }
    return ans;
}

int main() {
    vector<int> nums = {1,1,1,2,2,3};
    for (int x : topKFrequent(nums, 2)) cout << x << " ";
    cout << endl; // 1 2
    return 0;
}
