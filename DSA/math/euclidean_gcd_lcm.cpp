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

long long gcdll(long long a, long long b) {
    a = llabs(a);
    b = llabs(b);
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

long long lcmll(long long a, long long b) {
    if (a == 0 || b == 0) return 0;
    return a / gcdll(a, b) * b;
}

string gcdOfStrings(const string &str1, const string &str2) {
    if (str1 + str2 != str2 + str1) return "";
    int g = (int)gcdll((int)str1.size(), (int)str2.size());
    return str1.substr(0, g);
}

int main() {
    cout << gcdll(48, 18) << endl;  // 6
    cout << lcmll(4, 6) << endl;    // 12
    cout << gcdOfStrings("ABCABC", "ABC") << endl; // ABC
    return 0;
}
