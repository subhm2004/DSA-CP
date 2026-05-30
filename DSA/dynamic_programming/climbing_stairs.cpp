/*
 * ============================================================================
 * TOPIC    : Dynamic Programming — Climbing Stairs
 * FILE     : climbing_stairs.cpp
 * PROBLEM  : Ways to reach top taking 1 or 2 steps
 * LEETCODE : 70 — Climbing Stairs
 * APPROACH : dp[i] = dp[i-1] + dp[i-2] (Fibonacci)
 * COMPLEX  : Time: O(n)  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

int climbStairs(int n) {
    if (n <= 2) return n;
    int a = 1, b = 2;
    for (int i = 3; i <= n; i++) {
        int c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    cout << climbStairs(5) << endl; // 8
    return 0;
}
