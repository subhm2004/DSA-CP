#include <bits/stdc++.h>
using namespace std;
#define ll long long int

// ==========================
// 1️⃣ Point Update & Range Query
// ==========================
class BIT_PointUpdate_RangeQuery
{
public:
    int n;
    vector<ll> bit;

    BIT_PointUpdate_RangeQuery(int n)
    {
        this->n = n;
        bit.resize(n + 1, 0);
    }

    void update(int i, ll x)
    {
        for (; i <= n; i += (i & -i))
            bit[i] += x;
    }

    ll prefixSum(int i)
    {
        ll total = 0;
        for (; i > 0; i -= (i & -i))
            total += bit[i];
        return total;
    }

    ll rangeSum(int l, int r)
    {
        return prefixSum(r) - prefixSum(l - 1);
    }
};

// ==========================
// 2️⃣ Range Update & Point Query
// ==========================
class BIT_RangeUpdate_PointQuery
{
public:
    int n;
    vector<ll> bit;

    BIT_RangeUpdate_PointQuery(int n)
    {
        this->n = n;
        bit.resize(n + 1, 0);
    }

    void rangeAdd(int l, int r, ll x)
    {
        for (int i = l; i <= n; i += (i & -i))
            bit[i] += x;
        for (int i = r + 1; i <= n; i += (i & -i))
            bit[i] -= x;
    }

    ll pointQuery(int i)
    {
        ll total = 0;
        for (; i > 0; i -= (i & -i))
            total += bit[i];
        return total;
    }
};

// ==========================
// 3️⃣ Range Update & Range Query
// ==========================
class BIT_RangeUpdate_RangeQuery
{
public:
    int n;
    vector<ll> Bit1, Bit2;

    BIT_RangeUpdate_RangeQuery(int n)
    {
        this->n = n;
        Bit1.resize(n + 1, 0);
        Bit2.resize(n + 1, 0);
    }

    void add(vector<ll> &bit, int idx, ll x)
    {
        for (; idx <= n; idx += (idx & -idx))
            bit[idx] += x;
    }

    void rangeAdd(int l, int r, ll x)
    {
        add(Bit1, l, x);
        add(Bit1, r + 1, -x);
        add(Bit2, l, x * (l - 1));
        add(Bit2, r + 1, -x * r);
    }

    ll sum(vector<ll> &bit, int idx)
    {
        ll total = 0;
        for (; idx > 0; idx -= (idx & -idx))
            total += bit[idx];
        return total;
    }

    ll prefSum(int idx)
    {
        return sum(Bit1, idx) * idx - sum(Bit2, idx);
    }

    ll rangeSum(int l, int r)
    {
        return prefSum(r) - prefSum(l - 1);
    }
};

// ==========================
// Main examples
// ==========================
int main()
{
    int n = 5;

    cout << "===== 1️⃣ Point Update & Range Query =====\n";
    BIT_PointUpdate_RangeQuery bit1(n);
    bit1.update(2, 10);
    bit1.update(4, 5);
    bit1.update(5, 3);
    cout << "rangeSum(1,3) = " << bit1.rangeSum(1, 3) << "\n"; // 10
    cout << "rangeSum(2,5) = " << bit1.rangeSum(2, 5) << "\n"; // 10+0+5+3 = 18
    cout << "rangeSum(3,5) = " << bit1.rangeSum(3, 5) << "\n"; // 0+5+3 = 8

    cout << "\n===== 2️⃣ Range Update & Point Query =====\n";
    BIT_RangeUpdate_PointQuery bit2(n);
    bit2.rangeAdd(2, 4, 5);
    bit2.rangeAdd(1, 3, 2);
    cout << "pointQuery(1) = " << bit2.pointQuery(1) << "\n"; // 2
    cout << "pointQuery(3) = " << bit2.pointQuery(3) << "\n"; // 2+5=7
    cout << "pointQuery(5) = " << bit2.pointQuery(5) << "\n"; // 0

    cout << "\n===== 3️⃣ Range Update & Range Query =====\n";
    BIT_RangeUpdate_RangeQuery bit3(n);
    bit3.rangeAdd(1, 3, 2);
    bit3.rangeAdd(2, 5, 3);
    cout << "rangeSum(1,3) = " << bit3.rangeSum(1, 3) << "\n"; // 2+5+5 = 12
    cout << "rangeSum(2,5) = " << bit3.rangeSum(2, 5) << "\n"; // 5+5+3+3 = 16
    cout << "rangeSum(3,5) = " << bit3.rangeSum(3, 5) << "\n"; // 5+3+3 = 11

    return 0;
}
