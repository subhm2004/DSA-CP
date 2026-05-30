/*
 * ============================================================================
 * TOPIC    : Bit Manipulation — XOR Tricks & Bit Ops
 * FILE     : xor_tricks_and_bit_ops.cpp
 * PROBLEM  : Common bit tricks used in CP
 * APPROACH : __builtin_popcount, ctz, single-bit isolation
 * COMPLEX  : Time: O(1) per operation
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    int x = 84; // 1010100

    cout << "x = " << x << " (binary " << bitset<8>(x) << ")\n\n";

    // popcount — number of set bits
    cout << "__builtin_popcount(x) = " << __builtin_popcount(x) << endl;

    // ctz — count trailing zeros (index of lowest set bit)
    cout << "__builtin_ctz(x) = " << __builtin_ctz(x) << endl;

    // lowest set bit
    int lowest = x & (-x);
    cout << "lowest set bit (x & -x) = " << lowest << endl;

    // clear lowest set bit
    cout << "x with lowest bit cleared = " << (x & (x - 1)) << endl;

    // check if power of 2
    auto isPowerOfTwo = [](int n) { return n > 0 && (n & (n - 1)) == 0; };
    cout << "is 8 power of 2? " << isPowerOfTwo(8) << endl;

    // toggle i-th bit
    int i = 2;
    cout << "toggle bit " << i << ": " << (x ^ (1 << i)) << endl;

    // XOR prefix property: a^a=0, a^0=a
    vector<int> arr = {1, 2, 3, 2, 1};
    int xr = 0;
    for (int v : arr)
        xr ^= v;
    cout << "\nXOR of all (find odd occurrence): " << xr << endl;

    return 0;
}
