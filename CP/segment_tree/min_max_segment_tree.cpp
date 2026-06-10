#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// MIN-MAX SEGMENT TREE (with Lazy Propagation for Range Add)
// ────────────────────────────────────────────────────────────────────────────
// Har recursive function me 5 cheezein common hoti hain, inhe samajh le ek baar:
//
//   i   -> tree array me current node ka index (root = 0)
//          left child  = 2*i + 1
//          right child = 2*i + 2
//   l   -> current node jis segment ko cover karta hai uska LEFT  end  (actual array index)
//   r   -> current node jis segment ko cover karta hai uska RIGHT end  (actual array index)
//          matlab ye node array ke [l, r] hisse ka maalik hai
//   ql  -> QUERY ka left end  (user ne jo range maangi/update ki uska start)
//   qr  -> QUERY ka right end (user ne jo range maangi/update ki uska end)
//
// Har baar 3 case hote hain node [l,r] vs query [ql,qr]:
//   1) NO overlap    -> node poori tarah query ke bahar  (r < ql || l > qr)
//   2) FULL overlap  -> node poori tarah query ke andar  (ql <= l && r <= qr)
//   3) PARTIAL        -> thoda andar thoda bahar -> dono bachho me recurse karo
// ════════════════════════════════════════════════════════════════════════════

class SegmentTree
{
public:
    int n;
    vector<int> mini_segtree;  // har node pe uske segment ka MINIMUM
    vector<int> maxi_segtree;  // har node pe uske segment ka MAXIMUM
    vector<int> lazy;          // pending add jo abhi tak bachho tak nahi pahuncha

    // ── SegmentTree: tree initialize karo ──
    //   1) n store karo — kitne elements ka tree banana hai
    //   2) mini_segtree, maxi_segtree, lazy teeno ko size 4*n se banao (safe padding)
    //   3) sab nodes 0 se start — abhi koi value/lazy pending nahi hai
    SegmentTree(int _n)
    {
        n = _n;
        mini_segtree.assign(4 * n, 0);
        maxi_segtree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
    }

    // ── push: pending lazy ko apply karo ──
    //   1) agar lazy[i] == 0 hai to kuch pending nahi — seedha return
    //   2) mini/max dono me lazy[i] add karo (range add se har element badhta hai)
    //   3) agar leaf nahi (l != r) to wahi lazy bachho ke lazy me += karo
    //   4) apna lazy[i] = 0 kar do — ab ye node up-to-date hai, pending clear
    void push(int i, int l, int r)
    {
        if (lazy[i] != 0)
        {
            mini_segtree[i] += lazy[i];
            maxi_segtree[i] += lazy[i];

            if (l != r)  // internal node — lazy niche bachho tak defer karo
            {
                lazy[2 * i + 1] += lazy[i];
                lazy[2 * i + 2] += lazy[i];
            }
            lazy[i] = 0;  // is node ka pending ab apply ho chuka
        }
    }

    // ── range_update: [ql,qr] me val add karo (recursive) ──
    //   1) pehle push(i,l,r) — is node pe purana pending apply karo
    //   2) Case 1 NO overlap (r<ql || l>qr) — ye subtree query ke bahar, return
    //   3) Case 2 FULL overlap (ql<=l && r<=qr) — lazy[i]+=val, push, return
    //   4) Case 3 PARTIAL — mid split, dono bachho me recurse, parent min/max refresh
    void range_update(int ql, int qr, int i, int l, int r, int val)
    {
        push(i, l, r);

        if (r < ql || l > qr)  // Case 1: NO overlap — koi element match nahi
            return;

        if (ql <= l && r <= qr)  // Case 2: FULL overlap — poora segment update range ke andar
        {
            lazy[i] += val;       // abhi niche nahi jaate, pending me daal do
            push(i, l, r);        // turant apply taaki is node ka min/max sahi rahe
            return;
        }

        // Case 3: PARTIAL overlap — segment ka sirf kuch hissa query me aata hai
        int mid = (l + r) / 2;
        range_update(ql, qr, 2 * i + 1, l, mid, val);
        range_update(ql, qr, 2 * i + 2, mid + 1, r, val);

        // bachhe badle — parent ka aggregated min/max dobara banao
        mini_segtree[i] = min(mini_segtree[2 * i + 1], mini_segtree[2 * i + 2]);
        maxi_segtree[i] = max(maxi_segtree[2 * i + 1], maxi_segtree[2 * i + 2]);
    }

    // ── point_update: ek index idx pe val add karo ──
    //   1) push karo taaki raaste ke saare pending lazy clear ho jaayein
    //   2) l==r matlab leaf mil gaya — seedha mini/max me val add karo, return
    //   3) idx <= mid ho to left child me jao, warna right child me
    //   4) wapas aate waqt parent ka min/max bachho se refresh karo
    void point_update(int idx, int i, int l, int r, int val)
    {
        push(i, l, r);

        if (l == r)  // leaf node — yahi wo exact index hai
        {
            mini_segtree[i] += val;
            maxi_segtree[i] += val;
            return;
        }

        int mid = (l + r) / 2;
        if (idx <= mid)
            point_update(idx, 2 * i + 1, l, mid, val);
        else
            point_update(idx, 2 * i + 2, mid + 1, r, val);

        mini_segtree[i] = min(mini_segtree[2 * i + 1], mini_segtree[2 * i + 2]);
        maxi_segtree[i] = max(maxi_segtree[2 * i + 1], maxi_segtree[2 * i + 2]);
    }

    // ── min_query: [ql,qr] ka minimum nikalo ──
    //   1) push pehle — warna lazy pending ki wajah se purana min milega
    //   2) Case 1 NO overlap — INT_MAX return (min identity, merge me ignore hota)
    //   3) Case 2 FULL overlap — seedha mini_segtree[i] return, aur recurse nahi
    //   4) Case 3 PARTIAL — left/right dono ka min lo, unme se chhota return karo
    int min_query(int ql, int qr, int i, int l, int r)
    {
        push(i, l, r);

        if (r < ql || l > qr)  // Case 1: NO overlap
            return INT_MAX;

        if (ql <= l && r <= qr)  // Case 2: FULL overlap
            return mini_segtree[i];

        int mid = (l + r) / 2;  // Case 3: PARTIAL overlap
        return min(
            min_query(ql, qr, 2 * i + 1, l, mid),
            min_query(ql, qr, 2 * i + 2, mid + 1, r));
    }

    // ── max_query: [ql,qr] ka maximum nikalo ──
    //   1) push pehle — pending lazy apply karo warna max galat aayega
    //   2) Case 1 NO overlap — INT_MIN return (max identity)
    //   3) Case 2 FULL overlap — seedha maxi_segtree[i] return karo
    //   4) Case 3 PARTIAL — dono bachho ka max lo, unka overall max return karo
    int max_query(int ql, int qr, int i, int l, int r)
    {
        push(i, l, r);

        if (r < ql || l > qr)  // Case 1: NO overlap
            return INT_MIN;

        if (ql <= l && r <= qr)  // Case 2: FULL overlap
            return maxi_segtree[i];

        int mid = (l + r) / 2;  // Case 3: PARTIAL overlap
        return max(
            max_query(ql, qr, 2 * i + 1, l, mid),
            max_query(ql, qr, 2 * i + 2, mid + 1, r));
    }

    // ── point_query: index idx ki value lao ──
    //   1) har level pe push — raaste ka saara pending lazy leaf tak pahuncha do
    //   2) l==r pe leaf — mini_segtree[i] hi actual value hai (min=max ek element pe)
    //   3) idx left half me hai to left recurse, warna right recurse
    //   4) leaf tak pohoch ke value return — koi merge nahi chahiye
    int point_query(int idx, int i, int l, int r)
    {
        push(i, l, r);

        if (l == r)  // leaf — target index mil gaya
            return mini_segtree[i];

        int mid = (l + r) / 2;
        if (idx <= mid)
            return point_query(idx, 2 * i + 1, l, mid);
        else
            return point_query(idx, 2 * i + 2, mid + 1, r);
    }

    // ════════════════════════════════════════════════════════════════════════
    // WRAPPERS: bahar se seedha inhe call karo, i/l/r khud set ho jaata hai
    //           (har baar root se start: i=0, l=0, r=n-1)
    // ════════════════════════════════════════════════════════════════════════

    // ── range_update: public wrapper — root se range add shuru karo ──
    //   1) user sirf [l,r] aur val deta hai
    //   2) andar wale recursive call me i=0, l=0, r=n-1 pass hota hai
    void range_update(int l, int r, int val)
    {
        range_update(l, r, 0, 0, n - 1, val);
    }

    // ── point_update: public wrapper — ek index pe add ──
    //   1) idx aur val lo, root node (i=0) se recursion start karo
    //   2) poora segment [0, n-1] context automatically set ho jaata hai
    void point_update(int idx, int val)
    {
        point_update(idx, 0, 0, n - 1, val);
    }

    // ── rangeMin: [l,r] minimum ka public entry point ──
    //   1) min_query ko root (i=0) aur full array bounds se call karo
    //   2) andar 3-case logic + lazy push handle hota hai
    int rangeMin(int l, int r)
    {
        return min_query(l, r, 0, 0, n - 1);
    }

    // ── rangeMax: [l,r] maximum ka public entry point ──
    //   1) max_query ko root se start karo
    //   2) result directly return — user ko i/l/r yaad rakhne ki zarurat nahi
    int rangeMax(int l, int r)
    {
        return max_query(l, r, 0, 0, n - 1);
    }

    // ── get_val: single index ki value lao ──
    //   1) point_query root se call — leaf tak jake exact value return
    //   2) raaste me saare lazy push ho jaate hain, isliye answer updated hota hai
    int get_val(int idx)
    {
        return point_query(idx, 0, 0, n - 1);
    }
};

int main()
{
    // ---- Hard coded test cases ----

    int n = 8;
    SegmentTree seg(n);

    cout << "Initially all values are 0\n\n";

    // add 5 to range [2,6]
    seg.range_update(2, 6, 5);
    cout << "After range_update(2, 6, 5)\n";

    cout << "Min [0,7] = " << seg.rangeMin(0, 7) << "\n";
    cout << "Max [0,7] = " << seg.rangeMax(0, 7) << "\n\n";

    // add -3 to range [4,7]
    seg.range_update(4, 7, -3);
    cout << "After range_update(4, 7, -3)\n";

    cout << "Min [0,7] = " << seg.rangeMin(0, 7) << "\n";
    cout << "Max [0,7] = " << seg.rangeMax(0, 7) << "\n\n";

    // add 10 to range [0,3]
    seg.range_update(0, 3, 10);
    cout << "After range_update(0, 3, 10)\n";

    cout << "Min [0,7] = " << seg.rangeMin(0, 7) << "\n";
    cout << "Max [0,7] = " << seg.rangeMax(0, 7) << "\n\n";

    // point update: index 5 pe +100 add karo
    seg.point_update(5, 100);
    cout << "After point_update(5, +100)\n";
    cout << "Point[5]  = " << seg.get_val(5) << "\n";
    cout << "Max [0,7] = " << seg.rangeMax(0, 7) << "\n\n";

    cout << "Point values:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "index " << i << " -> " << seg.get_val(i) << "\n";
    }

    cout << "\nSome sub-range queries:\n";
    cout << "Min [2,5] = " << seg.rangeMin(2, 5) << "\n";
    cout << "Max [2,5] = " << seg.rangeMax(2, 5) << "\n";

    return 0;
}
