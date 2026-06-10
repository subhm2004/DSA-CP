/*
 * ============================================================================
 * TOPIC    : Math — Euclidean GCD & LCM
 * FILE     : euclidean_gcd_lcm.cpp
 * PROBLEM  : GCD / LCM of two numbers (interview utility)
 * LEETCODE : 1071 — Greatest Common Divisor of Strings (uses gcd on lengths)
 * APPROACH : Euclidean algorithm: gcd(a,b) = gcd(b, a % b)
 * COMPLEX  : Time: O(log min(a,b))  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// EUCLIDEAN GCD & LCM — number theory fundamentals
// ────────────────────────────────────────────────────────────────────────────
// Funda: gcd — modulo + swap loop; lcm = a/gcd * b
// gcdOfStrings — dono strings ka common repeat pattern
// COMPLEX: gcd O(log min(a,b))  |  Space O(1)
// ════════════════════════════════════════════════════════════════════════════

// ── gcdll: Euclidean algorithm se GCD ────────────────────────────────────────
//   1) a, b ko absolute value lo
//   2) while b != 0 — a %= b, swap(a,b)
//   3) b zero ho gaya — a hi GCD hai
long long gcdll(long long a, long long b) {
    a = llabs(a);
    b = llabs(b);
    while (b) {
        a %= b; // remainder le lo
        swap(a, b); // chhota number aage
    }
    return a;
}

// ── lcmll: GCD se LCM nikalo ───────────────────────────────────────────────
//   1) koi bhi zero? return 0
//   2) formula: a / gcd(a,b) * b — overflow kam karne ke liye divide pehle
long long lcmll(long long a, long long b) {
    if (a == 0 || b == 0) return 0;
    return a / gcdll(a, b) * b;
}

// ── gcdOfStrings: repeat pattern check + length GCD ────────────────────────
//   1) str1+str2 == str2+str1? nahi to "" — common base nahi
//   2) dono lengths ka gcd nikalo
//   3) str1.substr(0, g) return — yahi answer
string gcdOfStrings(const string &str1, const string &str2) {
    if (str1 + str2 != str2 + str1) return ""; // repeat nahi ho sakta
    int g = (int)gcdll((int)str1.size(), (int)str2.size());
    return str1.substr(0, g);
}

// ── main: gcd, lcm, gcdOfStrings demo ──────────────────────────────────────
//   1) gcd(48,18)=6, lcm(4,6)=12 print
//   2) gcdOfStrings("ABCABC","ABC") = "ABC"
int main() {
    cout << gcdll(48, 18) << endl;  // 6
    cout << lcmll(4, 6) << endl;    // 12
    cout << gcdOfStrings("ABCABC", "ABC") << endl; // ABC
    return 0;
}
