#include <bits/stdc++.h>
using namespace std;

class SQRT_Decomposition
{
private:
    vector<int> arr;      // Original array
    vector<int> blockSum; // Sum of each block
    int n;                // Size of array
    int blockSize;        // Size of each block

public:
    // Constructor: initialize with array
    SQRT_Decomposition(const vector<int> &input)
    {
        arr = input;
        n = arr.size();
        blockSize = (int)sqrt(n + 0.0) + 1;          // block size ≈ √n
        int numBlocks = ceil((double)n / blockSize); // Using ceil for number of blocks
        blockSum.assign(numBlocks, 0);               // initialize block sums

        // Preprocessing: calculate sum of each block
        for (int i = 0; i < n; i++)
            blockSum[i / blockSize] += arr[i];
    }

    // Query: sum of range [left, right]
    int query(int left, int right)
    {
        int total = 0;

        int leftBlock = left / blockSize;
        int rightBlock = right / blockSize;

        if (leftBlock == rightBlock)
        {
            // Case: left and right in the same block
            for (int i = left; i <= right; ++i)
                total += arr[i];
        }
        else
        {
            // 1️⃣ Left partial block
            int leftEnd = (leftBlock + 1) * blockSize - 1;
            for (int i = left; i <= leftEnd; ++i)
                total += arr[i];

            // 2️⃣ Full blocks in the middle
            for (int b = leftBlock + 1; b <= rightBlock - 1; ++b)
                total += blockSum[b];

            // 3️⃣ Right partial block
            int rightStart = rightBlock * blockSize;
            for (int i = rightStart; i <= right; ++i)
                total += arr[i];
        }

        return total;
    }

    // Update element at index idx to newValue
    void update(int idx, int newValue)
    {
        int block = idx / blockSize;
        blockSum[block] = blockSum[block] - arr[idx] + newValue;
        arr[idx] = newValue;
    }

    // Helper function to print current state (for debugging)
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
    // -------------------------------
    // 1️⃣ Multiple example arrays
    // -------------------------------
    vector<vector<int>> arrays = {
        {5, 3, 8, 6, 2, 7, 4, 1, 9, 10},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
        {10, 20, 30, 40, 50, 60}};

    // -------------------------------
    // 2️⃣ Queries and updates for each array
    // -------------------------------
    vector<vector<pair<int, int>>> allQueries = {
        {{0, 4}, {3, 8}, {5, 9}},  // queries for first array
        {{0, 5}, {2, 6}, {0, 10}}, // queries for second array
        {{1, 3}, {0, 5}}           // queries for third array
    };

    vector<vector<pair<int, int>>> allUpdates = {
        {{3, 20}},  // update arr[3] = 20 for first array
        {{0, 100}}, // update arr[0] = 100 for second array
        {{5, 99}}   // update arr[5] = 99 for third array
    };

    // -------------------------------
    // 3️⃣ Process each array
    // -------------------------------
    for (int idx = 0; idx < arrays.size(); ++idx)
    {
        cout << "\n=== Array " << idx + 1 << " ===\n";
        vector<int> arr = arrays[idx];
        SQRT_Decomposition sqrtDecomp(arr);

        // Print initial state
        sqrtDecomp.printState();
        cout << "\n";

        // Run queries
        cout << "Initial queries:\n";
        for (auto q : allQueries[idx])
        {
            int left = q.first, right = q.second;
            cout << "Sum(" << left << ", " << right << ") = "
                 << sqrtDecomp.query(left, right) << "\n";
        }

        // Run updates
        cout << "\nUpdates:\n";
        for (auto u : allUpdates[idx])
        {
            int pos = u.first, newVal = u.second;
            cout << "Updating arr[" << pos << "] to " << newVal << "\n";
            sqrtDecomp.update(pos, newVal);
        }

        // Queries again after updates
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