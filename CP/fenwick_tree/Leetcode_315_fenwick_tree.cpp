// Leetcode 315: Count of Smaller Numbers After Self
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ============================================================================
// COORDINATE COMPRESSION CLASS
// ============================================================================
// Purpose: Convert arbitrary integers to a smaller range [0, unique_count-1]
// Why needed: BIT works efficiently with small positive indices
// Example: [100, -50, 100, 200] -> [1, 0, 1, 2] (compressed indices)
class Coordinate_Compression
{
public:
    unordered_map<int, int> compress; // Maps: original value -> compressed index
    vector<int> rev_map;              // Maps: compressed index -> original value

    // Constructor: Takes input array and builds compression mappings
    Coordinate_Compression(const vector<int> &arr)
    {
        // Step 1: Get unique sorted values
        // set automatically removes duplicates and sorts
        // Example: [5,2,6,1] -> {1,2,5,6}
        set<int> st(arr.begin(), arr.end());

        int id = 0;
        // Step 2: Assign compressed indices (0-based)
        for (int x : st)
        {
            compress[x] = id;     // Store mapping: value -> index
            rev_map.push_back(x); // Store reverse mapping: index -> value
            id++;
        }
        // Result: compress = {1->0, 2->1, 5->2, 6->3}
        //         rev_map = [1, 2, 5, 6]
    }

    // Convert original array to compressed indices
    vector<int> get_compressed(const vector<int> &arr)
    {
        vector<int> res(arr.size());
        for (int i = 0; i < (int)arr.size(); i++)
            res[i] = compress[arr[i]];
        return res;
    }

    // Get original value from compressed index
    int get_original(int val)
    {
        return rev_map[val];
    }
};

// ============================================================================
// BINARY INDEXED TREE (FENWICK TREE) CLASS
// ============================================================================
// Purpose: Efficiently perform range queries and point updates in O(log n)
// Used here to count frequencies of elements
class BIT
{
public:
    int n;
    vector<ll> bit; // 1-indexed array (bit[0] unused)

    // Constructor: Initialize BIT with size n
    BIT(int n)
    {
        this->n = n;
        bit.assign(n + 1, 0); // Create array of size n+1, all zeros
    }

    // Add value 'x' at index 'i' (1-indexed)
    // Time: O(log n)
    void update(int i, ll x)
    {
        // Traverse all nodes responsible for index i
        for (; i <= n; i += (i & -i)) // (i & -i) gives least significant bit
            bit[i] += x;
    }

    // Get prefix sum from index 1 to i (1-indexed)
    // Returns: sum of elements in range [1, i]
    // Time: O(log n)
    ll sum(int i)
    {
        ll total = 0;
        // Traverse all parent nodes
        for (; i > 0; i -= (i & -i))
            total += bit[i];
        return total;
    }
};

// ============================================================================
// MAIN SOLUTION
// ============================================================================
class Solution
{
public:
    vector<int> countSmaller(vector<int> &nums)
    {
        int n = nums.size();

        // Step 1: Coordinate Compression
        // Convert nums to compressed range [0, K-1]
        Coordinate_Compression cc(nums);
        int K = cc.rev_map.size(); // Number of unique elements

        // Step 2: Initialize BIT
        // BIT will store frequency count of each compressed value
        BIT bit(K); // Size K for K unique values

        vector<int> ans(n, 0);

        // Step 3: Process array from RIGHT to LEFT
        // Key insight: When at index i, BIT already contains frequencies
        //              of all elements to the right of i
        for (int i = n - 1; i >= 0; i--)
        {

            // Get compressed index (0-based) of current element
            int id = cc.compress[nums[i]];

            // Step 4: Count smaller elements
            // Elements with compressed index [0, id-1] are smaller than nums[i]
            // BIT is 1-indexed, so query sum(id) gives count of indices [1, id]
            // which corresponds to compressed indices [0, id-1] in our mapping
            ans[i] = bit.sum(id); // Query BIT for count of smaller elements

            // Step 5: Insert current element into BIT
            // Add 1 to position (id+1) because BIT is 1-indexed
            // Compressed index 'id' (0-based) -> BIT index 'id+1' (1-based)
            bit.update(id + 1, 1);
        }

        return ans;
    }
};

/*
============================================================================
ALGORITHM WALKTHROUGH WITH EXAMPLE: nums = [5,2,6,1]
============================================================================

Step 1: Coordinate Compression
- Unique sorted values: {1, 2, 5, 6}
- Compression mapping:
  1 -> 0
  2 -> 1
  5 -> 2
  6 -> 3

Step 2: Processing (Right to Left)

i=3, nums[3]=1, id=0:
  - BIT state: [0,0,0,0] (empty)
  - Query sum(0) = 0  -> ans[3] = 0
  - Update bit[1] += 1 -> BIT: [0,1,0,0]
  - Meaning: Element with compressed index 0 (value=1) seen once

i=2, nums[2]=6, id=3:
  - BIT state: [0,1,0,0]
  - Query sum(3) = bit[1]+bit[2]+bit[3] = 1 -> ans[2] = 1
  - Update bit[4] += 1 -> BIT: [0,1,0,0,1]
  - Meaning: 1 element smaller than 6 (which is 1)

i=1, nums[1]=2, id=1:
  - BIT state: [0,1,0,0,1]
  - Query sum(1) = bit[1] = 1 -> ans[1] = 1
  - Update bit[2] += 1 -> BIT: [0,1,1,0,1]
  - Meaning: 1 element smaller than 2 (which is 1)

i=0, nums[0]=5, id=2:
  - BIT state: [0,1,1,0,1]
  - Query sum(2) = bit[1]+bit[2] = 2 -> ans[0] = 2
  - Update bit[3] += 1 -> BIT: [0,1,1,1,1]
  - Meaning: 2 elements smaller than 5 (which are 1 and 2)

Final Answer: [2,1,1,0] ✓

============================================================================
TIME & SPACE COMPLEXITY
============================================================================
Time: O(n log n)
  - Coordinate compression: O(n log n) for sorting
  - BIT operations: n queries × O(log K) = O(n log n)

Space: O(n)
  - Coordinate compression maps: O(K) where K ≤ n
  - BIT array: O(K)
  - Result array: O(n)

============================================================================
WHY THIS APPROACH WORKS
============================================================================
1. Process right to left: When at index i, we've already seen all elements
   to the right, so BIT contains their frequencies

2. Coordinate compression: Reduces the range to [0, K-1], making BIT
   efficient even for large values like -10^4 to 10^4

3. BIT query: sum(id) gives count of all elements with compressed index
   < id, which are exactly the smaller elements

4. One pass: Each element processed once with O(log n) BIT operations
*/
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Solution sol;
    vector<int> nums = {5, 2, 6, 1};
    vector<int> result = sol.countSmaller(nums);

    for (int count : result)
    {
        cout << count << " ";
    }
    cout << "\n";

    return 0;
}
// ============================================================================