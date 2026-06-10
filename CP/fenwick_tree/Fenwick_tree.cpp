#include <bits/stdc++.h>
using namespace std;
#define ll long long int

// ════════════════════════════════════════════════════════════════════════════
// FENWICK TREE (BIT) — 3 Classic Variations
// ────────────────────────────────────────────────────────────────────────────
// BIT 1-indexed hota hai. Core trick:
//   i & -i  -> lowest set bit (LSB) — isse pata chalta hai kaunse nodes
//              responsible hain index 'i' ke liye
//
//   update: i += (i & -i)  -> upar jaate jao, responsible nodes me add karo
//   query:  i -= (i & -i)  -> neeche aate jao, prefix sum nikalo
//
// Teen variations:
//   1) Point Update + Range Query  (sabse common)
//   2) Range Update + Point Query  (difference array trick on BIT)
//   3) Range Update + Range Query  (do BITs: Bit1 + Bit2)
// ════════════════════════════════════════════════════════════════════════════

// ---------------------- 1️⃣ Point Update & Range Query ----------------------
class BIT_PointUpdate_RangeQuery
{
public:
    int n;
    vector<ll> bit;  // 1-indexed fenwick array

    // ── BIT_PointUpdate_RangeQuery: constructor ──
    //   1) n store karo — kitne elements handle karne hain
    //   2) bit array n+1 size ka banao (index 0 dummy, 1-indexed BIT)
    //   3) sab entries 0 se initialize — abhi koi update nahi hua
    BIT_PointUpdate_RangeQuery(int n)
    {
        this->n = n;
        bit.resize(n + 1, 0);
    }

    // ── update: point add at index i ──
    //   1) index i se shuru karo (1-indexed)
    //   2) bit[i] me x add karo — ye node i ke prefix sum me contribute karta hai
    //   3) i += (i & -i) — LSB jump se agla responsible parent node pakdo
    //   4) jab tak i <= n, upar ke saare affected nodes update karte jao
    void update(int i, ll x)
    {
        for (; i <= n; i += (i & -i))  // i & -i = lowest set bit → next parent in BIT
            bit[i] += x;
    }

    // ── prefixSum: [1, i] ka cumulative sum ──
    //   1) total = 0 se shuru karo
    //   2) bit[i] ko total me jodo — ye node kuch prefix ranges cover karta hai
    //   3) i -= (i & -i) — LSB hata ke pichla covered block pakdo
    //   4) i > 0 tak repeat — saare relevant BIT nodes ka sum mil jaata hai
    ll prefixSum(int i)
    {
        ll total = 0;
        for (; i > 0; i -= (i & -i))  // neeche aate jao, har step pe ek block subtract
            total += bit[i];
        return total;
    }

    // ── rangeSum: [l, r] interval ka sum ──
    //   1) prefixSum(r) se [1, r] ka total lo
    //   2) prefixSum(l-1) subtract karo — [1, l-1] ka hissa hata do
    //   3) bacha hua = exactly [l, r] ka sum (inclusion-exclusion trick)
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

    // ── BIT_RangeUpdate_PointQuery: constructor ──
    //   1) n store karo, bit array n+1 size allocate karo
    //   2) sab 0 initialize — difference array style BIT ready
    BIT_RangeUpdate_PointQuery(int n)
    {
        this->n = n;
        bit.resize(n + 1, 0);
    }

    // ── rangeAdd: [l, r] me sab elements ko +x ──
    //   1) difference array trick: l pe +x daalo (range start)
    //   2) r+1 pe -x daalo (range ke baad effect band)
    //   3) dono jagah BIT update loop — i += (i & -i) se upar propagate
    //   4) prefix sum karne pe actual arr[i] automatically mil jaata hai
    void rangeAdd(int l, int r, ll x)
    {
        for (int i = l; i <= n; i += (i & -i))      // +x at start of range
            bit[i] += x;
        for (int i = r + 1; i <= n; i += (i & -i))  // -x just after range ends
            bit[i] -= x;
    }

    // ── pointQuery: index i ki actual value ──
    //   1) difference array ka prefix sum = original array ki value hoti hai
    //   2) i se neeche aate jao, har BIT node ka sum lo
    //   3) i -= (i & -i) se agla block — jab tak i > 0
    //   4) total = arr[i] after all range adds applied
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
    vector<ll> Bit1, Bit2;  // do BITs se range add + range sum dono handle

    // ── BIT_RangeUpdate_RangeQuery: constructor ──
    //   1) do BIT arrays allocate — Bit1 aur Bit2 dono n+1 size
    //   2) Bit1 = simple difference of range adds
    //   3) Bit2 = weighted difference (prefix formula ke liye zaroori)
    BIT_RangeUpdate_RangeQuery(int n)
    {
        this->n = n;
        Bit1.resize(n + 1, 0);
        Bit2.resize(n + 1, 0);
    }

    // ── add: internal BIT point update ──
    //   1) diye gaye BIT array ke index idx pe x add karo
    //   2) idx += (idx & -idx) se upar propagate karo
    //   3) jab tak idx <= n — standard BIT update loop
    void add(vector<ll> &bit, int idx, ll x)
    {
        for (; idx <= n; idx += (idx & -idx))  // LSB jump — next responsible node
            bit[idx] += x;
    }

    // ── rangeAdd: [l, r] me +x (do BIT trick) ──
    //   1) Bit1 me difference: l pe +x, r+1 pe -x
    //   2) Bit2 me weighted diff: l pe +x*(l-1), r+1 pe -x*r
    //   3) ye formula se prefix sum = actual array sum ban jaata hai
    //   4) formula: prefSum(i) = sum(Bit1,i)*i - sum(Bit2,i)
    void rangeAdd(int l, int r, ll x)
    {
        add(Bit1, l, x);
        add(Bit1, r + 1, -x);
        add(Bit2, l, x * (l - 1));   // weighted term for prefix reconstruction
        add(Bit2, r + 1, -x * r);
    }

    // ── sum: BIT se prefix sum at idx ──
    //   1) idx se neeche aate jao, har node ka value jodo
    //   2) idx -= (idx & -idx) — pichla covered block
    //   3) total return — [1, idx] ka prefix in this BIT
    ll sum(vector<ll> &bit, int idx)
    {
        ll total = 0;
        for (; idx > 0; idx -= (idx & -idx))
            total += bit[idx];
        return total;
    }

    // ── prefSum: [1, idx] ka actual array sum ──
    //   1) Bit1 ka prefix lo aur idx se multiply karo
    //   2) Bit2 ka prefix subtract karo
    //   3) result = real cumulative sum of original array up to idx
    ll prefSum(int idx)
    {
        return sum(Bit1, idx) * idx - sum(Bit2, idx);
    }

    // ── rangeSum: [l, r] ka sum ──
    //   1) prefSum(r) se [1, r] ka total lo
    //   2) prefSum(l-1) subtract — standard range from prefix trick
    ll rangeSum(int l, int r)
    {
        return prefSum(r) - prefSum(l - 1);
    }
};

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
