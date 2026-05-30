/*
 * ============================================================================
 * TOPIC    : Sliding Window
 * FILE     : subarray_sum_equals_k.cpp
 * PROBLEM  : Count subarrays with sum exactly K (handles negatives)
 * APPROACH : Prefix sum + hash map (sliding window works for positive only)
 * COMPLEX  : Time: O(n)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

int subarraySumEqualsK(const vector<int> &a, int k) {
    unordered_map<long long, int> freq;
    freq[0] = 1;
    long long prefix = 0;
    int count = 0;

    for (int x : a) {
        prefix += x;
        if (freq.count(prefix - k))
            count += freq[prefix - k];
        freq[prefix]++;
    }
    return count;
}

int subarraySumPositiveOnly(const vector<int> &a, int k) {
    int l = 0, sum = 0, count = 0;
    for (int r = 0; r < (int)a.size(); r++) {
        sum += a[r];
        while (sum > k && l <= r)
            sum -= a[l++];
        if (sum == k)
            count++;
    }
    return count;
}

int main() {
    vector<int> a = {1, 1, 1};
    cout << "Subarrays with sum 2 (any nums): " << subarraySumEqualsK(a, 2) << endl;

    vector<int> b = {1, 2, 1, 2, 1};
    cout << "Subarrays with sum 3 (positive): " << subarraySumPositiveOnly(b, 3) << endl;
    return 0;
}
