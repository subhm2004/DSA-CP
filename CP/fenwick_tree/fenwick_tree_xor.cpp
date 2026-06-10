#include <bits/stdc++.h>
using namespace std;
#define ll long long int

// ════════════════════════════════════════════════════════════════════════════
// FENWICK TREE — XOR Variant (1D + 2D)
// ────────────────────────────────────────────────────────────────────────────
// Normal BIT me + aur sum hota hai. XOR BIT me:
//   update: ^= val  (add ki jagah XOR)
//   query:  ^= bit  (sum ki jagah XOR)
//
// Range XOR = prefixXOR(r) ^ prefixXOR(l-1)
// Point set: purani value ^ nayi value XOR karke update
// i & -i -> LSB jump (same as normal BIT)
// ════════════════════════════════════════════════════════════════════════════

// ---------------------- 1D Fenwick XOR --------------------------------------
class BIT1D_XOR
{
public:
    int n;
    vector<ll> bit;

    // ── BIT1D_XOR: 1D XOR BIT initialize karo ──
    //   1) size 'n' store karo — array 1..n indexed hai
    //   2) bit vector ko size n+1 pe resize karo (index 0 unused)
    //   3) sab cells 0 se start — XOR identity element hai
    BIT1D_XOR(int n)
    {
        this->n = n;
        bit.assign(n + 1, 0);
    }

    // ── update: index 'i' pe 'val' XOR karo ──
    //   1) index i se shuru karo, jab tak i <= n tab tak loop chalao
    //   2) har covered BIT node bit[i] me val XOR karo (add ki jagah)
    //   3) i += (i & -i) se LSB jump — parent nodes tak propagate
    //   4) XOR associative hai, isliye normal BIT ka + wala pattern same kaam karta hai
    void update(int i, ll val)
    {
        for (; i <= n; i += (i & -i))  // i & -i = lowest set bit, next responsible node
            bit[i] ^= val;
    }

    // ── prefixXOR: arr[1..i] ka XOR ──
    //   1) result = 0 se start (XOR identity)
    //   2) index i se niche aate jao: i -= (i & -i) se previous responsible node
    //   3) har step pe bit[i] ko result me XOR karo
    //   4) i = 0 pe pohochte hi poora prefix XOR mil gaya
    ll prefixXOR(int i)
    {
        ll result = 0;
        for (; i > 0; i -= (i & -i))  // LSB hata ke pichle covered range pe jao
            result ^= bit[i];
        return result;
    }

    // ── rangeXOR: arr[l..r] ka XOR ──
    //   1) XOR bhi prefix difference se nikalta hai (sum jaisa inclusion-exclusion)
    //   2) agar l == 1 hai to seedha prefixXOR(r) return karo
    //   3) warna prefixXOR(r) ^ prefixXOR(l-1) — beech ka extra prefix cancel ho jata hai
    ll rangeXOR(int l, int r)
    {
        if (l == 1)
            return prefixXOR(r);
        return prefixXOR(r) ^ prefixXOR(l - 1);
    }

    // ── pointSet: arr[i] = newVal ──
    //   1) pehle rangeXOR(i,i) se purani value nikalo (single element ka XOR)
    //   2) oldVal ^ newVal = delta — jitna change chahiye woh XOR karna hai
    //   3) update(i, delta) se sirf index i ki value replace ho jaati hai
    void pointSet(int i, ll newVal)
    {
        ll oldVal = rangeXOR(i, i);
        update(i, oldVal ^ newVal);
    }
};

// ---------------------- 2D Fenwick XOR --------------------------------------
class BIT2D_XOR
{
public:
    int n, m;
    vector<vector<ll>> bit;

    // ── BIT2D_XOR: 2D XOR BIT initialize karo ──
    //   1) rows n aur cols m store karo (dono 1-indexed)
    //   2) (n+1) x (m+1) ka 2D bit array banao, sab 0
    //   3) row 0 aur col 0 dummy — actual data 1..n, 1..m me hai
    BIT2D_XOR(int n, int m)
    {
        this->n = n;
        this->m = m;
        bit.assign(n + 1, vector<ll>(m + 1, 0));
    }

    // ── update: cell (x,y) pe 'val' XOR karo ──
    //   1) outer loop: x se n tak, har step pe x += (x & -x) — row direction LSB jump
    //   2) inner loop: y se m tak, har step pe y += (y & -y) — col direction LSB jump
    //   3) har (i,j) node pe val XOR karo — 2D BIT me covered rectangles update hote hain
    void update(int x, int y, ll val)
    {
        for (int i = x; i <= n; i += (i & -i))       // row-wise parent nodes
            for (int j = y; j <= m; j += (j & -j))   // col-wise parent nodes
                bit[i][j] ^= val;
    }

    // ── prefixXOR: submatrix (1,1) to (x,y) ka XOR ──
    //   1) result = 0, phir i = x se niche, j = y se left aate jao
    //   2) dono dimensions me LSB jump: i -= (i&-i), j -= (j&-j)
    //   3) har visited bit[i][j] ko result me XOR karo
    //   4) yeh 2D BIT ka standard prefix query pattern hai
    ll prefixXOR(int x, int y)
    {
        ll result = 0;
        for (int i = x; i > 0; i -= (i & -i))
            for (int j = y; j > 0; j -= (j & -j))
                result ^= bit[i][j];
        return result;
    }

    // ── rangeXOR: rectangle (x1,y1) to (x2,y2) ──
    //   1) 2D inclusion-exclusion: 4 prefix XORs ka XOR lo
    //   2) prefixXOR(x2,y2) = poora bada rectangle
    //   3) baaki 3 terms extra corners subtract/cancel karte hain (XOR me ^ se)
    //   4) formula: P(x2,y2) ^ P(x1-1,y2) ^ P(x2,y1-1) ^ P(x1-1,y1-1)
    ll rangeXOR(int x1, int y1, int x2, int y2)
    {
        return prefixXOR(x2, y2) ^ prefixXOR(x1 - 1, y2) ^ prefixXOR(x2, y1 - 1) ^ prefixXOR(x1 - 1, y1 - 1);
    }

    // ── pointSet: (x,y) = newVal ──
    //   1) rangeXOR(x,y,x,y) se cell ki current value nikalo
    //   2) oldVal ^ newVal = XOR delta calculate karo
    //   3) update(x, y, delta) se sirf woh cell set ho jaati hai
    void pointSet(int x, int y, ll newVal)
    {
        ll oldVal = rangeXOR(x, y, x, y);
        update(x, y, oldVal ^ newVal);
    }
};

// ── main: 1D aur 2D XOR BIT demo ──
//   1) 1D BIT pe point updates, prefix/range XOR, pointSet test karo
//   2) 2D BIT pe grid fill karo, prefix aur rectangle XOR print karo
int main()
{
    cout << "===== 1D Fenwick XOR =====\n";
    BIT1D_XOR bit1(5);

    bit1.update(1, 2);
    bit1.update(2, 4);
    bit1.update(3, 6);
    bit1.update(4, 8);
    bit1.update(5, 10);

    cout << "prefixXOR(3)   = " << bit1.prefixXOR(3) << "\n";
    cout << "rangeXOR(2,4)  = " << bit1.rangeXOR(2, 4) << "\n";
    cout << "rangeXOR(1,5)  = " << bit1.rangeXOR(1, 5) << "\n";

    bit1.pointSet(3, 10);
    cout << "After set(3,10):\n";
    cout << "rangeXOR(1,5)  = " << bit1.rangeXOR(1, 5) << "\n";

    cout << "\n===== 2D Fenwick XOR =====\n";
    BIT2D_XOR bit2(4, 4);

    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= 4; j++)
            bit2.update(i, j, (ll)(i - 1) * 4 + j);

    cout << "prefixXOR(2,2)       = " << bit2.prefixXOR(2, 2) << "\n";
    cout << "rangeXOR(1,1,2,2)    = " << bit2.rangeXOR(1, 1, 2, 2) << "\n";
    cout << "rangeXOR(1,1,4,4)    = " << bit2.rangeXOR(1, 1, 4, 4) << "\n";
    cout << "rangeXOR(2,2,3,3)    = " << bit2.rangeXOR(2, 2, 3, 3) << "\n";

    bit2.pointSet(1, 1, 100);
    cout << "After set(1,1,100):\n";
    cout << "rangeXOR(1,1,2,2)    = " << bit2.rangeXOR(1, 1, 2, 2) << "\n";

    return 0;
}
