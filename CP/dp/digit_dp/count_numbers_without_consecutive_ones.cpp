/*
 * ============================================================================
 * TOPIC    : Digit DP
 * FILE     : count_numbers_without_consecutive_ones.cpp
 * PROBLEM  : Count numbers in [0, N] with no two consecutive 1 bits in binary
 * APPROACH : Digit DP on binary representation (like Fibonacci / LeetCode 600)
 * COMPLEX  : Time: O(log N)  |  Space: O(log N)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

string binary;
long long memo[65][2][2]; // pos, tight, prevOne

long long solve(int pos, int tight, int prevOne) {
    if (pos == (int)binary.size())
        return 1;

    if (memo[pos][tight][prevOne] != -1)
        return memo[pos][tight][prevOne];

    int limit = tight ? binary[pos] - '0' : 1;
    long long ans = 0;

    for (int bit = 0; bit <= limit; bit++) {
        if (prevOne && bit == 1)
            continue; // consecutive ones not allowed

        int nextTight = tight && (bit == limit);
        ans += solve(pos + 1, nextTight, bit);
    }

    return memo[pos][tight][prevOne] = ans;
}

long long countWithoutConsecutiveOnes(long long n) {
    binary = bitset<64>(n).to_string();
    binary = binary.substr(binary.find('1')); // strip leading zeros
    if (binary.empty())
        binary = "0";

    memset(memo, -1, sizeof(memo));
    return solve(0, 1, 0);
}

int main() {
    long long n;
    cout << "Enter N: ";
    cin >> n;

    cout << "Count in [0, " << n << "] without consecutive 1s in binary: "
         << countWithoutConsecutiveOnes(n) << endl;

    return 0;
}
