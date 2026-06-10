// Leetcode 315: Count of Smaller Numbers After Self
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ════════════════════════════════════════════════════════════════════════════
// LEETCODE 315 — Har index ke right me kitne chhote elements hain
// ────────────────────────────────────────────────────────────────────────────
// Approach: RIGHT se LEFT scan + BIT (frequency of seen elements)
// Jab index i pe ho, BIT me sirf i ke RIGHT wale elements ki freq hai.
// Query: compressed index < id wale kitne elements = bit.sum(id)
// ════════════════════════════════════════════════════════════════════════════

class Coordinate_Compression
{
public:
    unordered_map<int, int> compress;
    vector<int> rev_map;

    // ── Coordinate_Compression: unique values ko 0-based compressed id do ──
    //   1) nums ke unique values sorted set me collect karo
    //   2) har value ko 0, 1, 2, ... sequential id assign karo
    //   3) compress map + rev_map dono maintain — forward aur reverse lookup
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

    // ── get_compressed: array ko compressed indices me convert ──
    //   1) har element ka compress[arr[i]] nikalo
    //   2) 0-based compressed id return karo
    vector<int> get_compressed(const vector<int> &arr)
    {
        vector<int> res(arr.size());
        for (int i = 0; i < (int)arr.size(); i++)
            res[i] = compress[arr[i]];
        return res;
    }

    // ── get_original: compressed id se original value ──
    //   1) rev_map[val] se reverse lookup
    int get_original(int val)
    {
        return rev_map[val];
    }
};

class BIT
{
public:
    int n;
    vector<ll> bit;

    // ── BIT: frequency Fenwick tree setup ──
    //   1) n = unique value count (compressed range)
    //   2) bit size n+1, 1-indexed
    BIT(int n)
    {
        this->n = n;
        bit.assign(n + 1, 0);
    }

    // ── update: index 'i' pe 'x' add (frequency badhao) ──
    //   1) i se n tak BIT nodes me x add karo
    //   2) i += (i & -i) — LSB jump se parent frequency update
    void update(int i, ll x)
    {
        for (; i <= n; i += (i & -i))  // i & -i = lowest set bit
            bit[i] += x;
    }

    // ── sum: [1, i] ka prefix — compressed indices [0, i-1] ki count ──
    //   1) total = 0, i > 0 tak loop
    //   2) bit[i] add — kitne elements ki compressed value < i
    //   3) i -= (i & -i) LSB jump
    //   4) sum(id) = right side me kitne elements current se chhote hain
    ll sum(int i)
    {
        ll total = 0;
        for (; i > 0; i -= (i & -i))
            total += bit[i];
        return total;
    }
};

class Solution
{
public:
    // ── countSmaller: har i ke liye right side me chhote elements count ──
    //   1) coordinate compression — values ko 0..K-1 me map karo
    //   2) RIGHT se LEFT scan: BIT me sirf right wale elements ki freq hai
    //   3) har i pe: ans[i] = bit.sum(id) — id se chhote kitne already seen
    //   4) bit.update(id+1, 1) — current element ko BIT me daal do for next left indices
    vector<int> countSmaller(vector<int> &nums)
    {
        int n = nums.size();

        Coordinate_Compression cc(nums);
        int K = cc.rev_map.size();

        BIT bit(K);
        vector<int> ans(n, 0);

        // RIGHT se LEFT: BIT me pehle se right wale elements ki freq hai
        for (int i = n - 1; i >= 0; i--)
        {
            int id = cc.compress[nums[i]];

            ans[i] = bit.sum(id);      // compressed id se chhote = smaller count
            bit.update(id + 1, 1);     // 1-indexed BIT: current element freq +1
        }

        return ans;
    }
};

/*
Example walkthrough: nums = [5,2,6,1]
Compression: 1->0, 2->1, 5->2, 6->3

i=3, val=1: BIT empty -> ans[3]=0, update bit[1]
i=2, val=6: sum(3)=1 -> ans[2]=1, update bit[4]
i=1, val=2: sum(1)=1 -> ans[1]=1, update bit[2]
i=0, val=5: sum(2)=2 -> ans[0]=2

Answer: [2,1,1,0]
Complexity: O(n log n)
*/

// ── main: Leetcode 315 sample run ──
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution sol;
    vector<int> nums = {5, 2, 6, 1};
    vector<int> result = sol.countSmaller(nums);

    for (int count : result)
        cout << count << " ";
    cout << "\n";

    return 0;
}
