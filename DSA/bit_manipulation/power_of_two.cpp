/*
 * ============================================================================
 * TOPIC    : Bit Manipulation — Power of Two
 * FILE     : power_of_two.cpp
 * PROBLEM  : Check if n is a power of 2
 * LEETCODE : 231 — Power of Two
 * APPROACH : n > 0 && (n & (n-1)) == 0
 * COMPLEX  : Time: O(1)  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

bool isPowerOfTwo(int n) {
    return n > 0 && (n & (n - 1)) == 0;
}

int main() {
    cout << isPowerOfTwo(16) << " " << isPowerOfTwo(18) << endl; // 1 0
    return 0;
}
