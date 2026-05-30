#include <bits/stdc++.h> // mos algorithm for offline queries to find size of distinct elements in a range
using namespace std;

class MosAlgorithm
{
private:
    vector<int> arr;    // Original array
    vector<int> freq;   // Frequency array for current range
    int distinct_count; // Current number of distinct elements in range
    int BLOCK_SIZE;     // Size of each block (sqrt decomposition)

public:
    // ------------------------------
    // Constructor
    // ------------------------------
    MosAlgorithm(const vector<int> &input)
    {
        arr = input;
        int n = arr.size();
        BLOCK_SIZE = sqrt(n); // Block size = √n

        // Optimize frequency array size based on max element in arr
        int max_val = *max_element(arr.begin(), arr.end());
        freq.assign(max_val + 1, 0);

        distinct_count = 0;
    }

    // ------------------------------
    // Query structure
    // ------------------------------
    struct Query
    {
        int l, r, idx; // query range [l, r] and original index
    };

    // ------------------------------
    // Compare function for Mo's sorting
    // ------------------------------
    bool compare(const Query &a, const Query &b)
    {
        int block_a = a.l / BLOCK_SIZE;
        int block_b = b.l / BLOCK_SIZE;

        if (block_a != block_b)
            return block_a < block_b; // Different blocks → sort by block

        // Odd-even optimization
        if (block_a & 1)
            return a.r < b.r; // odd block → right ascending
        else
            return a.r > b.r; // even block → right descending
    }

    // ------------------------------
    // Add an index to current range
    // ------------------------------
    void add(int idx)
    {
        freq[arr[idx]]++;
        if (freq[arr[idx]] == 1)
            distinct_count++; // New distinct element added
    }

    // ------------------------------
    // Remove an index from current range
    // ------------------------------
    void remove(int idx)
    {
        freq[arr[idx]]--;
        if (freq[arr[idx]] == 0)
            distinct_count--; // Distinct element removed
    }

    // ------------------------------
    // Get current answer (number of distinct elements)
    // ------------------------------
    int get_answer()
    {
        return distinct_count;
    }

    // ------------------------------
    // Main Mo's Algorithm function
    // ------------------------------
    vector<int> process_queries(vector<Query> &queries)
    {
        int n = arr.size();
        int q = queries.size();

        // ✅ Sort queries using Mo's order
        sort(queries.begin(), queries.end(),
             [this](Query a, Query b)
             { return compare(a, b); });

        vector<int> answer(q);
        int cur_l = 0, cur_r = -1; // current range empty

        for (auto &query : queries)
        {
            int L = query.l, R = query.r;

            // Expand or shrink range to match query
            while (cur_l > L)
                add(--cur_l);
            while (cur_r < R)
                add(++cur_r);
            while (cur_l < L)
                remove(cur_l++);
            while (cur_r > R)
                remove(cur_r--);

            // Store answer
            answer[query.idx] = get_answer();
        }

        return answer;
    }
};

// ------------------------------
// Example usage
// ------------------------------
int main()
{
    vector<int> arr = {1, 2, 1, 3, 2, 2, 4};
    MosAlgorithm mo(arr);

    // Queries: [l, r] with original index
    vector<MosAlgorithm::Query> queries = {
        {0, 4, 0}, // query 0 → range 0-4
        {1, 5, 1}, // query 1 → range 1-5
        {2, 6, 2}  // query 2 → range 2-6
    };

    vector<int> answers = mo.process_queries(queries);

    cout << "Distinct elements in each query range:\n";
    for (int ans : answers)
    {
        cout << ans << "\n";
    }

    return 0;
}
