#include <bits/stdc++.h>
using namespace std;

// Ye class Mo's Algorithm with Updates ko implement karta hai
class Mos_Algorithm_With_Updates
{
private:
    vector<int> arr;         // Original array
    int BLOCK_SIZE;          // Block size for Mo's algorithm = sqrt(n)
    int cur_l, cur_r, cur_t; // Current left, right pointers and time (updates applied)
    long long cur_sum;       // Current sum of range [cur_l, cur_r]

public:
    // Query structure
    struct Query
    {
        int l, r; // Range [l,r]
        int idx;  // Query ka original index
        int t;    // Kitne updates apply hue us query ke time tak
    };

    // Update structure
    struct Update
    {
        int idx;     // Kaunsa index update ho raha hai
        int new_val; // Naya value
        int old_val; // Purana value (undo ke liye)
    };

    // Constructor
    Mos_Algorithm_With_Updates(const vector<int> &input)
    {
        arr = input;
        BLOCK_SIZE = max(1, (int)sqrt(arr.size())); // Block size = sqrt(n), 0 se avoid karne ke liye
        cur_l = 0;                                  // Current range start
        cur_r = -1;                                 // Current range end (-1 matlab empty range)
        cur_t = 0;                                  // Updates applied = 0
        cur_sum = 0;                                // Current sum = 0
    }

    // Query comparison function (Mo's ordering)
    bool compare(const Query &a, const Query &b) const
    {
        int block_a = a.l / BLOCK_SIZE;
        int block_b = b.l / BLOCK_SIZE;

        if (block_a != block_b)
        {
            return block_a < block_b; // Alag block me lower block first
        }

        // Same block - alternate ordering odd/even blocks
        if (block_a & 1)
        { // odd block
            if (a.r != b.r)
                return a.r < b.r; // increasing r
        }
        else
        { // even block
            if (a.r != b.r)
                return a.r > b.r; // decreasing r
        }

        return a.t < b.t; // Agar r bhi same, toh earlier update first
    }

    // Add function - jab index ko range me include karte hai
    void add(int idx)
    {
        cur_sum += arr[idx];
    }

    // Remove function - jab index ko range se remove karte hai
    void remove(int idx)
    {
        cur_sum -= arr[idx];
    }

    // Update apply / undo function
    void apply_update(const Update &u, bool undo = false)
    {
        int idx = u.idx;
        int val = undo ? u.old_val : u.new_val; // Undo kar rahe ho ya normal apply

        // Agar ye index current range me hai, toh sum update karna padega
        if (cur_l <= idx && idx <= cur_r)
        {
            cur_sum -= arr[idx];
            cur_sum += val;
        }
        arr[idx] = val; // Array me actual update
    }

    // Main function jo queries ko process karta hai
    vector<long long> process_queries(vector<Query> &queries, vector<Update> &updates)
    {
        // Queries ko sort karo Mo's ordering me
        sort(queries.begin(), queries.end(),
             [this](const Query &a, const Query &b)
             {
                 return compare(a, b);
             });

        vector<long long> answers(queries.size()); // Answers store karne ke liye

        // Sabhi queries ke liye loop
        for (const auto &q : queries)
        {
            // Left pointer ko move karo
            while (cur_l > q.l)
                add(--cur_l); // left expand
            while (cur_l < q.l)
                remove(cur_l++); // left shrink

            // Right pointer ko move karo
            while (cur_r < q.r)
                add(++cur_r); // right expand
            while (cur_r > q.r)
                remove(cur_r--); // right shrink

            // Updates ko handle karo
            while (cur_t < q.t)
            {                                        // agar updates pending hain
                apply_update(updates[cur_t], false); // apply next update
                cur_t++;
            }
            while (cur_t > q.t)
            { // agar time backwards move karna hai
                cur_t--;
                apply_update(updates[cur_t], true); // undo update
            }

            answers[q.idx] = cur_sum; // Current range ka sum store
        }

        return answers; // Sabhi query results return
    }
};

// Test function to verify correctness
void test_algorithm()
{
    cout << "=== TEST CASE 1: Basic Operations ===\n";
    vector<int> arr1 = {1, 2, 3, 4, 5};
    Mos_Algorithm_With_Updates mo1(arr1);

    // Updates define karo
    vector<Mos_Algorithm_With_Updates::Update> updates1 = {
        {1, 10, arr1[1]}, // arr[1]: 2 -> 10
        {3, 20, arr1[3]}  // arr[3]: 4 -> 20
    };

    // Queries define karo
    vector<Mos_Algorithm_With_Updates::Query> queries1 = {
        {0, 2, 0, 0}, // sum[0,2] before updates = 1+2+3 = 6
        {1, 4, 1, 1}, // sum[1,4] after 1st update = 10+3+4+5 = 22
        {0, 4, 2, 2}, // sum[0,4] after 2nd update = 1+10+3+20+5 = 39
        {2, 3, 3, 1}, // sum[2,3] after 1st update = 3+4 = 7
        {0, 1, 4, 0}  // sum[0,1] before any update = 1+2 = 3
    };

    vector<long long> answers1 = mo1.process_queries(queries1, updates1);

    cout << "Query 1 [0,2] t=0 (expected 6): " << answers1[0] << "\n";
    cout << "Query 2 [1,4] t=1 (expected 22): " << answers1[1] << "\n";
    cout << "Query 3 [0,4] t=2 (expected 39): " << answers1[2] << "\n";
    cout << "Query 4 [2,3] t=1 (expected 7): " << answers1[3] << "\n";
    cout << "Query 5 [0,1] t=0 (expected 3): " << answers1[4] << "\n\n";

    cout << "=== TEST CASE 2: Multiple Updates on Same Index ===\n";
    vector<int> arr2 = {10, 20, 30, 40};
    Mos_Algorithm_With_Updates mo2(arr2);

    vector<Mos_Algorithm_With_Updates::Update> updates2 = {
        {0, 100, arr2[0]}, // arr[0]: 10 -> 100
        {0, 200, 100},     // arr[0]: 100 -> 200
        {2, 300, arr2[2]}  // arr[2]: 30 -> 300
    };

    vector<Mos_Algorithm_With_Updates::Query> queries2 = {
        {0, 3, 0, 0}, // sum[0,3] t=0 = 10+20+30+40 = 100
        {0, 3, 1, 1}, // sum[0,3] t=1 = 100+20+30+40 = 190
        {0, 3, 2, 2}, // sum[0,3] t=2 = 200+20+30+40 = 290
        {0, 3, 3, 3}, // sum[0,3] t=3 = 200+20+300+40 = 560
        {1, 2, 4, 2}  // sum[1,2] t=2 = 20+30 = 50
    };

    vector<long long> answers2 = mo2.process_queries(queries2, updates2);

    cout << "Query 1 [0,3] t=0 (expected 100): " << answers2[0] << "\n";
    cout << "Query 2 [0,3] t=1 (expected 190): " << answers2[1] << "\n";
    cout << "Query 3 [0,3] t=2 (expected 290): " << answers2[2] << "\n";
    cout << "Query 4 [0,3] t=3 (expected 560): " << answers2[3] << "\n";
    cout << "Query 5 [1,2] t=2 (expected 50): " << answers2[4] << "\n\n";

    cout << "=== TEST CASE 3: Edge Cases ===\n";
    vector<int> arr3 = {5, -3, 7, -1, 2};
    Mos_Algorithm_With_Updates mo3(arr3);

    vector<Mos_Algorithm_With_Updates::Update> updates3 = {
        {1, 0, arr3[1]},  // arr[1]: -3 -> 0
        {4, -10, arr3[4]} // arr[4]: 2 -> -10
    };

    vector<Mos_Algorithm_With_Updates::Query> queries3 = {
        {0, 0, 0, 0}, // single element: arr[0] = 5
        {1, 1, 1, 0}, // single element: arr[1] = -3
        {1, 1, 2, 1}, // single element after update: arr[1] = 0
        {0, 4, 3, 0}, // full array t=0 = 5-3+7-1+2 = 10
        {0, 4, 4, 2}, // full array t=2 = 5+0+7-1-10 = 1
        {2, 4, 5, 1}  // range[2,4] t=1 = 7-1+2 = 8
    };

    vector<long long> answers3 = mo3.process_queries(queries3, updates3);

    cout << "Query 1 [0,0] t=0 (expected 5): " << answers3[0] << "\n";
    cout << "Query 2 [1,1] t=0 (expected -3): " << answers3[1] << "\n";
    cout << "Query 3 [1,1] t=1 (expected 0): " << answers3[2] << "\n";
    cout << "Query 4 [0,4] t=0 (expected 10): " << answers3[3] << "\n";
    cout << "Query 5 [0,4] t=2 (expected 1): " << answers3[4] << "\n";
    cout << "Query 6 [2,4] t=1 (expected 8): " << answers3[5] << "\n\n";

    cout << "=== All Tests Completed! ===\n";
}

// ========================== Time Complexity Explanation ===========================
/*
    Mo's Algorithm with Updates ki time complexity:

    - Agar sirf queries hoti (no updates): O((Q + N) * sqrt(N)), jahan Q = queries, N = array size.
    - Agar updates bhi hain (let U = total updates):
        - Sorting queries: O(Q * log Q)
        - Har query ke liye:
            - Left/right pointers move: O(sqrt(N)) (amortized)
            - Time pointer (updates apply/undo): O(sqrt(U)) (amortized)
        - Total: O((Q + U) * N^(2/3)) (cube root decomposition ke idea se)
        - Practical: Har query ke liye O(N^(2/3)) expected, jab blocks ka size N^(2/3) liya jaye.

    - Overall: O((Q + U) * N^(2/3)) (amortized per query), lekin implementation me block size sqrt(N) bhi kaafi cases me fast hota hai.

    - Note: Ye complexity tabhi valid hai jab queries aur updates random order me ho aur block size optimize kiya ho.
*/

// Main function
int main()
{
    test_algorithm(); // Test the Mo's algorithm with updates
    return 0;
}
