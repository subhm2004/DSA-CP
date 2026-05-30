#include <bits/stdc++.h>
using namespace std;
#define ll long long int

// ==========================
// 1D Fenwick Tree - XOR
// ==========================
class BIT1D_XOR
{
public:
    int n;
    vector<ll> bit;

    BIT1D_XOR(int n)
    {
        this->n = n;
        bit.assign(n + 1, 0);
    }

    // Point XOR update at index i
    void update(int i, ll val)
    {
        for (; i <= n; i += (i & -i))
            bit[i] ^= val;
    }

    // Prefix XOR: XOR of arr[1..i]
    ll prefixXOR(int i)
    {
        ll result = 0;
        for (; i > 0; i -= (i & -i))
            result ^= bit[i];
        return result;
    }

    // Range XOR: XOR of arr[l..r]
    ll rangeXOR(int l, int r)
    {
        if (l == 1)
            return prefixXOR(r);
        return prefixXOR(r) ^ prefixXOR(l - 1);
    }

    // Point set: arr[i] = newVal
    void pointSet(int i, ll newVal)
    {
        ll oldVal = rangeXOR(i, i); // current value
        update(i, oldVal ^ newVal); // old^new XOR karo
    }
};

// ==========================
// 2D Fenwick Tree - XOR
// ==========================
class BIT2D_XOR
{
public:
    int n, m;
    vector<vector<ll>> bit;

    BIT2D_XOR(int n, int m)
    {
        this->n = n;
        this->m = m;
        bit.assign(n + 1, vector<ll>(m + 1, 0));
    }

    // Point XOR update at (x, y)
    void update(int x, int y, ll val)
    {
        for (int i = x; i <= n; i += (i & -i))
            for (int j = y; j <= m; j += (j & -j))
                bit[i][j] ^= val;
    }

    // Prefix XOR: XOR of submatrix (1,1) to (x,y)
    ll prefixXOR(int x, int y)
    {
        ll result = 0;
        for (int i = x; i > 0; i -= (i & -i))
            for (int j = y; j > 0; j -= (j & -j))
                result ^= bit[i][j];
        return result;
    }

    // Range XOR: XOR of submatrix (x1,y1) to (x2,y2)
    // Inclusion-Exclusion (XOR version)
    ll rangeXOR(int x1, int y1, int x2, int y2)
    {
        return prefixXOR(x2, y2) ^ prefixXOR(x1 - 1, y2) ^ prefixXOR(x2, y1 - 1) ^ prefixXOR(x1 - 1, y1 - 1);
    }

    // Point set: (x,y) = newVal
    void pointSet(int x, int y, ll newVal)
    {
        ll oldVal = rangeXOR(x, y, x, y); // current value
        update(x, y, oldVal ^ newVal);    // old^new XOR karo
    }
};

// ==========================
// Main
// ==========================
int main()
{
    // ---- 1D ----
    cout << "===== 1D Fenwick XOR =====\n";
    BIT1D_XOR bit1(5);

    // Array: [2, 4, 6, 8, 10]
    bit1.update(1, 2);
    bit1.update(2, 4);
    bit1.update(3, 6);
    bit1.update(4, 8);
    bit1.update(5, 10);

    cout << "prefixXOR(3)   = " << bit1.prefixXOR(3) << "\n";   // 2^4^6 = 0
    cout << "rangeXOR(2,4)  = " << bit1.rangeXOR(2, 4) << "\n"; // 4^6^8 = 10
    cout << "rangeXOR(1,5)  = " << bit1.rangeXOR(1, 5) << "\n"; // 2^4^6^8^10 = 8

    bit1.pointSet(3, 10); // arr[3] = 10
    cout << "After set(3,10):\n";
    cout << "rangeXOR(1,5)  = " << bit1.rangeXOR(1, 5) << "\n"; // 2^4^10^8^10 = 14

    // ---- 2D ----
    cout << "\n===== 2D Fenwick XOR =====\n";
    BIT2D_XOR bit2(4, 4);

    /*
      Matrix:
      1  2  3  4
      5  6  7  8
      9  10 11 12
      13 14 15 16
    */
    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= 4; j++)
            bit2.update(i, j, (ll)(i - 1) * 4 + j);

    cout << "prefixXOR(2,2)       = "
         << bit2.prefixXOR(2, 2) << "\n"; // 1^2^5^6 = 0

    cout << "rangeXOR(1,1,2,2)    = "
         << bit2.rangeXOR(1, 1, 2, 2) << "\n"; // 1^2^5^6 = 0

    cout << "rangeXOR(1,1,4,4)    = "
         << bit2.rangeXOR(1, 1, 4, 4) << "\n"; // all XOR

    cout << "rangeXOR(2,2,3,3)    = "
         << bit2.rangeXOR(2, 2, 3, 3) << "\n"; // 6^7^10^11 = 0

    bit2.pointSet(1, 1, 100); // (1,1) = 100
    cout << "After set(1,1,100):\n";
    cout << "rangeXOR(1,1,2,2)    = "
         << bit2.rangeXOR(1, 1, 2, 2) << "\n"; // 100^2^5^6

    return 0;
}