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

// ════════════════════════════════════════════════════════════════════════════
// CLIMBING STAIRS — n steps top tak 1 ya 2 step leke kitne tareeke?
// ────────────────────────────────────────────────────────────────────────────
// Step i pe pahunchne ke tareeke = (i-1 se 1 step) + (i-2 se 2 step).
// Classic Fibonacci: ways(1)=1, ways(2)=2, ways(i)=ways(i-1)+ways(i-2).
// Do variables se O(1) space — sirf last two values yaad rakho.
// COMPLEX: Time O(n)  |  Space O(1)
// ════════════════════════════════════════════════════════════════════════════

// ── climbStairs: n steps tak pahunchne ke total ways ───────────────────────
//   1) n<=2 base case — seedha n return (1 step=1 way, 2 steps=2 ways)
//   2) a=ways(1), b=ways(2) initialize karo
//   3) i=3 se n tak: c = a+b, slide window (a=b, b=c)
//   4) Har step pe purane do states se naya ways count
//   5) b = ways(n) final answer
int climbStairs(int n) {
    if (n <= 2) return n;                                  // base: 1 ya 2 steps
    int a = 1, b = 2;
    for (int i = 3; i <= n; i++) {
        int c = a + b;                                     // Fibonacci recurrence
        a = b;
        b = c;
    }
    return b;
}

// ── main: n=5 stairs pe ways count test ────────────────────────────────────
//   1) climbStairs(5) call — expected 8 ways
//   2) Answer print karo
int main() {
    cout << climbStairs(5) << endl; // 8
    return 0;
}
