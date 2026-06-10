#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ════════════════════════════════════════════════════════════════════════════
// INVERSION COUNT — Fenwick Tree + Coordinate Compression
// ────────────────────────────────────────────────────────────────────────────
// Idea: left se right scan karo. Har element ke liye:
//   "mere se pehle kitne MERE SE BADE elements aaye?" = total - count<=me
// BIT me frequencies store karte hain compressed indices pe.
// ════════════════════════════════════════════════════════════════════════════

class BIT
{
public:
    int n;
    vector<ll> bit;

    // ── BIT: frequency BIT initialize ──
    //   1) n = compressed value range size
    //   2) bit size n+1, 1-indexed
    BIT(int n)
    {
        this->n = n;
        bit.assign(n + 1, 0);
    }

    // ── update: index 'i' pe 'x' add karo ──
    //   1) i se n tak har BIT node pe x add (frequency increment)
    //   2) i += (i & -i) — LSB jump se parent nodes update
    void update(int i, ll x)
    {
        for (; i <= n; i += (i & -i))  // i & -i = lowest set bit
            bit[i] += x;
    }

    // ── sum: [1, i] ka prefix sum (kitne elements <= compressed index i-1) ──
    //   1) total = 0, i > 0 tak loop
    //   2) bit[i] add karo — cumulative frequency count
    //   3) i -= (i & -i) se pichla node
    //   4) sum(idx) = kitne processed elements ki compressed value < idx
    ll sum(int i)
    {
        ll total = 0;
        for (; i > 0; i -= (i & -i))
            total += bit[i];
        return total;
    }
};

// ── Coordinate_Compression: bade values ko 0..K-1 me map karo ──
class Coordinate_Compression
{
public:
    unordered_map<int, int> compress;
    vector<int> rev_map;

    // ── Coordinate_Compression: unique values compress karo ──
    //   1) array ke unique values set me daalo (auto sorted)
    //   2) har unique value ko 0, 1, 2, ... id do
    //   3) compress map: original -> id, rev_map: id -> original
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

    // ── get_compressed: poori array ko compressed indices me convert ──
    //   1) har element arr[i] ka compress[arr[i]] nikalo
    //   2) result vector same size, 0-based compressed ids
    vector<int> get_compressed(const vector<int> &arr)
    {
        vector<int> res(arr.size());
        for (int i = 0; i < (int)arr.size(); i++)
            res[i] = compress[arr[i]];
        return res;
    }

    // ── get_original: compressed id se original value ──
    //   1) rev_map[val] return — reverse lookup
    int get_original(int val)
    {
        return rev_map[val];
    }
};

// ── count_Inversions: BIT se inversion count ──
//   1) coordinate compression karo — values ko 0..m-1 me map
//   2) left se right scan: har element ke liye pehle se kitne bade aaye?
//   3) count += sum(m) - sum(idx) — total processed minus <= current
//   4) current element ko BIT me +1 frequency daal do
ll count_Inversions(vector<int> &arr)
{
    int n = arr.size();

    Coordinate_Compression cc(arr);
    vector<int> comp = cc.get_compressed(arr);

    int m = cc.rev_map.size();
    BIT bit(m);

    ll count = 0;

    for (int i = 0; i < n; i++)
    {
        int idx = comp[i] + 1;  // 1-indexed for BIT (compressed value + 1)

        count += bit.sum(m) - bit.sum(idx);  // total seen - <= current = greater than current
        bit.update(idx, 1);                   // current element BIT me daal do
    }

    return count;
}

// ── main: multiple test arrays pe inversion count ──
int main()
{
    vector<vector<int>> tests = {
        {8, 4, 2, 1},
        {3, 1, 2},
        {1, 20, 6, 4, 5},
        {10, 9, 8, 7, 6, 5},
        {1, 2, 3, 4, 5},
        {1000000, 999999, 2, 1, 5000},
        {5, 3, 5, 1, 3}};

    for (auto &arr : tests)
    {
        cout << "Array: ";
        for (int x : arr)
            cout << x << " ";
        cout << "\nInversions = " << count_Inversions(arr) << "\n\n";
    }

    return 0;
}
