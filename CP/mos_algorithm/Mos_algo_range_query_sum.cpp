#include <bits/stdc++.h> // Mo's algorithm for offline range sum queries
using namespace std;

class MosAlgorithmSum
{
private:
    vector<int> arr; // Original array
    int current_sum; // Sum of current range
    int BLOCK_SIZE;  // Block size for Mo's algorithm

public:
    // ------------------------------
    // Constructor
    // ------------------------------
    MosAlgorithmSum(const vector<int> &input)
    {
        arr = input;
        int n = arr.size();
        BLOCK_SIZE = sqrt(n); // Block size ≈ √n
        current_sum = 0;
    }

    // ------------------------------
    // Query structure
    // ------------------------------
    struct Query
    {
        int l, r, idx; // query range [l,r] and original index
    };

    // ------------------------------
    // Compare function for Mo's sorting
    // ------------------------------
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

    // ------------------------------
    // Add element at idx to current range
    // ------------------------------
    void add(int idx)
    {
        current_sum += arr[idx]; // sum me add kar do
    }

    // ------------------------------
    // Remove element at idx from current range
    // ------------------------------
    void remove(int idx)
    {
        current_sum -= arr[idx]; // sum me se subtract kar do
    }

    // ------------------------------
    // Get current answer (sum of range)
    // ------------------------------
    int get_answer()
    {
        return current_sum;
    }

    // ------------------------------
    // Process all queries
    // ------------------------------
    vector<int> process_queries(vector<Query> &queries)
    {
        int n = arr.size();
        int q = queries.size();

        // Sort queries in Mo's order
        sort(queries.begin(), queries.end(),
             [this](Query a, Query b)
             { return compare(a, b); });

        vector<int> answers(q);
        int cur_l = 0, cur_r = -1; // current range empty

        for (auto &query : queries)
        {
            int L = query.l, R = query.r;

            while (cur_l > L)
                add(--cur_l);
            while (cur_r < R)
                add(++cur_r);
            while (cur_l < L)
                remove(cur_l++);
            while (cur_r > R)
                remove(cur_r--);

            answers[query.idx] = get_answer();
        }

        return answers;
    }
};

// ------------------------------
// Example usage
// ------------------------------
int main()
{
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7};
    MosAlgorithmSum mo(arr);

    vector<MosAlgorithmSum::Query> queries = {
        {0, 3, 0}, // sum 1+2+3+4 = 10
        {2, 5, 1}, // sum 3+4+5+6 = 18
        {1, 6, 2}  // sum 2+3+4+5+6+7 = 27
    };

    vector<int> answers = mo.process_queries(queries);

    cout << "Range sum of each query:\n";
    for (int ans : answers)
        cout << ans << "\n";

    return 0;
}
