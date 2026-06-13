#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ════════════════════════════════════════════════════════════════════════════
// SEGMENT TREE KE 3 CLASSIC VARIATIONS (sum wala seg tree)
// ────────────────────────────────────────────────────────────────────────────
// 📁 Naya split structure: types_of_segment_tree/
//    sum/ max/ min/ xor/ gcd/ — har ek me 3 files (point/range update combos)
//    Is file me sirf SUM ke teeno ek saath hain (legacy reference).
// ────────────────────────────────────────────────────────────────────────────
// Har recursive function me ye params baar baar aate hain, ek baar samajh le:
//
//   i (ya idx) -> tree array me current node ka index (root = 0)
//                 left child  = 2*i + 1
//                 right child = 2*i + 2
//   l   -> current node jis segment ka maalik hai uska LEFT  end (actual arr index)
//   r   -> current node jis segment ka maalik hai uska RIGHT end (actual arr index)
//          matlab ye node array ke [l, r] hisse ko represent karta hai
//   start/end (ya ql/qr) -> user ne jo range maangi/update ki uske left-right ends
//   mid -> (l + r) / 2, segment ko do halves me todne ka point
//
// Har query/update me 3 case hote hain node [l,r] vs query [start,end]:
//   1) NO overlap    -> node poori tarah query ke bahar  (r < start || l > end)
//   2) FULL overlap  -> node poori tarah query ke andar  (start <= l && r <= end)
//   3) PARTIAL        -> thoda andar thoda bahar -> dono bachho me recurse karo
//
// Yaha 3 variations hain:
//   1) Point Update + Range Query  -> ek index badlo, range ka sum maango (lazy nahi)
//   2) Range Update + Point Query  -> poori range me add karo, ek index ki value maango
//   3) Range Update + Range Query  -> poori range me add karo, range ka sum maango
// ════════════════════════════════════════════════════════════════════════════

// ---------------------- 1️⃣ Point Update + Range Query ----------------------
// Sabse simple variation: sum segment tree bina lazy ke.
// Ek hi index ki value set kar sakte ho, aur kisi bhi [l,r] range ka sum nikaal sakte ho.
class SegmentTree_PointUpdate_RangeQuery
{
private:
    vector<ll> segTree;  // har node pe uske segment ka SUM store hota hai
    int n;

    // ── build: array se poora segment tree banao (recursive) ──────────────────
    // Leaf (l == r) pe seedha arr[l] daal do. Warna do halves me todo,
    // dono bachho ko build karo, phir parent ka sum = left child + right child.
    void build(const vector<int> &arr, int i, int l, int r)
    {
        if (l == r)  // leaf node -> ek hi element
        {
            segTree[i] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(arr, 2 * i + 1, l, mid);      // left half
        build(arr, 2 * i + 2, mid + 1, r);  // right half
        segTree[i] = segTree[2 * i + 1] + segTree[2 * i + 2];  // sum merge
    }

    // ── update_Point: index 'idx' ki value 'val' set karo ─────────────────────
    // Root se leaf tak ek hi raasta jaata hai. idx mid ke left me hai to left
    // child me jao, warna right me. Leaf pe value set, wapsi pe sum refresh.
    void update_Point(int i, int l, int r, int idx, int val)
    {
        if (l == r)  // leaf mil gaya (yahi wo index hai)
        {
            segTree[i] = val;
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid)
            update_Point(2 * i + 1, l, mid, idx, val);
        else
            update_Point(2 * i + 2, mid + 1, r, idx, val);
        segTree[i] = segTree[2 * i + 1] + segTree[2 * i + 2];  // wapsi pe parent ka sum refresh
    }

    // ── query_Range: [start, end] range ka total sum nikaalo ──────────────────
    // No overlap -> 0 return (sum me 0 add karne se kuch farak nahi).
    // Full overlap -> seedha is node ka sum de do.
    // Partial -> dono bachho ka sum mangaao aur jod do.
    ll query_Range(int i, int l, int r, int start, int end)
    {
        if (r < start || l > end)  // Case 1: no overlap -> identity for sum
            return 0;
        if (start <= l && r <= end)  // Case 2: full overlap
            return segTree[i];
        int mid = (l + r) / 2;  // Case 3: partial -> dono taraf
        return query_Range(2 * i + 1, l, mid, start, end) + query_Range(2 * i + 2, mid + 1, r, start, end);
    }

public:
    // ── SegmentTree_PointUpdate_RangeQuery: constructor ──
    //   1) n = arr.size(), segTree vector 4*n size allocate (safe upper bound)
    //   2) Root i=0 se poori array [0, n-1] par build() call karo
    //   3) Ab point update aur range sum query dono ready hain
    SegmentTree_PointUpdate_RangeQuery(const vector<int> &arr)
    {
        n = arr.size();
        segTree.resize(4 * n);
        build(arr, 0, 0, n - 1);
    }
    // Wrapper: bahar se seedha call — root (i=0, l=0, r=n-1) khud set
    void update_Point(int idx, int val) { update_Point(0, 0, n - 1, idx, val); }
    ll query_Range(int l, int r) { return query_Range(0, 0, n - 1, l, r); }
};

// ---------------------- 2️⃣ Range Update + Point Query ----------------------
// Lazy propagation use hota hai: poori range [l,r] me ek saath add kar sakte ho,
// aur kisi bhi single index ki current value maang sakte ho.
class SegmentTree_RangeUpdate_PointQuery
{
private:
    vector<ll> segTree, lazy;  // segTree = sum, lazy = pending add jo bachho tak nahi pahuncha
    int n;

    // ── build: same sum tree banao (lazy yaha 0 hi rehta hai shuru me) ─────────
    void build(const vector<int> &arr, int i, int l, int r)
    {
        if (l == r)  // leaf -> ek element
        {
            segTree[i] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(arr, 2 * i + 1, l, mid);
        build(arr, 2 * i + 2, mid + 1, r);
        segTree[i] = segTree[2 * i + 1] + segTree[2 * i + 2];  // sum merge
    }

    // ── push: node 'i' pe pada pending lazy apply karo ────────────────────────
    // segTree[i] me add karo lazy * (segment ka size = r-l+1).
    // Agar leaf nahi hai to wahi lazy dono bachho ke lazy me daal do (taaki baad
    // me wo apply ho). Ant me apna lazy 0 kar do kyunki ab apply ho chuka.
    void push(int i, int l, int r)
    {
        if (lazy[i] != 0)
        {
            segTree[i] += (r - l + 1) * lazy[i];  // poore segment me add hua
            if (l != r)  // leaf nahi -> bachho ko lazy pass karo
            {
                lazy[2 * i + 1] += lazy[i];
                lazy[2 * i + 2] += lazy[i];
            }
            lazy[i] = 0;  // apna pending clear
        }
    }

    // ── update_Range: [start, end] ke har element me 'val' add karo ───────────
    // Pehle apna pending lazy apply karo (push).
    // No overlap -> kuch mat karo. Full overlap -> lazy[i] me val daalo aur turant
    // push karke apply kar do. Partial -> dono bachho me recurse.
    // NOTE: yaha point-query variant hai isliye wapsi pe sum refresh nahi karte
    //       (kyunki hume sum nahi, sirf point value chahiye).
    void update_Range(int i, int l, int r, int start, int end, int val)
    {
        push(i, l, r);
        if (r < start || l > end)  // no overlap
            return;
        if (start <= l && r <= end)  // full overlap
        {
            lazy[i] += val;
            push(i, l, r);  // turant apply
            return;
        }
        int mid = (l + r) / 2;  // partial
        update_Range(2 * i + 1, l, mid, start, end, val);
        update_Range(2 * i + 2, mid + 1, r, start, end, val);
    }

    // ── query_Point: index 'idx' ki current value kya hai ─────────────────────
    // Root se leaf tak jao, raaste me push karte jao taaki saara pending lazy
    // apply ho jaaye. Leaf pe jo sum (single element) bacha wahi answer hai.
    ll query_Point(int i, int l, int r, int idx)
    {
        push(i, l, r);
        if (l == r)  // leaf -> yahi value chahiye thi
            return segTree[i];
        int mid = (l + r) / 2;
        if (idx <= mid)
            return query_Point(2 * i + 1, l, mid, idx);
        else
            return query_Point(2 * i + 2, mid + 1, r, idx);
    }

public:
    // ── SegmentTree_RangeUpdate_PointQuery: constructor ──
    //   1) n = arr.size(), segTree aur lazy dono 4*n size allocate
    //   2) lazy ko 0 se init karo — shuru me koi pending add nahi
    //   3) build() se initial array values tree me daal do
    SegmentTree_RangeUpdate_PointQuery(const vector<int> &arr)
    {
        n = arr.size();
        segTree.resize(4 * n);
        lazy.assign(4 * n, 0);
        build(arr, 0, 0, n - 1);
    }
    void update_Range(int l, int r, int val) { update_Range(0, 0, n - 1, l, r, val); }
    ll query_Point(int idx) { return query_Point(0, 0, n - 1, idx); }
};

// ---------------------- 3️⃣ Range Update + Range Query ----------------------
// Sabse powerful variation: lazy propagation ke saath poori range me add bhi
// kar sakte ho aur poori range ka sum bhi maang sakte ho. (Variation 2 jaisa
// hi, bas yaha update aur query dono me wapsi pe sum refresh hota hai.)
class SegmentTree_RangeUpdate_RangeQuery
{
private:
    vector<ll> segTree, lazy;  // segTree = sum, lazy = pending add
    int n;

    // ── build: array se sum tree banao ───────────────────────────────────────
    void build(const vector<int> &arr, int i, int l, int r)
    {
        if (l == r)  // leaf
        {
            segTree[i] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(arr, 2 * i + 1, l, mid);
        build(arr, 2 * i + 2, mid + 1, r);
        segTree[i] = segTree[2 * i + 1] + segTree[2 * i + 2];  // sum merge
    }

    // ── push: pending lazy ko khud pe apply karo aur bachho tak pass karo ─────
    // segment ka size (r-l+1) se multiply karke sum me add karte hain.
    void push(int i, int l, int r)
    {
        if (lazy[i] != 0)
        {
            segTree[i] += (r - l + 1) * lazy[i];  // poore segment me lazy add
            if (l != r)  // leaf nahi -> bachho ko lazy do
            {
                lazy[2 * i + 1] += lazy[i];
                lazy[2 * i + 2] += lazy[i];
            }
            lazy[i] = 0;  // pending clear
        }
    }

    // ── update_Range: [start, end] me 'val' add karo ──────────────────────────
    // No overlap -> skip. Full overlap -> lazy lagao + push. Partial -> dono
    // bachho me recurse. Yaha (variation 2 se alag) wapsi pe parent ka sum
    // refresh karte hain kyunki aage range-sum query bhi karni hai.
    void update_Range(int i, int l, int r, int start, int end, int val)
    {
        push(i, l, r);
        if (r < start || l > end)  // no overlap
            return;
        if (start <= l && r <= end)  // full overlap
        {
            lazy[i] += val;
            push(i, l, r);  // turant apply
            return;
        }
        int mid = (l + r) / 2;  // partial
        update_Range(2 * i + 1, l, mid, start, end, val);
        update_Range(2 * i + 2, mid + 1, r, start, end, val);
        push(2 * i + 1, l, mid);
        push(2 * i + 2, mid + 1, r);
        segTree[i] = segTree[2 * i + 1] + segTree[2 * i + 2];  // bacche badle -> sum refresh
    }

    // ── query_Range: [start, end] ka sum nikaalo (lazy apply karte hue) ───────
    // Pehle push (taaki current node ki value sahi ho). No overlap -> 0,
    // full overlap -> node ka sum, partial -> dono bachho ka sum jodo.
    ll query_Range(int i, int l, int r, int start, int end)
    {
        push(i, l, r);
        if (r < start || l > end)  // no overlap -> identity for sum
            return 0;
        if (start <= l && r <= end)  // full overlap
            return segTree[i];
        int mid = (l + r) / 2;  // partial
        return query_Range(2 * i + 1, l, mid, start, end) + query_Range(2 * i + 2, mid + 1, r, start, end);
    }

public:
    // ── SegmentTree_RangeUpdate_RangeQuery: constructor ──
    //   1) n = arr.size(), segTree + lazy dono 4*n size allocate
    //   2) lazy 0 se init — abhi koi pending range-add nahi
    //   3) build() se sum tree ready karo — range update + range query dono chalenge
    SegmentTree_RangeUpdate_RangeQuery(const vector<int> &arr)
    {
        n = arr.size();
        segTree.resize(4 * n);
        lazy.assign(4 * n, 0);
        build(arr, 0, 0, n - 1);
    }
    void update_Range(int l, int r, int val) { update_Range(0, 0, n - 1, l, r, val); }
    ll query_Range(int l, int r) { return query_Range(0, 0, n - 1, l, r); }
};

// ---------------------- Main function ----------------------
// Teeno variations ko ek hi array pe try karke output dikhata hai
int main()
{
    vector<int> arr = {5, 3, 8, 6, 1, 4, 7, 9, 2, 0};

    // Variation 1: ek index update karke alag alag range ka sum
    cout << "---- 1️⃣ Point Update + Range Query ----\n";
    SegmentTree_PointUpdate_RangeQuery st1(arr);
    st1.update_Point(2, 10); // arr[2]=10 set kar diya
    cout << "Sum [0,4]: " << st1.query_Range(0, 4) << endl;
    cout << "Sum [2,6]: " << st1.query_Range(2, 6) << endl;

    // Variation 2: do overlapping range updates, phir single index ki value
    cout << "\n---- 2️⃣ Range Update + Point Query ----\n";
    SegmentTree_RangeUpdate_PointQuery st2(arr);
    st2.update_Range(2, 6, 5);   // [2,6] me +5
    st2.update_Range(0, 4, 10);  // [0,4] me +10 (index 2-4 dono se affected)
    cout << "Value at index 2: " << st2.query_Point(2) << endl;
    cout << "Value at index 5: " << st2.query_Point(5) << endl;

    // Variation 3: range updates ke baad range sum
    cout << "\n---- 3️⃣ Range Update + Range Query ----\n";
    SegmentTree_RangeUpdate_RangeQuery st3(arr);
    st3.update_Range(2, 6, 5);   // [2,6] me +5
    st3.update_Range(0, 4, 10);  // [0,4] me +10
    cout << "Sum [0,4]: " << st3.query_Range(0, 4) << endl;
    cout << "Sum [2,6]: " << st3.query_Range(2, 6) << endl;

    return 0;
}
