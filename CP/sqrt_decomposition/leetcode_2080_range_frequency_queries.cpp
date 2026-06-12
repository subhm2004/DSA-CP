#include <bits/stdc++.h>
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * LEETCODE 2080 — Range Frequency Queries
 * ════════════════════════════════════════════════════════════════════════════
 *
 * DIYA HAI:
 *   arr array, queries[i] = [left, right, value]
 *
 * POOCHNA HAI:
 *   arr[left..right] me `value` kitni baar aata hai?
 *
 * Example: arr=[12,33,4,56,22,2,34,33,22,12,34,56]
 *   query [1,2,4]  → arr[1..2]={33,4}, 4 count=1
 *   query [0,11,33] → poori array me 33 → 2
 *
 * APPROACH: Sqrt Decomposition on array blocks
 *   Har block me frequency map (value → count in that block)
 *   Query: partial left + full blocks lookup + partial right
 *   Update: point update — block map adjust O(1) amortized
 *
 * Time: build O(n) | query O(sqrt n) | update O(1)
 * ════════════════════════════════════════════════════════════════════════════
 */

class RangeFreqSqrt {
private:
    vector<int> arr;
    vector<unordered_map<int, int>> blockFreq;
    int n, blockSize, numBlocks;

    /*
     * rebuildBlock(b)
     * Block b ki frequency map dobara banao (update ke baad rare use).
     */
    void rebuildBlock(int b) {
        blockFreq[b].clear();
        int start = b * blockSize;
        int end = min(n, (b + 1) * blockSize);
        for (int i = start; i < end; i++)
            blockFreq[b][arr[i]]++;
    }

public:
    RangeFreqSqrt(const vector<int>& a) : arr(a) {
        n = (int)arr.size();
        blockSize = max(1, (int)sqrt(n));
        numBlocks = (n + blockSize - 1) / blockSize;
        blockFreq.assign(numBlocks, {});
        for (int b = 0; b < numBlocks; b++)
            rebuildBlock(b);
    }

    /*
     * update(i, val)
     * Point update — purani value block map se hatao, nayi add.
     */
    void update(int i, int val) {
        int b = i / blockSize;
        blockFreq[b][arr[i]]--;
        if (blockFreq[b][arr[i]] == 0) blockFreq[b].erase(arr[i]);
        arr[i] = val;
        blockFreq[b][arr[i]]++;
    }

    /*
     * countInRange(left, right, value)
     * --------------------------------
     * Teen phase (classic sqrt query):
     *   1) left partial block — scan elements
     *   2) full middle blocks — blockFreq[b][value]
     *   3) right partial block — scan elements
     */
    int countInRange(int left, int right, int value) const {
        int ans = 0;
        int l = left, r = right;

        while (l <= r && l % blockSize != 0) {
            if (arr[l] == value) ans++;
            l++;
        }

        while (l + blockSize - 1 <= r) {
            auto it = blockFreq[l / blockSize].find(value);
            if (it != blockFreq[l / blockSize].end()) ans += it->second;
            l += blockSize;
        }

        while (l <= r) {
            if (arr[l] == value) ans++;
            l++;
        }

        return ans;
    }

    vector<int> rangeFreqQueries(vector<vector<int>>& queries) {
        vector<int> res;
        for (auto& q : queries)
            res.push_back(countInRange(q[0], q[1], q[2]));
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> arr = {12, 33, 4, 56, 22, 2, 34, 33, 22, 12, 34, 56};
    RangeFreqSqrt rf(arr);

    vector<vector<int>> queries = {
        {1, 2, 4}, {0, 11, 33}, {1, 3, 56}, {0, 3, 12}};

    cout << "LC 2080 — Range Frequency Queries (sqrt)\n";
  auto res = rf.rangeFreqQueries(queries);
    for (int i = 0; i < (int)queries.size(); i++)
        cout << "  [" << queries[i][0] << "," << queries[i][1] << "," << queries[i][2]
             << "] -> " << res[i] << "\n";

    cout << "\nAfter update arr[0]=33:\n";
    rf.update(0, 33);
    cout << "  [0,11,33] -> " << rf.countInRange(0, 11, 33) << " (expected 3)\n";

    return 0;
}
