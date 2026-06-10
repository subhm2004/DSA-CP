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
// Range XOR = prefixXOR(r) ^ prefixXOR(l-1)  (same inclusion-exclusion idea)
// Point set: purani value ^ nayi value XOR karke update
// ════════════════════════════════════════════════════════════════════════════

// ---------------------- 1D Fenwick XOR --------------------------------------
class BIT1D_XOR
{
public:
    int n;
    vector<ll> bit;

    // ── BIT1D_XOR: 1D XOR BIT banao ──
    //   1) n = array size (1-indexed use hoga)
    //   2) bit array size n+1, index 0 skip
    //   3) initial sab 0 — XOR ke liye neutral value
    BIT1D_XOR(int n)
    {
        this->n = n;
        bit.assign(n + 1, 0);
    }

    // ── update: index 'i' pe 'val' XOR karo ──
    //   1) i se start karke har responsible BIT node tak jao
    //   2) bit[i] ^= val — value add nahi, XOR hota hai
    //   3) i += (i & -i) se agla parent node — LSB trick same as normal BIT
    void update(int i, ll val)
    {
        for (; i <= n; i += (i & -i))  // i & -i = lowest set bit
            bit[i] ^= val;
    }

    // ── prefixXOR: arr[1..i] ka XOR ──
    //   1) result 0 se shuru, i > 0 tak loop
    //   2) har node bit[i] ko result me XOR karo
    //   3) i -= (i & -i) se pichla covered prefix node pick karo
    //   4) end me [1..i] ka cumulative XOR milta hai
    ll prefixXOR(int i)
    {
        ll result = 0;
        for (; i > 0; i -= (i & -i))
            result ^= bit[i];
        return result;
    }

    // ── rangeXOR: arr[l..r] ka XOR ──
    //   1) prefix XOR se range nikalte hain: XOR(l..r) = pref(r) ^ pref(l-1)
    //   2) l==1 edge case: seedha prefixXOR(r), kyunki l-1 invalid ho jata hai
    //   3) do prefix XOR karke beech wala portion isolate ho jata hai
    ll rangeXOR(int l, int r)
    {
        if (l == 1)
            return prefixXOR(r);
        return prefixXOR(r) ^ prefixXOR(l - 1);
    }

    // ── pointSet: arr[i] = newVal (purani ^ nayi se delta update) ──
    //   1) rangeXOR(i,i) se abhi ki value oldVal nikalo
    //   2) oldVal ^ newVal = kitna XOR karna hai woh delta hai
    //   3) update(i, delta) call karke cell ko exactly newVal pe set karo
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

    // ── BIT2D_XOR: 2D XOR BIT initialize ──
    //   1) dimensions n (rows) aur m (cols) save karo
    //   2) (n+1) x (m+1) grid of zeros — 1-indexed BIT convention
    BIT2D_XOR(int n, int m)
    {
        this->n = n;
        this->m = m;
        bit.assign(n + 1, vector<ll>(m + 1, 0));
    }

    // ── update: cell (x,y) pe 'val' XOR karo ──
    //   1) nested loops: row i aur col j dono me LSB jump
    //   2) i += (i&-i) aur j += (j&-j) se saare parent cells cover hote hain
    //   3) har bit[i][j] ^= val — 2D XOR propagation
    void update(int x, int y, ll val)
    {
        for (int i = x; i <= n; i += (i & -i))
            for (int j = y; j <= m; j += (j & -j))
                bit[i][j] ^= val;
    }

    // ── prefixXOR: submatrix (1,1) to (x,y) ka XOR ──
    //   1) i = x, j = y se shuru karke (0,0) ki taraf aao
    //   2) dono loops me LSB se pichle nodes visit karo
    //   3) har bit[i][j] ko result me XOR karte jao
    ll prefixXOR(int x, int y)
    {
        ll result = 0;
        for (int i = x; i > 0; i -= (i & -i))
            for (int j = y; j > 0; j -= (j & -j))
                result ^= bit[i][j];
        return result;
    }

    // ── rangeXOR: rectangle (x1,y1) to (x2,y2) — XOR inclusion-exclusion ──
    //   1) 4 corner prefix XORs lo — 2D me sum jaisa hi pattern, bas ^ use hota hai
    //   2) P(x2,y2) main rectangle, baaki 3 extra areas cancel
    //   3) XOR associative hai isliye order matter nahi karta
    ll rangeXOR(int x1, int y1, int x2, int y2)
    {
        return prefixXOR(x2, y2) ^ prefixXOR(x1 - 1, y2) ^ prefixXOR(x2, y1 - 1) ^ prefixXOR(x1 - 1, y1 - 1);
    }

    // ── pointSet: (x,y) = newVal ──
    //   1) pehle 1x1 rangeXOR se purani cell value nikalo
    //   2) old ^ new = delta, phir update se replace karo
    void pointSet(int x, int y, ll newVal)
    {
        ll oldVal = rangeXOR(x, y, x, y);
        update(x, y, oldVal ^ newVal);
    }
};

// ── main: XOR BIT demos print karo ──
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
