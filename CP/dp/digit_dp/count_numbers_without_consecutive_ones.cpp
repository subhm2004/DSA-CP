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

// ════════════════════════════════════════════════════════════════════════════
// NO CONSECUTIVE ONES (BINARY) — Digit DP on bits
// ────────────────────────────────────────────────────────────────────────────
// State: pos (bit index), tight (N ke binary se bound?), prevOne (pichla bit 1 tha?)
// Memo: memo[pos][tight][prevOne]
// Binary digits: limit = tight ? binary[pos] : 1 (sirf 0 ya 1)
// Constraint: prevOne && bit==1 -> skip (consecutive ones banned)
// Base case: pos==len -> 1 (har valid binary prefix count hota hai)
// ════════════════════════════════════════════════════════════════════════════

string binary;
long long memo[65][2][2]; // pos, tight, prevOne

// ── solve: binary representation me consecutive 1s ke bina count ──────────
//   1) pos == len -> valid number ban gaya, 1 return
//   2) memo check
//   3) limit = tight ? binary[pos] : 1 (binary digit DP)
//   4) prevOne && bit==1 -> continue (do 1s lagatar allowed nahi)
//   5) nextTight = tight && bit==limit, prevOne = bit for next step
long long solve(int pos, int tight, int prevOne) {
    if (pos == (int)binary.size())
        return 1;

    if (memo[pos][tight][prevOne] != -1)
        return memo[pos][tight][prevOne];

    int limit = tight ? binary[pos] - '0' : 1; // binary: max digit 1 jab tight=0
    long long ans = 0;

    for (int bit = 0; bit <= limit; bit++) {
        if (prevOne && bit == 1)
            continue; // consecutive ones not allowed — pichla 1 tha to ab 1 mat lagao

        int nextTight = tight && (bit == limit); // tight transition on binary bound
        ans += solve(pos + 1, nextTight, bit);
    }

    return memo[pos][tight][prevOne] = ans;
}

// ── countWithoutConsecutiveOnes: N ka binary banao aur DP chalao ────────────
//   1) N ko 64-bit binary string me convert
//   2) leading zeros hatao (MSB se pehli 1 tak)
//   3) N=0 case: binary = "0"
//   4) memo reset, solve(0, 1, 0) — prevOne=0 se start
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
