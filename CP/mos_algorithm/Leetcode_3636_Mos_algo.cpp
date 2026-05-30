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
// 🔹 Summary:
// Har query me hume subarray ke elements ka **frequency count** karna hai,
// aur max frequency wala element pick karna hai jo threshold se bada ho.
// Agar tie ho to **smallest element choose karna**. Agar koi satisfy nahi kare to -1 return.

#include <bits/stdc++.h>
using namespace std;

// ============================
// Coordinate Compression
// ============================
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

// ============================
// Mo's Algorithm for Majority Query
// ============================
class Mos_Algorithm
{
private:
    vector<int> arr;  // compressed array
    vector<int> freq; // frequency of each element
    int BLOCK_SIZE;
    vector<int> rev_map;

public:
    struct Query
    {
        int l, r, threshold, idx;
    };

    Mos_Algorithm(const vector<int> &compressed, const vector<int> &rev_map_input)
    {
        arr = compressed;
        rev_map = rev_map_input;
        int n = arr.size();
        BLOCK_SIZE = sqrt(n);
        freq.assign(rev_map.size(), 0);
    }

    bool compare(const Query &a, const Query &b)
    {
        int block_a = a.l / BLOCK_SIZE;
        int block_b = b.l / BLOCK_SIZE;

        if (block_a != block_b)
            return block_a < block_b;

        // Odd-even optimization
        if (block_a & 1)
            return a.r < b.r;
        else
            return a.r > b.r;
    }

    void add(int idx)
    {
        freq[arr[idx]]++;
    }

    void remove(int idx)
    {
        freq[arr[idx]]--;
    }

    int get_answer(int threshold)
    {
        int best_freq = 0;
        int ans = -1;

        // Loop over all compressed values
        for (int i = 0; i < freq.size(); i++)
        {
            if (freq[i] >= threshold)
            {
                if (freq[i] > best_freq || (freq[i] == best_freq && rev_map[i] < ans))
                {
                    best_freq = freq[i];
                    ans = rev_map[i];
                }
            }
        }

        return ans;
    }

    vector<int> process_queries(vector<Query> &queries)
    {
        sort(queries.begin(), queries.end(), [this](Query a, Query b)
             { return compare(a, b); });

        vector<int> answer(queries.size());
        int cur_l = 0, cur_r = -1;

        for (auto &q : queries)
        {
            while (cur_l > q.l)
                add(--cur_l);
            while (cur_r < q.r)
                add(++cur_r);
            while (cur_l < q.l)
                remove(cur_l++);
            while (cur_r > q.r)
                remove(cur_r--);
            answer[q.idx] = get_answer(q.threshold);
        }
        return answer;
    }
};

// ============================
// Solution Class
// ============================
class Solution
{
public:
    vector<int> subarray_Majority(vector<int> &nums, vector<vector<int>> &queries)
    {
        // 1️⃣ Coordinate Compression
        Coordinate_Compression cc(nums);
        vector<int> compressed = cc.get_compressed(nums);

        // 2️⃣ Prepare queries
        vector<Mos_Algorithm::Query> qs;
        for (int i = 0; i < queries.size(); i++)
            qs.push_back({queries[i][0], queries[i][1], queries[i][2], i});

        // 3️⃣ Run Mo's Algorithm
        Mos_Algorithm mo(compressed, cc.rev_map);
        return mo.process_queries(qs);
    }
};

// ============================
// Example Usage
// ============================
int main()
{
    Solution sol;

    // Example 1
    vector<int> nums1 = {1, 1, 2, 2, 1, 1};
    vector<vector<int>> queries1 = {{0, 5, 4}, {0, 3, 3}, {2, 3, 2}};
    vector<int> ans1 = sol.subarray_Majority(nums1, queries1);

    cout << "Example 1 Output: ";
    for (int x : ans1)
        cout << x << " ";
    cout << endl;

    // Example 2
    vector<int> nums2 = {3, 2, 3, 2, 3, 2, 3};
    vector<vector<int>> queries2 = {{0, 6, 4}, {1, 5, 2}, {2, 4, 1}, {3, 3, 1}};
    vector<int> ans2 = sol.subarray_Majority(nums2, queries2);

    cout << "Example 2 Output: ";
    for (int x : ans2)
        cout << x << " ";
    cout << endl;

    return 0;
}
