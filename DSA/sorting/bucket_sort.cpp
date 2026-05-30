/*
 * ============================================================================
 * TOPIC    : Sorting
 * FILE     : bucket_sort.cpp
 * PROBLEM  : Bucket Sort (uniformly distributed floats in [0,1))
 * APPROACH : Distribute into buckets, sort each, concatenate
 * COMPLEX  : Time: O(n) avg  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

void bucketSort(vector<float> &a) {
    int n = a.size();
    if (n <= 0)
        return;

    vector<vector<float>> buckets(n);
    for (float x : a) {
        int idx = min(n - 1, (int)(x * n));
        buckets[idx].push_back(x);
    }

    for (auto &bucket : buckets)
        sort(bucket.begin(), bucket.end());

    int i = 0;
    for (auto &bucket : buckets)
        for (float x : bucket)
            a[i++] = x;
}

int main() {
    vector<float> a = {0.897f, 0.565f, 0.656f, 0.1234f, 0.665f, 0.3434f};
    bucketSort(a);
    for (float x : a)
        cout << x << " ";
    cout << endl;
    return 0;
}
