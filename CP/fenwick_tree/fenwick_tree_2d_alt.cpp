#include <bits/stdc++.h>
using namespace std;
#define ll long long int

// ════════════════════════════════════════════════════════════════════════════
// FENWICK TREE VARIATIONS — 1D + 2D (Point/Range combos)
// ────────────────────────────────────────────────────────────────────────────
// BIT 1-indexed hota hai. Core:
//   i & -i  -> LSB (lowest set bit) — update/query me jump karne ke liye
//   update: i += (i & -i)  |  query: i -= (i & -i)
//
// Is file me:
//   BIT1D     -> point update + range sum (1D)
//   BIT1D_RU  -> range add + point query (difference trick)
//   BIT2D     -> point update + submatrix sum (2D BIT)
// ════════════════════════════════════════════════════════════════════════════

// ---------------------- 1️⃣ 1D Point Update & Range Sum ----------------------
class BIT1D
{
public:
    int n;
    vector<ll> bit;

    // ── BIT1D: point-update range-query BIT ──
    //   1) n size store, bit vector n+1 length (1-indexed)
    //   2) initializer list se sab 0 — empty BIT
    BIT1D(int n) : n(n), bit(n + 1, 0) {}

    // ── update: index 'i' pe 'val' add karo ──
    //   1) i se n tak har responsible BIT node pe val add karo
    //   2) i += (i & -i) — LSB jump se parent nodes cover hote hain
    //   3) O(log n) me poora propagation ho jaata hai
    void update(int i, ll val)
    {
        for (; i <= n; i += (i & -i))  // i & -i = lowest set bit
            bit[i] += val;
    }

    // ── prefix: [1, i] ka sum ──
    //   1) sum = 0, i > 0 tak loop chalao
    //   2) bit[i] ko sum me add karo
    //   3) i -= (i & -i) se pichla prefix-covered node lo
    ll prefix(int i)
    {
        ll sum = 0;
        for (; i > 0; i -= (i & -i))
            sum += bit[i];
        return sum;
    }

    // ── query: [l, r] ka sum ──
    //   1) range sum = prefix(r) - prefix(l-1) — classic inclusion-exclusion
    //   2) prefix(r) me [1..r] sab included
    //   3) prefix(l-1) subtract karke [l..r] isolate ho jaata hai
    ll query(int l, int r)
    {
        return prefix(r) - prefix(l - 1);
    }
};

// ---------------------- 2️⃣ 1D Range Update & Point Query ------------------
class BIT1D_RU
{
public:
    int n;
    vector<ll> bit;

    // ── BIT1D_RU: range-update point-query BIT ──
    //   1) andar difference array store hota hai, direct array nahi
    //   2) bit size n+1, sab 0
    BIT1D_RU(int n) : n(n), bit(n + 1, 0) {}

    // ── add: internal — index 'i' pe 'val' add (difference array style) ──
    //   1) standard BIT update — bit[i] += val
    //   2) i += (i & -i) se parent nodes tak propagate
    //   3) yeh internal helper hai, rangeAdd isko call karta hai
    void add(int i, ll val)
    {
        for (; i <= n; i += (i & -i))
            bit[i] += val;
    }

    // ── rangeAdd: arr[l..r] me sab me 'val' add karo ──
    //   1) difference trick: start pe +val, end ke baad -val
    //   2) add(l, val) — position l se aage sab me +val accumulate hoga
    //   3) add(r+1, -val) — r+1 se aage effect band, range exactly [l,r] rehta hai
    void rangeAdd(int l, int r, ll val)
    {
        add(l, val);
        add(r + 1, -val);  // difference array: r ke baad delta reverse
    }

    // ── pointQuery: arr[i] ki value = prefix sum at i ──
    //   1) difference array ka i-th prefix sum = actual arr[i]
    //   2) normal BIT query jaisa: i se 1 tak bit nodes add karo
    //   3) i -= (i & -i) se LSB jump — O(log n)
    ll pointQuery(int i)
    {
        ll sum = 0;
        for (; i > 0; i -= (i & -i))
            sum += bit[i];
        return sum;
    }
};

// ---------------------- 3️⃣ 2D Point Update & Range Sum --------------------
class BIT2D
{
public:
    int n, m;
    vector<vector<ll>> bit;

    // ── BIT2D: 2D point-update range-sum BIT ──
    //   1) n x m grid, 1-indexed
    //   2) (n+1) x (m+1) bit matrix initialize
    BIT2D(int n, int m) : n(n), m(m),
                          bit(n + 1, vector<ll>(m + 1, 0)) {}

    // ── update: cell (x, y) pe 'val' add karo ──
    //   1) row loop: i = x se n, i += (i&-i) — row-wise LSB jump
    //   2) col loop: j = y se m, j += (j&-j) — col-wise LSB jump
    //   3) har bit[i][j] += val — 2D BIT propagation
    void update(int x, int y, ll val)
    {
        for (int i = x; i <= n; i += (i & -i))       // row direction
            for (int j = y; j <= m; j += (j & -j))   // col direction
                bit[i][j] += val;
    }

    // ── prefix: submatrix (1,1) se (x,y) tak ka sum ──
    //   1) i = x, j = y se (0,0) ki taraf aao
    //   2) dono me LSB jump: i -= (i&-i), j -= (j&-j)
    //   3) har bit[i][j] ko sum me add karte jao
    ll prefix(int x, int y)
    {
        ll sum = 0;
        for (int i = x; i > 0; i -= (i & -i))
            for (int j = y; j > 0; j -= (j & -j))
                sum += bit[i][j];
        return sum;
    }

    // ── query: rectangle (x1,y1) se (x2,y2) ka sum (inclusion-exclusion) ──
    //   1) prefix(x2,y2) = poora bada rectangle
    //   2) minus prefix(x1-1,y2) aur prefix(x2,y1-1) — extra strips hatao
    //   3) plus prefix(x1-1,y1-1) — corner double-count fix
    ll query(int x1, int y1, int x2, int y2)
    {
        return prefix(x2, y2) - prefix(x1 - 1, y2) - prefix(x2, y1 - 1) + prefix(x1 - 1, y1 - 1);
    }
};

// ── main: teen BIT variations ka demo ──
int main()
{
    cout << "===== 1D Point Update Range Sum =====\n";
    BIT1D b1(5);
    b1.update(1, 3);
    b1.update(3, 7);
    b1.update(5, 2);
    cout << "query(1,3) = " << b1.query(1, 3) << "\n";
    cout << "query(1,5) = " << b1.query(1, 5) << "\n";
    b1.update(3, -3);
    cout << "After update(3,-3):\n";
    cout << "query(1,3) = " << b1.query(1, 3) << "\n";

    cout << "\n===== 1D Range Update Point Query =====\n";
    BIT1D_RU b2(5);
    b2.rangeAdd(1, 3, 5);
    b2.rangeAdd(2, 5, 2);
    cout << "pointQuery(1) = " << b2.pointQuery(1) << "\n";
    cout << "pointQuery(2) = " << b2.pointQuery(2) << "\n";
    cout << "pointQuery(4) = " << b2.pointQuery(4) << "\n";
    cout << "pointQuery(5) = " << b2.pointQuery(5) << "\n";

    cout << "\n===== 2D Point Update Range Sum =====\n";
    BIT2D b3(4, 4);
    b3.update(1, 1, 10);
    b3.update(2, 2, 5);
    b3.update(3, 3, 7);
    cout << "query(1,1,2,2) = " << b3.query(1, 1, 2, 2) << "\n";
    cout << "query(1,1,4,4) = " << b3.query(1, 1, 4, 4) << "\n";
    cout << "query(2,2,3,3) = " << b3.query(2, 2, 3, 3) << "\n";
    b3.update(2, 2, -5);
    cout << "After update(2,2,-5):\n";
    cout << "query(1,1,2,2) = " << b3.query(1, 1, 2, 2) << "\n";

    return 0;
}
