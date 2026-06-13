#include <bits/stdc++.h>
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * OPERATION : XOR
 * VARIATION : Range Update + Range Query
 * LAZY      : YES (range XOR flip + parent refresh on partial update)
 * COMPLEXITY: build O(n) | range update O(log n) | range query O(log n)
 * ════════════════════════════════════════════════════════════════════════════
 * Range me ^= flip karo aur range ka XOR bhi maango.
 * Odd-length lazy rule apply hota hai; partial update pe parent XOR refresh karo.
 * ════════════════════════════════════════════════════════════════════════════
 */

class XorSeg_RangeUpdate_RangeQuery
{
private:
    vector<int> segTree, lazyXor; // segTree = segment XOR, lazy = pending XOR flip
    int n;

    // Har recursive function me ye params baar baar aate hain, ek baar samajh le:
    //
    //   i (ya node) -> tree array me current node ka index (root = 0)
    //                  left child  = 2*i + 1
    //                  right child = 2*i + 2
    //   l, r   -> current node ka segment [l, r] (actual array indices)
    //   start, end -> user ne jo range update/query maangi uske left-right ends
    //   mid -> (l + r) / 2, segment ko do halves me todne ka point
    //   val/v -> range update me har element par ^= karne ki value
    //
    // Har range op me 3 case hote hain node [l,r] vs range [start,end]:
    //   1) NO overlap    -> skip ya 0 return (query me)
    //   2) FULL overlap  -> apply() ya segTree[i] return
    //   3) PARTIAL       -> dono bachho me recurse
    //
    // XOR lazy rule (SUM se alag):
    //   segTree[i] ^= v  SIRF jab segment length ODD ho
    //   lazyXor[i] ^= v     HAMESHA (pending flip bachho tak pass)

    // ── build: array se XOR tree banao ──────────────────────────────────────
    // Params: arr = input array, i = current node, l/r = segment bounds
    // Steps:
    //   1) Agar l == r (leaf) → segTree[i] = arr[l], return
    //   2) mid nikalo, left aur right child recursively build karo
    //   3) Parent XOR = left child XOR ^ right child XOR
    void build(const vector<int> &arr, int i, int l, int r)
    {
        if (l == r)
        {
            segTree[i] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(arr, 2 * i + 1, l, mid);
        build(arr, 2 * i + 2, mid + 1, r);
        segTree[i] = segTree[2 * i + 1] ^ segTree[2 * i + 2];
    }

    // ── apply: RANGE XOR update lagao (push isse call karta hai) ────────────
    //   lazy UPDATE type = XOR flip (^=v) | merge (query) = ^ alag cheez hai
    //   1) len = r-l+1
    //   2) len ODD → segTree[i] ^= v   (odd flips = v, even = 0)
    //   3) lazyXor[i] ^= v HAMESHA     (pending flip store)
    void apply(int i, int l, int r, int v)
    {
        int len = r - l + 1;
        if (len & 1)
        {
            segTree[i] ^= v;
        }
        lazyXor[i] ^= v;
    }

    // ── push: LAZY UPDATE = RANGE XOR (^=v) | MERGE (query) = ^ ─────────────
    //   ⚠️ push me merge (^) NAHI lagta seedha — apply() odd-length rule use karta hai!
    //   lazyXor[i] = pending XOR flip sab elements par
    //   1) lazyXor[i] == 0 → return
    //   2) apply(left child, lazyXor[i])  — odd len pe segTree ^= v
    //   3) apply(right child, lazyXor[i]) — lazyXor child ^= v hamesha
    //   4) lazyXor[i] = 0
    void push(int i, int l, int r)
    {
        if (lazyXor[i] == 0)
        {
            return;
        }
        int mid = (l + r) / 2;
        apply(2 * i + 1, l, mid, lazyXor[i]);
        apply(2 * i + 2, mid + 1, r, lazyXor[i]);
        lazyXor[i] = 0;
    }

    // ── update_Range: [start, end] ^= val, partial pe parent XOR refresh ────
    // Params: i = current node, l/r = node segment, start/end = update range, val = flip
    // Steps:
    //   1) push(i,l,r) — pehle apna pending lazy apply karo
    //   2) NO overlap → return
    //   3) FULL overlap → apply(i,l,r,val), return
    //   4) PARTIAL → dono bachho me recurse
    //   5) Wapas aate waqt parent XOR refresh: left ^ right
    //      (range query bhi karni hai isliye parent update zaroori hai — variation 2 se alag)
    void update_Range(int i, int l, int r, int start, int end, int val)
    {
        push(i, l, r);
        if (r < start || l > end)
        {
            return;
        }
        if (start <= l && r <= end)
        {
            apply(i, l, r, val);
            return;
        }
        int mid = (l + r) / 2;
        update_Range(2 * i + 1, l, mid, start, end, val);
        update_Range(2 * i + 2, mid + 1, r, start, end, val);
        push(2 * i + 1, l, mid);
        push(2 * i + 2, mid + 1, r);
        segTree[i] = segTree[2 * i + 1] ^ segTree[2 * i + 2];
    }

    // ── query_Range: [start, end] ka XOR nikaalo (lazy apply karte hue) ───────
    // Params: i = current node, l/r = node segment, start/end = query range
    // Steps:
    //   1) push(i,l,r) — current node ki value sahi karo
    //   2) NO overlap → 0 return (XOR identity)
    //   3) FULL overlap → segTree[i] return
    //   4) PARTIAL → dono bachho se XOR mangaao, ^ karke jodo
    int query_Range(int i, int l, int r, int start, int end)
    {
        push(i, l, r);
        if (r < start || l > end)
        {
            return 0;
        }
        if (start <= l && r <= end)
        {
            return segTree[i];
        }
        int mid = (l + r) / 2;
        return query_Range(2 * i + 1, l, mid, start, end)
             ^ query_Range(2 * i + 2, mid + 1, r, start, end);
    }

public:
    // ── XorSeg_RangeUpdate_RangeQuery: constructor ──────────────────────────
    // Params: arr = initial array
    // Steps:
    //   1) n = arr.size(), segTree + lazy dono 4*n size allocate
    //   2) lazy 0 se init — abhi koi pending range XOR flip nahi
    //   3) build() se XOR tree ready — range update + range query dono chalenge
    XorSeg_RangeUpdate_RangeQuery(const vector<int> &arr)
    {
        n = (int)arr.size();
        segTree.assign(4 * max(n, 1), 0);
        lazyXor.assign(4 * max(n, 1), 0);
        if (n > 0)
        {
            build(arr, 0, 0, n - 1);
        }
    }

    // ── update_Range: public wrapper — bahar se seedha range XOR flip ───────
    // Params: l, r = update range, val = har element par ^= value
    void update_Range(int l, int r, int val)
    {
        update_Range(0, 0, n - 1, l, r, val);
    }

    // ── query_Range: public wrapper — bahar se seedha range XOR query ───────
    // Params: l, r = query range [l, r] inclusive
    int query_Range(int l, int r)
    {
        return query_Range(0, 0, n - 1, l, r);
    }
};

int main()
{
    vector<int> arr = {1, 2, 3, 4, 5};

    cout << "---- XOR | Range Update + Range Query ----\n";
    XorSeg_RangeUpdate_RangeQuery st(arr);
    cout << "Initial XOR(0,4): " << st.query_Range(0, 4) << endl;

    st.update_Range(0, 2, 10);
    cout << "After [0,2] ^= 10, XOR(0,2): " << st.query_Range(0, 2) << endl;
    cout << "XOR(0,4): " << st.query_Range(0, 4) << endl;

    return 0;
}
