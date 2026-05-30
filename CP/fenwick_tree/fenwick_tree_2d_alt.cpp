#include <bits/stdc++.h>
using namespace std;
#define ll long long int

// ==========================
// 1️⃣ 1D - Point Update & Range Sum
// ==========================
class BIT1D
{
public:
    int n;
    vector<ll> bit;

    BIT1D(int n) : n(n), bit(n + 1, 0) {}

    void update(int i, ll val)
    {
        for (; i <= n; i += (i & -i))
            bit[i] += val;
    }

    ll prefix(int i)
    {
        ll sum = 0;
        for (; i > 0; i -= (i & -i))
            sum += bit[i];
        return sum;
    }

    ll query(int l, int r)
    {
        return prefix(r) - prefix(l - 1);
    }
};

// ==========================
// 2️⃣ 1D - Range Update & Point Query
// ==========================
class BIT1D_RU
{
public:
    int n;
    vector<ll> bit;

    BIT1D_RU(int n) : n(n), bit(n + 1, 0) {}

    void add(int i, ll val)
    {
        for (; i <= n; i += (i & -i))
            bit[i] += val;
    }

    // arr[l..r] += val
    void rangeAdd(int l, int r, ll val)
    {
        add(l, val);
        add(r + 1, -val);
    }

    // arr[i] ki current value
    ll pointQuery(int i)
    {
        ll sum = 0;
        for (; i > 0; i -= (i & -i))
            sum += bit[i];
        return sum;
    }
};

// ==========================
// 3️⃣ 2D - Point Update & Range Sum
// ==========================
class BIT2D
{
public:
    int n, m;
    vector<vector<ll>> bit;

    BIT2D(int n, int m) : n(n), m(m),
                          bit(n + 1, vector<ll>(m + 1, 0)) {}

    void update(int x, int y, ll val)
    {
        for (int i = x; i <= n; i += (i & -i))
            for (int j = y; j <= m; j += (j & -j))
                bit[i][j] += val;
    }

    ll prefix(int x, int y)
    {
        ll sum = 0;
        for (int i = x; i > 0; i -= (i & -i))
            for (int j = y; j > 0; j -= (j & -j))
                sum += bit[i][j];
        return sum;
    }

    // Sum of submatrix (x1,y1) to (x2,y2)
    ll query(int x1, int y1, int x2, int y2)
    {
        return prefix(x2, y2) - prefix(x1 - 1, y2) - prefix(x2, y1 - 1) + prefix(x1 - 1, y1 - 1);
    }
};

// ==========================
// Main
// ==========================
int main()
{
    cout << "===== 1D Point Update Range Sum =====\n";
    BIT1D b1(5);
    b1.update(1, 3);
    b1.update(3, 7);
    b1.update(5, 2);
    cout << "query(1,3) = " << b1.query(1, 3) << "\n"; // 10
    cout << "query(1,5) = " << b1.query(1, 5) << "\n"; // 12
    b1.update(3, -3);                                  // arr[3] -= 3
    cout << "After update(3,-3):\n";
    cout << "query(1,3) = " << b1.query(1, 3) << "\n"; // 7

    cout << "\n===== 1D Range Update Point Query =====\n";
    BIT1D_RU b2(5);
    b2.rangeAdd(1, 3, 5);                                   // arr[1..3] += 5
    b2.rangeAdd(2, 5, 2);                                   // arr[2..5] += 2
    cout << "pointQuery(1) = " << b2.pointQuery(1) << "\n"; // 5
    cout << "pointQuery(2) = " << b2.pointQuery(2) << "\n"; // 7
    cout << "pointQuery(4) = " << b2.pointQuery(4) << "\n"; // 2
    cout << "pointQuery(5) = " << b2.pointQuery(5) << "\n"; // 2

    cout << "\n===== 2D Point Update Range Sum =====\n";
    BIT2D b3(4, 4);
    b3.update(1, 1, 10);
    b3.update(2, 2, 5);
    b3.update(3, 3, 7);
    cout << "query(1,1,2,2) = " << b3.query(1, 1, 2, 2) << "\n"; // 15
    cout << "query(1,1,4,4) = " << b3.query(1, 1, 4, 4) << "\n"; // 22
    cout << "query(2,2,3,3) = " << b3.query(2, 2, 3, 3) << "\n"; // 12
    b3.update(2, 2, -5);                                         // (2,2) -= 5
    cout << "After update(2,2,-5):\n";
    cout << "query(1,1,2,2) = " << b3.query(1, 1, 2, 2) << "\n"; // 10

    return 0;
}