// Count of numbers in an array greater than x using Fenwick Tree (Binary Indexed Tree)
// This code is total - count of numbers less than or equal to x
// Leetcode question reference: https://leetcode.com/problems/count-of-smaller-numbers-after-self/
// count > x  == total - count <= x
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class Coordinate_Compression
{
public:
    unordered_map<int, int> compress; // original value -> compressed value
    vector<int> rev_map;              // compressed value -> original value

    Coordinate_Compression(const vector<int> &arr)
    {
        set<int> st(arr.begin(), arr.end()); // unique & sorted
        int id = 0;
        for (int x : st)
        {
            compress[x] = id; // 0-based
            rev_map.push_back(x);
            id++;
        }
    }

    vector<int> get_compressed(const vector<int> &arr)
    {
        vector<int> res(arr.size());
        for (int i = 0; i < (int)arr.size(); i++)
            res[i] = compress[arr[i]];
        return res;
    }

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

    Fenwick_Tree(int n)
    {
        this->n = n;
        bit.assign(n + 1, 0);
    }

    void update(int i, ll x)
    {
        for (; i <= n; i += (i & -i))
            bit[i] += x;
    }

    ll sum_query(int i)
    {
        ll total = 0;
        for (; i > 0; i -= (i & -i))
            total += bit[i];
        return total;
    }
};

int main()
{
    vector<int> arr = {5, 1, 3, 3, 10, 7};

    int x;
    cin >> x; // query value

    Coordinate_Compression cc(arr);

    int K = cc.rev_map.size();
    Fenwick_Tree bit(K);

    // insert all elements into BIT (frequency)
    for (int v : arr)
    {
        int id = cc.compress[v]; // 0-based
        bit.update(id + 1, 1);   // BIT is 1-based
    }

    // count how many elements are <= x
    int pos = upper_bound(cc.rev_map.begin(),
                          cc.rev_map.end(),
                          x) -
              cc.rev_map.begin();

    ll total = bit.sum_query(K);
    ll le_x = bit.sum_query(pos);
    ll greater = total - le_x;

    cout << "Elements > " << x << " = " << greater << "\n";

    return 0;
}
