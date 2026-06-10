// Problem Summary in Hinglish:
//.
// Humko ek integer array `nums` diya gaya hai, length n.
// Aur ek array `queries` diya hai, jisme har query format me hai [li, ri, thresholdi].
//
// Humko ek naya array `ans` return karna hai, jisme ans[i] ka matlab hai:
// "nums[li...ri] subarray me woh element jo kam se kam thresholdi baar appear hota ho,
// aur agar multiple elements max frequency ke saath satisfy karte hain,
// to sabse chhota element choose karna"
// Agar koi element thresholdi se zyada occur nahi karta, to -1 return karna.
//
// Example 1:
// nums = [1,1,2,2,1,1], queries = [[0,5,4],[0,3,3],[2,3,2]]
//
// Query 0: [0,5,4] => Subarray = [1,1,2,2,1,1]
// Element frequency: 1 -> 4, 2 -> 2
// Threshold = 4 => 1 appear hua >= 4 baar => ans[0] = 1
//
// Query 1: [0,3,3] => Subarray = [1,1,2,2]
// Frequency: 1 -> 2, 2 -> 2
// Threshold = 3 => koi element satisfy nahi karta => ans[1] = -1
//
// Query 2: [2,3,2] => Subarray = [2,2]
// Frequency: 2 -> 2
// Threshold = 2 => 2 satisfy karta => ans[2] = 2
//
// Output: [1,-1,2]
//
// Example 2:
// nums = [3,2,3,2,3,2,3], queries = [[0,6,4],[1,5,2],[2,4,1],[3,3,1]]
//
// Query 0: [0,6,4] => Subarray = [3,2,3,2,3,2,3]
// Frequency: 3 -> 4, 2 -> 3
// Threshold = 4 => 3 satisfy karta => ans[0] = 3
//
// Query 1: [1,5,2] => Subarray = [2,3,2,3,2]
// Frequency: 2 -> 3, 3 -> 2
// Threshold = 2 => 2 max freq, satisfy karta => ans[1] = 2
//
// Query 2: [2,4,1] => Subarray = [3,2,3]
// Frequency: 3 -> 2, 2 -> 1
// Threshold = 1 => 3 max freq, satisfy karta => ans[2] = 3
//
// Query 3: [3,3,1] => Subarray = [2]
// Frequency: 2 -> 1
// Threshold = 1 => 2 satisfy karta => ans[3] = 2
//
// Output: [3,2,3,2]
//
// Constraints:
// 1 <= nums.length == n <= 10^4
// 1 <= nums[i] <= 10^9
// 1 <= queries.length <= 5 * 10^4
// queries[i] = [li, ri, thresholdi]
// 0 <= li <= ri < n
// 1 <= thresholdi <= ri - li + 1
//
// Summary:
// Har query me subarray ke elements ka frequency count karna hai,
// aur max frequency wala element pick karna hai jo threshold se bada ho.
// Agar tie ho to smallest element choose karna. Agar koi satisfy nahi kare to -1.

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// COORDINATE COMPRESSION
// ────────────────────────────────────────────────────────────────────────────
// nums me values bahut badi ho sakti hain (1e9) lekin distinct kam hain.
// Unhe 0,1,2,... me map kar dete hain taaki freq array chhota rahe.
// ════════════════════════════════════════════════════════════════════════════
class Coordinate_Compression
{
public:
    unordered_map<int, int> compress; // original -> compressed id
    vector<int> rev_map;              // compressed id -> original value

    // ── Coordinate_Compression: unique values ko sorted ids me map karo ──
    //   1) array ki saari values set me daalo — duplicates auto remove ho jate hain
    //   2) set sorted order me iterate karo (chhote se bade)
    //   3) har unique value ko id=0,1,2,... assign karo compress map me
    //   4) rev_map me id -> original value store karo (baad me answer decode ke liye)
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

    // ── get_compressed: poori array ko compressed ids me convert karo ──
    //   1) result vector input array jitna bada banao
    //   2) har position i pe arr[i] ko compress map se lookup karke chhoti id lo
    //   3) compressed array Mo's freq array ke liye use hogi — size = distinct count
    //   4) original values nahi, sirf 0..D-1 ids store hoti hain
    vector<int> get_compressed(const vector<int> &arr)
    {
        vector<int> res(arr.size());
        for (int i = 0; i < arr.size(); i++)
            res[i] = compress[arr[i]];
        return res;
    }

    // ── get_original: compressed id se wapas original value lo ──
    //   1) rev_map[val] se compressed id ka asli number return karo
    //   2) get_answer() me final answer original value me dena hota hai
    //   3) O(1) lookup — rev_map pre-built hai constructor me
    int get_original(int val)
    {
        return rev_map[val];
    }
};

// ════════════════════════════════════════════════════════════════════════════
// MO'S ALGORITHM — Threshold Frequency Query (LeetCode 3636 style)
// ────────────────────────────────────────────────────────────────────────────
// Har query [l, r, threshold]: range me wo element dhundo jiski freq >= threshold,
// aur agar multiple hain to sabse chhota. Mo's se offline process karte hain.
// ════════════════════════════════════════════════════════════════════════════
class Mos_Algorithm
{
private:
    vector<int> arr;   // compressed array
    vector<int> freq;  // current range me har compressed value ki frequency
    int BLOCK_SIZE;
    vector<int> rev_map;

public:
    struct Query
    {
        int l, r, threshold, idx;
    };

    // ── Mos_Algorithm: compressed array aur freq array setup ──
    //   1) compressed array aur rev_map (id -> original) store karo
    //   2) BLOCK_SIZE = sqrt(n) set karo Mo's sorting ke liye
    //   3) freq array size = distinct values count, sab 0 se initialize
    //   4) shuru me koi range active nahi — freq sab zero
    Mos_Algorithm(const vector<int> &compressed, const vector<int> &rev_map_input)
    {
        arr = compressed;
        rev_map = rev_map_input;
        int n = arr.size();
        BLOCK_SIZE = sqrt(n);
        freq.assign(rev_map.size(), 0);
    }

    // ── compare: Mo's block sorting (odd-even r optimization) ──
    //   1) left endpoint ka block nikalo: l / BLOCK_SIZE
    //   2) alag blocks me chhota block pehle — cur_l kam jump karega
    //   3) same block me odd -> r ascending, even -> r descending (zig-zag)
    //   4) is order se cur_r pointer amortized kam move karta hai
    bool compare(const Query &a, const Query &b)
    {
        int block_a = a.l / BLOCK_SIZE;
        int block_b = b.l / BLOCK_SIZE;

        if (block_a != block_b)
            return block_a < block_b;

        // odd-even r optimization: block parity se sort direction flip
        if (block_a & 1)
            return a.r < b.r;
        else
            return a.r > b.r;
    }

    // ── add: index ko current Mo window me include karo ──
    //   1) arr[idx] compressed id lo (chhoti value 0..D-1)
    //   2) us id ki freq array me frequency badhao
    //   3) O(1) per add — sirf ek freq counter increment
    //   4) get_answer() baad me is freq array scan karke best element dhundega
    void add(int idx)
    {
        freq[arr[idx]]++;
    }

    // ── remove: index ko current Mo window se bahar nikalo ──
    //   1) arr[idx] ki compressed id ki freq ghatao
    //   2) element ab active range me nahi — uska count kam ho gaya
    //   3) O(1) per remove — sirf ek freq counter decrement
    //   4) freq 0 ho sakti hai lekin array slot rehta hai (compressed id fixed)
    void remove(int idx)
    {
        freq[arr[idx]]--;
    }

    // ── get_answer: threshold satisfy karne wala sabse chhota element ──
    //   1) saari compressed ids (0 se freq.size()-1) scan karo
    //   2) jinki freq >= threshold ho unhe candidates maano
    //   3) candidates me sabse zyada freq wala choose karo
    //   4) agar freq tie ho to rev_map se original value chhota wala lo
    //   5) koi candidate nahi mila to -1 return karo
    int get_answer(int threshold)
    {
        int best_freq = 0;
        int ans = -1;

        for (int i = 0; i < freq.size(); i++)
        {
            if (freq[i] >= threshold)
            {
                // max freq prefer; tie pe chhota original value (rev_map[i] < ans)
                if (freq[i] > best_freq || (freq[i] == best_freq && rev_map[i] < ans))
                {
                    best_freq = freq[i];
                    ans = rev_map[i];
                }
            }
        }

        return ans;
    }

    // ── process_queries: Mo's order me saari queries answer karo ──
    //   1) queries ko compare() se sort karo
    //   2) cur_l=0, cur_r=-1 se empty range shuru karo
    //   3) har query ke liye 4 while loops se range [q.l, q.r] pe adjust karo
    //   4) range match hone par get_answer(q.threshold) call karke answer store karo
    //   5) original idx se answers input query order me restore hote hain
    vector<int> process_queries(vector<Query> &queries)
    {
        sort(queries.begin(), queries.end(), [this](Query a, Query b)
             { return compare(a, b); });

        vector<int> answer(queries.size());
        int cur_l = 0, cur_r = -1;  // shuru me empty range

        for (auto &q : queries)
        {
            // Mo's expand/shrink: pehle add (expand), phir remove (shrink)
            while (cur_l > q.l) add(--cur_l);       // left expand
            while (cur_r < q.r) add(++cur_r);       // right expand
            while (cur_l < q.l) remove(cur_l++);    // left shrink
            while (cur_r > q.r) remove(cur_r--);    // right shrink
            answer[q.idx] = get_answer(q.threshold);
        }
        return answer;
    }
};

// ── subarray_Majority: coordinate compression + Mo's pipeline ──
//   1) Coordinate_Compression se nums ko chhoti ids me map karo
//   2) compressed array banao Mo's ke liye
//   3) queries ko {l, r, threshold, idx} format me convert karo
//   4) Mos_Algorithm chalao aur process_queries se answers lo
class Solution
{
public:
    vector<int> subarray_Majority(vector<int> &nums, vector<vector<int>> &queries)
    {
        Coordinate_Compression cc(nums);
        vector<int> compressed = cc.get_compressed(nums);

        vector<Mos_Algorithm::Query> qs;
        for (int i = 0; i < queries.size(); i++)
            qs.push_back({queries[i][0], queries[i][1], queries[i][2], i});

        Mos_Algorithm mo(compressed, cc.rev_map);
        return mo.process_queries(qs);
    }
};

// ── main: do LeetCode examples chalao aur output print karo ──
//   1) Example 1 aur Example 2 ke nums + queries set karo
//   2) Solution::subarray_Majority call karo
//   3) computed answers print karo
int main()
{
    Solution sol;

    vector<int> nums1 = {1, 1, 2, 2, 1, 1};
    vector<vector<int>> queries1 = {{0, 5, 4}, {0, 3, 3}, {2, 3, 2}};
    vector<int> ans1 = sol.subarray_Majority(nums1, queries1);

    cout << "Example 1 Output: ";
    for (int x : ans1)
        cout << x << " ";
    cout << endl;

    vector<int> nums2 = {3, 2, 3, 2, 3, 2, 3};
    vector<vector<int>> queries2 = {{0, 6, 4}, {1, 5, 2}, {2, 4, 1}, {3, 3, 1}};
    vector<int> ans2 = sol.subarray_Majority(nums2, queries2);

    cout << "Example 2 Output: ";
    for (int x : ans2)
        cout << x << " ";
    cout << endl;

    return 0;
}
