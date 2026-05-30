#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ==========================
// Fenwick Tree (BIT)
// ==========================
class BIT
{
public:
    int n;
    vector<ll> bit;

    BIT(int n)
    {
        this->n = n;
        bit.assign(n + 1, 0);
    }

    void update(int i, ll x)
    {
        for (; i <= n; i += (i & -i))
            bit[i] += x;
    }

    ll sum(int i)
    {
        ll total = 0;
        for (; i > 0; i -= (i & -i))
            total += bit[i];
        return total;
    }
};
// ==========================
// Coordinate Compression Class 
// ==========================
class Coordinate_Compression
{
public:
    unordered_map<int, int> compress; // original -> compressed
    vector<int> rev_map;              // compressed -> original

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

    vector<int> get_compressed(const vector<int> &arr)
    {
        vector<int> res(arr.size());
        for (int i = 0; i < arr.size(); i++)
            res[i] = compress[arr[i]];
        return res;
    }

    int get_original(int val)
    {
        return rev_map[val];
    }
};

// ==========================
// Inversion Count using Fenwick Tree
// ==========================
ll count_Inversions(vector<int> &arr)
{
    int n = arr.size();

     Coordinate_Compression cc(arr);

    vector<int> comp = cc.get_compressed(arr);

    int m = cc.rev_map.size(); // number of unique values
    BIT bit(m);

    ll count = 0;

    for (int i = 0; i < n; i++)
    {
        // comp[i] is 0-based
        int idx = comp[i] + 1; // make it 1-based for BIT

        count += bit.sum(m) - bit.sum(idx);
        bit.update(idx, 1);
    }

    return count;
}

// ==========================
// Main
// ==========================
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
