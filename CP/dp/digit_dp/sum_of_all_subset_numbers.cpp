/*
 * ============================================================================
 * TOPIC    : Digit DP
 * FILE     : sum_of_all_subset_numbers.cpp
 * PROBLEM  : Sum of all numbers formed by subsets of digits of a given number
 * APPROACH : Digit DP — each position contributes to all subset choices
 * COMPLEX  : Time: O(n)  |  Space: O(n)
 * ============================================================================
 *
 * Recurrence at digit i:
 *   total = 2 * f(i-1) + digit * 10^(remaining positions) * 2^(i-1)
 * Simplified memo on index only (classic Codeforces / interview problem).
 */

#include <iostream>
#include <vector>

using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// SUM OF ALL SUBSET NUMBERS — Digit DP (index-based memo)
// ────────────────────────────────────────────────────────────────────────────
// State: i (right se left tak index) — har position pe subset choice double hoti hai
// Memo: dp[i] — digits [0..i] se banne wale subset numbers ka total sum
// Recurrence: 2 * f(i-1) + current_digit (har purana subset dobara + naya digit)
// Base case: i < 0 -> 0 (koi digit nahi)
// ════════════════════════════════════════════════════════════════════════════

// ── sumOfSubsetsHelper: right-to-left DP — subset sum calculate karo ────────
//   1) i < 0 -> base case, kuch nahi bana, 0 return
//   2) dp[i] cached ho to wahi return
//   3) current digit = num[i]
//   4) purane subsets double (include/exclude) + current digit har extension me add
//   5) result dp[i] me store karke return
long long sumOfSubsetsHelper(const string &num, int i, vector<long long> &dp) {
    if (i < 0)
        return 0;

    if (dp[i] != -1)
        return dp[i];

    int digit = num[i] - '0';
    // Har previous subset do baar count hota hai (digit include ya skip)
    return dp[i] = 2 * sumOfSubsetsHelper(num, i - 1, dp) + digit;
}

// ── sumOfAllSubsetNumbers: string number se total subset sum nikalo ─────────
//   1) n = length, dp array size n with -1 (unvisited)
//   2) last index (n-1) se helper call — poora number cover
//   3) final sum return
long long sumOfAllSubsetNumbers(const string &num) {
    int n = num.length();
    vector<long long> dp(n, -1);
    return sumOfSubsetsHelper(num, n - 1, dp);
}

int main() {
    string num;
    cout << "Enter a number: ";
    cin >> num;

    cout << "Sum of all subset-formed numbers: " << sumOfAllSubsetNumbers(num) << endl;
    return 0;
}
