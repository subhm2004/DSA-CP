// Count of numbers in array GREATER than x using Fenwick Tree
// Formula: count > x  ==  total - count <= x
// Leetcode ref: https://leetcode.com/problems/count-of-smaller-numbers-after-self/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ════════════════════════════════════════════════════════════════════════════
// COUNT ELEMENTS > x — BIT + Coordinate Compression
// ────────────────────────────────────────────────────────────────────────────
// Steps: values compress karo -> BIT me frequencies daalo ->
//        sum(pos) se <= x count -> total - le_x = > x count
// ════════════════════════════════════════════════════════════════════════════

class Coordinate_Compression
{
public:
    unordered_map<int, int> compress;
    vector<int> rev_map;

    // ── Coordinate_Compression: unique sorted values ko 0..K-1 me map karo ──
    //   1) array ke saare unique values set me daalo — auto sorted order
    //   2) har unique value ko sequential id (0, 1, 2, ...) do
    //   3) compress: value -> id, rev_map: id -> value (reverse lookup)
    Coordinate_Compression(const vector<int> &arr)
    {
        set<int> st(arr.begin(), arr.end());
        int id = 0;
        for (int x : st)
        {
            compress[x] = id;
            rev_map.push_back(x);
            id++;
        }
    }

    // ── get_compressed: array elements ko compressed ids me convert ──
    //   1) har arr[i] ke liye compress[arr[i]] lookup karo
    //   2) result vector same length, 0-based compressed indices
    vector<int> get_compressed(const vector<int> &arr)
    {
        vector<int> res(arr.size());
        for (int i = 0; i < (int)arr.size(); i++)
            res[i] = compress[arr[i]];
        return res;
    }

    // ── get_original: compressed id se original value wapas ──
    //   1) rev_map[val] return karo
    int get_original(int val)
    {
        return rev_map[val];
    }
};

class Fenwick_Tree
{
public:
    int n;
    vector<ll> bit;

    // ── Fenwick_Tree: frequency BIT setup ──
    //   1) n = number of unique compressed values
    //   2) bit size n+1, 1-indexed BIT convention
    Fenwick_Tree(int n)
    {
        this->n = n;
        bit.assign(n + 1, 0);
    }

    // ── update: compressed index 'i' pe frequency +1 ──
    //   1) i se n tak har BIT node pe x add karo
    //   2) i += (i & -i) — LSB jump, parent nodes update
    void update(int i, ll x)
    {
        for (; i <= n; i += (i & -i))  // i & -i = lowest set bit
            bit[i] += x;
    }

    // ── sum_query: [1, i] me kitne elements (prefix frequency count) ──
    //   1) total = 0, i > 0 tak loop
    //   2) bit[i] add karo — cumulative count of values with compressed id < i
    //   3) i -= (i & -i) se pichla covered prefix node
    ll sum_query(int i)
    {
        ll total = 0;
        for (; i > 0; i -= (i & -i))
            total += bit[i];
        return total;
    }
};

// ── main: count elements > x using BIT ──
//   1) array compress karo, saari frequencies BIT me daalo
//   2) upper_bound se x se <= kitne unique positions hain nikalo
//   3) total - le_x = greater than x count print karo
int main()
{
    vector<int> arr = {5, 1, 3, 3, 10, 7};

    int x;
    cin >> x;

    Coordinate_Compression cc(arr);

    int K = cc.rev_map.size();
    Fenwick_Tree bit(K);

    // saare elements ki frequency BIT me daal do
    for (int v : arr)
    {
        int id = cc.compress[v];
        bit.update(id + 1, 1);  // 1-indexed BIT: compressed id + 1
    }

    // x se chhote/equal kitne unique positions hain
    int pos = upper_bound(cc.rev_map.begin(),
                          cc.rev_map.end(),
                          x) -
              cc.rev_map.begin();  // rev_map sorted hai — pos = count of values <= x

    ll total = bit.sum_query(K);   // poori array ki total count
    ll le_x = bit.sum_query(pos);  // values <= x ki count (compressed prefix)
    ll greater = total - le_x;       // > x = total - <= x

    cout << "Elements > " << x << " = " << greater << "\n";

    return 0;
}
