#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// MO'S ALGORITHM WITH UPDATES (Mo's + Time Pointer)
// ────────────────────────────────────────────────────────────────────────────
// Normal Mo's sirf static array pe kaam karta hai. Yaha queries ke saath-saath
// point updates bhi hain. Isliye teen pointers maintain karte hain:
//
//   cur_l, cur_r -> current range [cur_l, cur_r] in array
//   cur_t        -> kitne updates apply ho chuke hain (time pointer)
//
// Har query me ek extra field 't' hoti hai — "is query ke time tak kitne updates
// apply hone chahiye". Jab query process karte hain to:
//   - pehle range adjust karo (add/remove)
//   - phir cur_t ko q.t tak le jao (updates apply ya undo)
//
// Sorting: block on l, odd-even on r, phir t ascending (same l-block + same r)
// Complexity: ~O((Q + U) * N^(2/3)) with proper block sizing
// ════════════════════════════════════════════════════════════════════════════

class Mos_Algorithm_With_Updates
{
private:
    vector<int> arr;
    int BLOCK_SIZE;
    int cur_l, cur_r, cur_t;  // current range + kitne updates apply hue
    long long cur_sum;

public:
    // Query: range [l,r], original index, aur kitne updates apply karne hain (t)
    struct Query
    {
        int l, r;
        int idx;
        int t;
    };

    // Update: index pe value badalna + undo ke liye purani value yaad rakhna
    struct Update
    {
        int idx;
        int new_val;
        int old_val;
    };

    // ── Mos_Algorithm_With_Updates: constructor — pointers aur sum init ──
    //   1) input array copy karo member 'arr' me
    //   2) BLOCK_SIZE = max(1, sqrt(n)) set karo — Mo's block width (empty array safe)
    //   3) cur_l=0, cur_r=-1 rakho — shuru me empty range (koi element include nahi)
    //   4) cur_t=0 aur cur_sum=0 — abhi koi update apply nahi, sum bhi zero
    Mos_Algorithm_With_Updates(const vector<int> &input)
    {
        arr = input;
        BLOCK_SIZE = max(1, (int)sqrt(arr.size()));
        cur_l = 0;
        cur_r = -1;
        cur_t = 0;
        cur_sum = 0;
    }

    // ── compare: Mo's ordering + time 't' as tiebreaker ──
    //   1) pehle left block (l / BLOCK_SIZE) se compare — alag blocks me chhota pehle
    //   2) same block me odd-even r trick: odd me r ascending, even me r descending
    //   3) agar l-block aur r dono same hain to t ascending — pehle kam updates wali query
    //   4) ye 3-level sort se range, r, aur time teeno pointers kam bounce karte hain
    bool compare(const Query &a, const Query &b) const
    {
        int block_a = a.l / BLOCK_SIZE;
        int block_b = b.l / BLOCK_SIZE;

        if (block_a != block_b)
        {
            return block_a < block_b;
        }

        // odd-even r optimization within same left block
        if (block_a & 1)
        {
            if (a.r != b.r)
                return a.r < b.r;
        }
        else
        {
            if (a.r != b.r)
                return a.r > b.r;
        }

        // same l-block + same r -> time pointer kam hilane ke liye t ascending
        return a.t < b.t;
    }

    // ── add: index ko current Mo window me include karo ──
    //   1) arr[idx] ki current value (jo ab tak ke updates reflect karti hai) lo
    //   2) us value ko cur_sum me add karo
    //   3) O(1) — sirf ek element range me aaya, running sum update
    void add(int idx)
    {
        cur_sum += arr[idx];
    }

    // ── remove: index ko current Mo window se bahar nikalo ──
    //   1) arr[idx] ki current value cur_sum se subtract karo
    //   2) element ab active range me nahi hai lekin array me value ab bhi hai
    //   3) O(1) — running sum se element ka contribution hata diya
    void remove(int idx)
    {
        cur_sum -= arr[idx];
    }

    // ── apply_update: ek point update apply karo ya undo karo ──
    //   1) undo=false -> new_val lagao; undo=true -> purani old_val wapas lagao
    //   2) agar update wala index current range [cur_l, cur_r] me hai to sum adjust karo:
    //      pehle purani arr[idx] sum se hatao, phir nayi value sum me add karo
    //   3) arr[idx] ko nayi value se overwrite karo — aage ke add/remove is value use karenge
    //   4) range ke bahar index ho to sirf array update — cur_sum affect nahi hota
    void apply_update(const Update &u, bool undo = false)
    {
        int idx = u.idx;
        int val = undo ? u.old_val : u.new_val;

        // index active range me hai to sum me purani value hata ke nayi add karo
        if (cur_l <= idx && idx <= cur_r)
        {
            cur_sum -= arr[idx];  // purani value ka contribution hatao
            cur_sum += val;       // nayi value ka contribution add karo
        }
        arr[idx] = val;  // array permanently update — future add/remove is value use karenge
    }

    // ── process_queries: queries + updates dono offline process karo ──
    //   1) queries ko compare() se sort karo (l-block, odd-even r, phir t)
    //   2) har query ke liye pehle range adjust: cur_l/cur_r ko [q.l, q.r] pe lao
    //   3) phir time pointer adjust: cur_t < q.t pe updates apply, cur_t > q.t pe undo
    //   4) jab range aur time dono match ho jayein, answers[q.idx] = cur_sum store karo
    //   5) original idx se answers input order me restore hote hain
    vector<long long> process_queries(vector<Query> &queries, vector<Update> &updates)
    {
        sort(queries.begin(), queries.end(),
             [this](const Query &a, const Query &b)
             {
                 return compare(a, b);
             });

        vector<long long> answers(queries.size());

        for (const auto &q : queries)
        {
            // Step 1: range pointers adjust — Mo's expand/shrink
            while (cur_l > q.l)
                add(--cur_l);       // left expand
            while (cur_l < q.l)
                remove(cur_l++);    // left shrink

            while (cur_r < q.r)
                add(++cur_r);       // right expand
            while (cur_r > q.r)
                remove(cur_r--);    // right shrink

            // Step 2: time pointer aage badhao — updates apply karo
            while (cur_t < q.t)
            {
                apply_update(updates[cur_t], false);
                cur_t++;
            }
            // Step 3: time pointer peeche lao — updates undo karo (rollback)
            while (cur_t > q.t)
            {
                cur_t--;
                apply_update(updates[cur_t], true);  // last applied update ko reverse karo
            }

            answers[q.idx] = cur_sum;
        }

        return answers;
    }
};

// ── test_algorithm: teen test cases se correctness verify karo ──
//   1) Test 1: basic range queries + do updates — expected sums check karo
//   2) Test 2: same index pe multiple updates — time pointer rollback test
//   3) Test 3: edge cases — single element, negative values, partial ranges
//   4) har test me queries aur updates banao, process_queries chalao, print karo
void test_algorithm()
{
    cout << "=== TEST CASE 1: Basic Operations ===\n";
    vector<int> arr1 = {1, 2, 3, 4, 5};
    Mos_Algorithm_With_Updates mo1(arr1);

    vector<Mos_Algorithm_With_Updates::Update> updates1 = {
        {1, 10, arr1[1]},
        {3, 20, arr1[3]}
    };

    vector<Mos_Algorithm_With_Updates::Query> queries1 = {
        {0, 2, 0, 0},
        {1, 4, 1, 1},
        {0, 4, 2, 2},
        {2, 3, 3, 1},
        {0, 1, 4, 0}
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
        {0, 100, arr2[0]},
        {0, 200, 100},
        {2, 300, arr2[2]}
    };

    vector<Mos_Algorithm_With_Updates::Query> queries2 = {
        {0, 3, 0, 0},
        {0, 3, 1, 1},
        {0, 3, 2, 2},
        {0, 3, 3, 3},
        {1, 2, 4, 2}
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
        {1, 0, arr3[1]},
        {4, -10, arr3[4]}
    };

    vector<Mos_Algorithm_With_Updates::Query> queries3 = {
        {0, 0, 0, 0},
        {1, 1, 1, 0},
        {1, 1, 2, 1},
        {0, 4, 3, 0},
        {0, 4, 4, 2},
        {2, 4, 5, 1}
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

// ── main: test_algorithm() chalao aur program exit karo ──
int main()
{
    test_algorithm();
    return 0;
}
