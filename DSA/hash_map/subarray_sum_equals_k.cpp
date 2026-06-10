/*
 * ============================================================================
 * TOPIC    : Hash Map — Subarray Sum Equals K
 * FILE     : subarray_sum_equals_k.cpp
 * PROBLEM  : Count subarrays with sum exactly k
 * LEETCODE : 560 — Subarray Sum Equals K
 * APPROACH : Prefix sum + hashmap of prefix frequency
 * COMPLEX  : Time: O(n)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// SUBARRAY SUM = K — Prefix sum + frequency map
// ────────────────────────────────────────────────────────────────────────────
// Subarray [j..i] sum = prefix[i] - prefix[j-1] = k
// Matlab prefix[j-1] = prefix[i] - k pehle kitni baar aaya
// freq map: prefix sum -> kitni baar dekha
// freq[0]=1 — empty prefix se start
// ════════════════════════════════════════════════════════════════════════════

// ── subarraySum: exactly sum k wale subarrays count ────────────────────────
//   1) freq[0]=1, running sum=0, ans=0
//   2) har x: sum += x
//   3) ans += freq[sum - k] (pehle wale prefix jo match karte)
//   4) freq[sum]++ — current prefix store
int subarraySum(vector<int> &nums, int k) {
    unordered_map<int, int> freq;
    freq[0] = 1;
    int sum = 0, ans = 0;
    for (int x : nums) {
        sum += x;
        if (freq.count(sum - k)) ans += freq[sum - k]; // kitne purane prefix
        freq[sum]++;
    }
    return ans;
}

// ── main: {1,1,1}, k=2 -> 2 subarrays ──────────────────────────────────────
int main() {
    vector<int> nums = {1, 1, 1};
    cout << subarraySum(nums, 2) << endl; // 2
    return 0;
}
