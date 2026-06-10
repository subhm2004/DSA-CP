#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// SQRT DECOMPOSITION — Range Sum Query + Point Update
// ────────────────────────────────────────────────────────────────────────────
// Idea: array ko ~sqrt(n) size ke blocks me todo. Har block ka sum pehle se
// store karo (blockSum). Range query me:
//   1) left partial block  -> elements ek-ek karke jodo
//   2) beech ke full blocks -> seedha blockSum use karo (fast)
//   3) right partial block -> elements ek-ek karke jodo
//
// Params:
//   blockSize  -> har block me kitne elements (~sqrt(n))
//   blockSum[b]-> block b ke saare elements ka sum
//   idx/blockSize -> element idx kaunse block me hai
//
// Complexity: Build O(n) | Query O(sqrt n) | Update O(1)
// ════════════════════════════════════════════════════════════════════════════

class SQRT_Decomposition
{
private:
    vector<int> arr;      // original array
    vector<int> blockSum; // har block ka precomputed sum
    int n;                // array size
    int blockSize;        // ~sqrt(n)

public:
    // ── Constructor: array lo, blocks banao, har block ka sum nikaalo ───────
    //   1) arr copy karo, n = size, blockSize ≈ sqrt(n)+1
    //   2) numBlocks = ceil(n/blockSize) — kitne blocks banenge
    //   3) har element ko uske block ke blockSum me add karo (preprocess)
    //   4) ab har block ka sum pehle se ready — query me fast use hoga
    SQRT_Decomposition(const vector<int> &input)
    {
        arr = input;
        n = arr.size();
        blockSize = (int)sqrt(n + 0.0) + 1;
        int numBlocks = ceil((double)n / blockSize);
        blockSum.assign(numBlocks, 0);

        // preprocessing: har element ko uske block ke sum me add karo
        for (int i = 0; i < n; i++)
            blockSum[i / blockSize] += arr[i];
    }

    // ── query: range [left, right] ka sum nikalo ─────────────────────────────
    //   1) leftBlock aur rightBlock nikalo — same block hai ya alag?
    //   2) same block -> seedha left se right elements jodo
    //   3) alag block -> left partial + middle full blocks (blockSum) + right partial
    //   4) total return — O(sqrt n) worst case
    int query(int left, int right)
    {
        int total = 0;

        int leftBlock = left / blockSize;
        int rightBlock = right / blockSize;

        if (leftBlock == rightBlock)
        {
            // dono same block me -> seedha elements jodo
            for (int i = left; i <= right; ++i)
                total += arr[i];
        }
        else
        {
            // 1) left partial block (left se us block ke end tak)
            int leftEnd = (leftBlock + 1) * blockSize - 1;
            for (int i = left; i <= leftEnd; ++i)
                total += arr[i];

            // 2) beech ke poori blocks -> seedha blockSum use karo
            for (int b = leftBlock + 1; b <= rightBlock - 1; ++b)
                total += blockSum[b];

            // 3) right partial block (right block ke start se right tak)
            int rightStart = rightBlock * blockSize;
            for (int i = rightStart; i <= right; ++i)
                total += arr[i];
        }

        return total;
    }

    // ── update: index 'idx' ki value 'newValue' se replace karo ──────────────
    //   1) block = idx / blockSize — kaunsa block affect hua
    //   2) blockSum me purani value hatao, nayi add karo (delta update)
    //   3) arr[idx] = newValue — O(1) point update
    void update(int idx, int newValue)
    {
        int block = idx / blockSize;
        blockSum[block] = blockSum[block] - arr[idx] + newValue;
        arr[idx] = newValue;
    }

    // ── printState: debug ke liye array + block sums print karo ──────────────
    //   1) poori arr print, blockSize dikhao
    //   2) har block ka precomputed sum print — verify karne ke liye
    void printState()
    {
        cout << "Array: ";
        for (int x : arr)
            cout << x << " ";
        cout << "\nBlock size: " << blockSize << "\n";
        cout << "Block sums: ";
        for (int x : blockSum)
            cout << x << " ";
        cout << "\n";
    }
};

int main()
{
    vector<vector<int>> arrays = {
        {5, 3, 8, 6, 2, 7, 4, 1, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
        {10, 20, 30, 40, 50, 60}};

    vector<vector<pair<int, int>>> allQueries = {
        {{0, 4}, {3, 8}, {5, 9}},
        {{0, 5}, {2, 6}, {0, 10}},
        {{1, 3}, {0, 5}}
    };

    vector<vector<pair<int, int>>> allUpdates = {
        {{3, 20}},
        {{0, 100}},
        {{5, 99}}
    };

    for (int idx = 0; idx < arrays.size(); ++idx)
    {
        cout << "\n=== Array " << idx + 1 << " ===\n";
        vector<int> arr = arrays[idx];
        SQRT_Decomposition sqrtDecomp(arr);

        sqrtDecomp.printState();
        cout << "\n";

        cout << "Initial queries:\n";
        for (auto q : allQueries[idx])
        {
            int left = q.first, right = q.second;
            cout << "Sum(" << left << ", " << right << ") = "
                 << sqrtDecomp.query(left, right) << "\n";
        }

        cout << "\nUpdates:\n";
        for (auto u : allUpdates[idx])
        {
            int pos = u.first, newVal = u.second;
            cout << "Updating arr[" << pos << "] to " << newVal << "\n";
            sqrtDecomp.update(pos, newVal);
        }

        cout << "\nQueries after updates:\n";
        for (auto q : allQueries[idx])
        {
            int left = q.first, right = q.second;
            cout << "Sum(" << left << ", " << right << ") = "
                 << sqrtDecomp.query(left, right) << "\n";
        }
    }

    return 0;
}
