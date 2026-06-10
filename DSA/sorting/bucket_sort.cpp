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

// ════════════════════════════════════════════════════════════════════════════
// BUCKET SORT — Uniform distribution wale floats ke liye
// ────────────────────────────────────────────────────────────────────────────
// [0,1) range ko n buckets me divide — x*n se bucket index
// Har bucket individually sort — phir concatenate
// Average O(n) jab data uniformly distributed ho
// ════════════════════════════════════════════════════════════════════════════

// ── bucketSort: buckets me distribute, sort, merge ──────────────────────────
//   1) n buckets banao
//   2) x*n se bucket choose, push
//   3) har bucket sort, phir ek array me jodo
void bucketSort(vector<float> &a) {
    int n = a.size();
    if (n <= 0)
        return;

    vector<vector<float>> buckets(n);
    for (float x : a) {
        int idx = min(n - 1, (int)(x * n));  // bucket index
        buckets[idx].push_back(x);
    }

    for (auto &bucket : buckets)
        sort(bucket.begin(), bucket.end());  // har bucket sort

    int i = 0;
    for (auto &bucket : buckets)
        for (float x : bucket)
            a[i++] = x;  // concatenate
}

// ── main: bucket sort demo ──────────────────────────────────────────────────
int main() {
    vector<float> a = {0.897f, 0.565f, 0.656f, 0.1234f, 0.665f, 0.3434f};
    bucketSort(a);
    for (float x : a)
        cout << x << " ";
    cout << endl;
    return 0;
}
