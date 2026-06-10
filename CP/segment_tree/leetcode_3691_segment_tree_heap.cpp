#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// LEETCODE 3691 — Maximum Total Subarray Value II
// ────────────────────────────────────────────────────────────────────────────
// Problem: k distinct subarrays choose karo jinka value = max - min ho.
//          Total value maximize karni hai.
//
// Approach: Greedy + Max Heap + Min-Max Segment Tree
//   - Har subarray [l,r] ki value = rangeMax(l,r) - rangeMin(l,r)
//   - Segment tree se range min/max O(log n) me
//   - Max heap se hamesha sabse badi value wala subarray uthao
//   - Us range ko left/right se shrink karke naye candidates heap me daalo
//   - visited set se same [l,r] dobara na aaye
//
// Complexity: build O(n), har query O(log n), heap ops O(k log n)
//             Total ~ O(n + k log n)  (array static — koi update nahi)
// ════════════════════════════════════════════════════════════════════════════

class SegmentTree
{
public:
    int n;
    vector<int> mini_seg;
    vector<int> maxi_seg;

    // ── SegmentTree: constructor — min/max trees build karo ──
    //   1) n = nums.size(), mini_seg aur maxi_seg dono 4*n size allocate
    //   2) Root i=0 se poori array [0, n-1] par build() call karo
    //   3) Static array hai — koi update nahi, sirf range min/max queries
    SegmentTree(vector<int> &nums)
    {
        n = nums.size();
        mini_seg.assign(4 * n, 0);
        maxi_seg.assign(4 * n, 0);
        build(nums, 0, 0, n - 1);
    }

    // ── build: leaf pe nums[l], internal pe min/max of children ──
    //   1) Base case l==r → mini_seg[i] = maxi_seg[i] = nums[l]
    //   2) mid se segment ko left [l,m] aur right [m+1,r] me todo
    //   3) Dono bachho ko recursively build karo
    //   4) Parent: mini = min(left,right), maxi = max(left,right)
    void build(vector<int> &nums, int i, int l, int r)
    {
        if (l == r)
        {
            mini_seg[i] = nums[l];
            maxi_seg[i] = nums[l];
            return;
        }
        int mid = (l + r) / 2;
        build(nums, 2 * i + 1, l, mid);
        build(nums, 2 * i + 2, mid + 1, r);
        mini_seg[i] = min(mini_seg[2 * i + 1], mini_seg[2 * i + 2]);
        maxi_seg[i] = max(maxi_seg[2 * i + 1], maxi_seg[2 * i + 2]);
    }

    // ── min_query: range [ql,qr] ka minimum ──
    //   1) Case 1 NO overlap (r<ql || l>qr) → INT_MAX return
    //   2) Case 2 FULL overlap (ql<=l && r<=qr) → seedha mini_seg[i] return
    //   3) Case 3 PARTIAL → dono bachho ka min lo aur unka min return
    int min_query(int ql, int qr, int i, int l, int r)
    {
        if (r < ql || l > qr)  // Case 1
            return INT_MAX;
        if (ql <= l && r <= qr)  // Case 2
            return mini_seg[i];
        int mid = (l + r) / 2;  // Case 3
        return min(min_query(ql, qr, 2 * i + 1, l, mid),
                   min_query(ql, qr, 2 * i + 2, mid + 1, r));
    }

    // ── max_query: range [ql,qr] ka maximum ──
    //   1) Case 1 NO overlap → INT_MIN return
    //   2) Case 2 FULL overlap → seedha maxi_seg[i] return
    //   3) Case 3 PARTIAL → dono bachho ka max lo aur unka max return
    int max_query(int ql, int qr, int i, int l, int r)
    {
        if (r < ql || l > qr)  // Case 1
            return INT_MIN;
        if (ql <= l && r <= qr)  // Case 2
            return maxi_seg[i];
        int mid = (l + r) / 2;  // Case 3
        return max(max_query(ql, qr, 2 * i + 1, l, mid),
                   max_query(ql, qr, 2 * i + 2, mid + 1, r));
    }

    // Public wrappers: bahar se [l,r] range min/max
    int rangeMin(int l, int r) { return min_query(l, r, 0, 0, n - 1); }
    int rangeMax(int l, int r) { return max_query(l, r, 0, 0, n - 1); }
};

class Solution
{
public:
    // ── maxTotalValue: k subarrays ka max total (max-min) sum ──
    //   1) Segment tree banao — har range ka max-min O(log n) me milega
    //   2) Max heap me poori array [0,n-1] daalo as starting candidate
    //   3) k baar: heap se sabse badi value wala subarray uthao, ans me jodo
    //   4) Us range ko left/right se shrink karke naye candidates heap me daalo
    //   5) visited set se same [l,r] dobara na aaye — greedy se best k subarrays
    long long maxTotalValue(vector<int> &nums, int k)
    {
        int n = nums.size();

        SegmentTree seg(nums); // static array — koi update nahi ho raha

        priority_queue<pair<long long, pair<int, int>>> maxHeap;
        set<pair<int, int>> visited;

        long long start_val = seg.rangeMax(0, n - 1) - seg.rangeMin(0, n - 1);
        maxHeap.push({start_val, {0, n - 1}});
        visited.insert({0, n - 1});

        long long ans = 0;

        while (k-- > 0 && !maxHeap.empty())
        {
            pair<long long, pair<int, int>> top = maxHeap.top();
            maxHeap.pop();

            long long val = top.first;
            int l = top.second.first;
            int r = top.second.second;

            ans += val;

            // Left se shrink → [l+1 .. r] — left element hata ke naya candidate
            if (l + 1 <= r && !visited.count({l + 1, r}))
            {
                long long v = seg.rangeMax(l + 1, r) - seg.rangeMin(l + 1, r);
                maxHeap.push({v, {l + 1, r}});
                visited.insert({l + 1, r});
            }

            // Right se shrink → [l .. r-1] — right element hata ke naya candidate
            if (l <= r - 1 && !visited.count({l, r - 1}))
            {
                long long v = seg.rangeMax(l, r - 1) - seg.rangeMin(l, r - 1);
                maxHeap.push({v, {l, r - 1}});
                visited.insert({l, r - 1});
            }
        }

        return ans;
    }
};

// ═══════════════════════════════════════════════════════
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution sol;

    // Example 1: nums = [1,3,2], k = 2  →  4
    {
        vector<int> nums = {1, 3, 2};
        int k = 2;
        cout << "Example 1: " << sol.maxTotalValue(nums, k) << "\n"; // expected 4
    }

    // Example 2: nums = [4,1,5,2,3], k = 3  →  12
    {
        vector<int> nums = {4, 1, 5, 2, 3};
        int k = 3;
        cout << "Example 2: " << sol.maxTotalValue(nums, k) << "\n"; // expected 12
    }

    return 0;
}
