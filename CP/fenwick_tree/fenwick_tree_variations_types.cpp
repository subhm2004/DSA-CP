#include <bits/stdc++.h>
using namespace std;
#define ll long long int

// ════════════════════════════════════════════════════════════════════════════
// FENWICK TREE — 3 Variations (Types Reference)
// ────────────────────────────────────────────────────────────────────────────
// Variation 1 (Point Update + Range Query) sabse zyada use hoti hai CP me.
// BIT 1-indexed, i & -i se LSB jump karte hain update/query me.
// ════════════════════════════════════════════════════════════════════════════

// ---------------------- 1️⃣ Point Update & Range Query (mainly use hoga) ------
class BIT_PointUpdate_RangeQuery
{
public:
    int n;
    vector<ll> bit;

    // ── BIT_PointUpdate_RangeQuery: standard BIT setup ──
    //   1) n = array length, bit size n+1 (1-indexed convention)
    //   2) resize + zero initialize
    BIT_PointUpdate_RangeQuery(int n)
    {
        this->n = n;
        bit.resize(n + 1, 0);
    }

    // ── update: index 'i' pe 'x' add karo ──
    //   1) i se n tak loop — har covered BIT node pe x add
    //   2) i += (i & -i) — LSB se agla parent node
    //   3) O(log n) me point update complete
    void update(int i, ll x)
    {
        for (; i <= n; i += (i & -i))  // i & -i = lowest set bit
            bit[i] += x;
    }

    // ── prefixSum: [1, i] ka sum ──
    //   1) total = 0, i > 0 tak chalao
    //   2) bit[i] ko total me add karo
    //   3) i -= (i & -i) se pichla responsible node
    ll prefixSum(int i)
    {
        ll total = 0;
        for (; i > 0; i -= (i & -i))
            total += bit[i];
        return total;
    }

    // ── rangeSum: [l, r] ka sum ──
    //   1) prefixSum(r) - prefixSum(l-1) — standard range formula
    //   2) do prefix queries, O(log n) each
    ll rangeSum(int l, int r)
    {
        return prefixSum(r) - prefixSum(l - 1);
    }
};

// ---------------------- 2️⃣ Range Update & Point Query ----------------------
class BIT_RangeUpdate_PointQuery
{
public:
    int n;
    vector<ll> bit;

    // ── BIT_RangeUpdate_PointQuery: difference-array BIT ──
    //   1) andar difference array BIT pe stored hai
    //   2) n+1 size, sab 0
    BIT_RangeUpdate_PointQuery(int n)
    {
        this->n = n;
        bit.resize(n + 1, 0);
    }

    // ── rangeAdd: [l,r] me 'x' add (difference array on BIT) ──
    //   1) l se n tak BIT nodes me +x add — start se aage sab affect
    //   2) r+1 se n tak BIT nodes me -x add — range ke baad cancel
    //   3) do alag loops kyunki l aur r+1 alag BIT paths follow karte hain
    //   4) prefix sum at i = actual arr[i] ban jaata hai
    void rangeAdd(int l, int r, ll x)
    {
        for (int i = l; i <= n; i += (i & -i))
            bit[i] += x;
        for (int i = r + 1; i <= n; i += (i & -i))  // r+1 pe -x: range band
            bit[i] -= x;
    }

    // ── pointQuery: index 'i' ki value ──
    //   1) difference array ka prefix sum = arr[i]
    //   2) normal BIT query: i se 1 tak nodes add karo
    //   3) i -= (i & -i) LSB jump
    ll pointQuery(int i)
    {
        ll total = 0;
        for (; i > 0; i -= (i & -i))
            total += bit[i];
        return total;
    }
};

// ---------------------- 3️⃣ Range Update & Range Query ----------------------
class BIT_RangeUpdate_RangeQuery
{
public:
    int n;
    vector<ll> Bit1, Bit2;

    // ── BIT_RangeUpdate_RangeQuery: do BIT wala range update+query ──
    //   1) Bit1 aur Bit2 — do BIT trick se range add + range sum dono
    //   2) formula: prefix sum at i = Bit1_sum(i)*i - Bit2_sum(i)
    BIT_RangeUpdate_RangeQuery(int n)
    {
        this->n = n;
        Bit1.resize(n + 1, 0);
        Bit2.resize(n + 1, 0);
    }

    // ── add: internal helper — kisi BIT pe index pe x add ──
    //   1) reference se bit vector pass hota hai (Bit1 ya Bit2)
    //   2) standard BIT update: idx += (idx & -idx)
    void add(vector<ll> &bit, int idx, ll x)
    {
        for (; idx <= n; idx += (idx & -idx))
            bit[idx] += x;
    }

    // ── rangeAdd: do BIT trick se range me add ──
    //   1) Bit1 pe: add(l, x) aur add(r+1, -x) — difference style coefficients
    //   2) Bit2 pe: add(l, x*(l-1)) aur add(r+1, -x*r) — linear correction term
    //   3) dono BIT milke prefix sum formula banate hain: Bit1*i - Bit2
    void rangeAdd(int l, int r, ll x)
    {
        add(Bit1, l, x);
        add(Bit1, r + 1, -x);
        add(Bit2, l, x * (l - 1));   // Bit2 correction: l-1 factor
        add(Bit2, r + 1, -x * r);    // Bit2 correction: r factor at r+1
    }

    // ── sum: internal — BIT ka prefix sum ──
    //   1) idx se 1 tak bit[idx] add karo
    //   2) idx -= (idx & -idx) LSB jump
    ll sum(vector<ll> &bit, int idx)
    {
        ll total = 0;
        for (; idx > 0; idx -= (idx & -idx))
            total += bit[idx];
        return total;
    }

    // ── prefSum: Bit1*idx - Bit2 se prefix array sum ──
    //   1) sum(Bit1, idx) * idx — linear term from range adds
    //   2) minus sum(Bit2, idx) — offset correction
    //   3) yeh [1..idx] ka actual array prefix sum deta hai
    ll prefSum(int idx)
    {
        return sum(Bit1, idx) * idx - sum(Bit2, idx);
    }

    // ── rangeSum: [l, r] ka sum ──
    //   1) prefSum(r) - prefSum(l-1) — do prefix queries
    //   2) range update ke baad bhi O(log n) me kaam karta hai
    ll rangeSum(int l, int r)
    {
        return prefSum(r) - prefSum(l - 1);
    }
};

// ── main: teen variations ka side-by-side demo ──
int main()
{
    int n = 5;

    cout << "===== 1️⃣ Point Update & Range Query =====\n";
    BIT_PointUpdate_RangeQuery bit1(n);
    bit1.update(2, 10);
    bit1.update(4, 5);
    bit1.update(5, 3);
    cout << "rangeSum(1,3) = " << bit1.rangeSum(1, 3) << "\n";
    cout << "rangeSum(2,5) = " << bit1.rangeSum(2, 5) << "\n";
    cout << "rangeSum(3,5) = " << bit1.rangeSum(3, 5) << "\n";

    cout << "\n===== 2️⃣ Range Update & Point Query =====\n";
    BIT_RangeUpdate_PointQuery bit2(n);
    bit2.rangeAdd(2, 4, 5);
    bit2.rangeAdd(1, 3, 2);
    cout << "pointQuery(1) = " << bit2.pointQuery(1) << "\n";
    cout << "pointQuery(3) = " << bit2.pointQuery(3) << "\n";
    cout << "pointQuery(5) = " << bit2.pointQuery(5) << "\n";

    cout << "\n===== 3️⃣ Range Update & Range Query =====\n";
    BIT_RangeUpdate_RangeQuery bit3(n);
    bit3.rangeAdd(1, 3, 2);
    bit3.rangeAdd(2, 5, 3);
    cout << "rangeSum(1,3) = " << bit3.rangeSum(1, 3) << "\n";
    cout << "rangeSum(2,5) = " << bit3.rangeSum(2, 5) << "\n";
    cout << "rangeSum(3,5) = " << bit3.rangeSum(3, 5) << "\n";

    return 0;
}
