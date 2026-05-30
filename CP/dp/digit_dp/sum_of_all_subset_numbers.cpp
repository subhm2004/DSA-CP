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

long long sumOfSubsetsHelper(const string &num, int i, vector<long long> &dp) {
    if (i < 0)
        return 0;

    if (dp[i] != -1)
        return dp[i];

    int digit = num[i] - '0';
    // Each previous subset doubles; current digit added in all extensions
    return dp[i] = 2 * sumOfSubsetsHelper(num, i - 1, dp) + digit;
}

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
