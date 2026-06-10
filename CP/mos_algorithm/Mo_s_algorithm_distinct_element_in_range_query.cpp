#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// MO'S ALGORITHM — Distinct Elements in Range Query (Offline)
// ────────────────────────────────────────────────────────────────────────────
// Problem: bahut saari range queries [L, R] aati hain — har range me kitne
//          DISTINCT elements hain?
// Approach: queries ko special order me sort karo (block-wise), phir do pointers
//           cur_l aur cur_r ko expand/shrink karke har query ka answer nikalo.
//
// Key idea:
//   cur_l, cur_r -> abhi ka current range [cur_l, cur_r]
//   add(idx)     -> arr[idx] range me daalo, freq badhao
//   remove(idx)  -> arr[idx] range se nikalo, freq ghatao
//   distinct_count -> freq[x]==1 wale elements ki ginti
//
// Complexity: O((n + q) * sqrt(n)) amortized
// ════════════════════════════════════════════════════════════════════════════

class MosAlgorithm
{
private:
    vector<int> arr;          // original array
    vector<int> freq;         // current range me har value ki frequency
    int distinct_count;       // abhi range me kitne distinct elements
    int BLOCK_SIZE;           // sqrt(n) — Mo's block size

public:
    // ── MosAlgorithm: constructor — array, freq array aur block size setup ──
    //   1) input array copy karo aur n = arr.size() lo
    //   2) BLOCK_SIZE = sqrt(n) set karo — Mo's sorting ke liye block width
    //   3) array me max value nikalo aur freq array us size ka allocate karo (sab 0)
    //   4) distinct_count = 0 rakho kyunki shuru me range empty hai
    MosAlgorithm(const vector<int> &input)
    {
        arr = input;
        int n = arr.size();
        BLOCK_SIZE = sqrt(n);

        int max_val = *max_element(arr.begin(), arr.end());
        freq.assign(max_val + 1, 0);
        distinct_count = 0;
    }

    // Query structure: range [l, r] + original index (answer store karne ke liye)
    struct Query
    {
        int l, r, idx;
    };

    // ── compare: Mo's sorting order (block + odd-even r trick) ──
    //   1) pehle left endpoint ka block compare karo: l / BLOCK_SIZE
    //   2) alag blocks me chhota block pehle — cur_l kam jump karega
    //   3) same block me: odd block -> r ascending, even block -> r descending
    //   4) ye zig-zag r-order se cur_r pointer amortized kam move karta hai
    bool compare(const Query &a, const Query &b)
    {
        int block_a = a.l / BLOCK_SIZE;
        int block_b = b.l / BLOCK_SIZE;

        if (block_a != block_b)
            return block_a < block_b;

        // odd-even r optimization: block parity se r ka sort direction flip
        if (block_a & 1)
            return a.r < b.r;
        else
            return a.r > b.r;
    }

    // ── add: index 'idx' ko current Mo window me include karo ──
    //   1) arr[idx] ki value ki freq array me frequency badhao
    //   2) agar freq exactly 1 ho gayi (pehli baar range me aayi) to distinct_count++
    //   3) freq > 1 matlab element pehle se tha — distinct count same rehta hai
    //   4) O(1) per add — sirf ek freq update aur shayad ek counter increment
    void add(int idx)
    {
        freq[arr[idx]]++;
        if (freq[arr[idx]] == 1)
            distinct_count++;  // pehli baar aaya -> naya distinct element
    }

    // ── remove: index 'idx' ko current Mo window se bahar nikalo ──
    //   1) arr[idx] ki value ki freq ghatao
    //   2) agar freq 0 ho gayi (element poori tarah range se chala gaya) to distinct_count--
    //   3) freq > 0 matlab element ab bhi range me hai — distinct count same
    //   4) O(1) per remove — freq decrement aur shayad counter decrement
    void remove(int idx)
    {
        freq[arr[idx]]--;
        if (freq[arr[idx]] == 0)
            distinct_count--;  // ab range me nahi bacha -> distinct kam
    }

    // ── get_answer: abhi active range ka distinct count return karo ──
    //   1) distinct_count har add/remove se incrementally maintain ho raha hai
    //   2) koi poori range scan nahi — seedha counter return karo
    //   3) process_queries har matched range ke baad is value ko store karti hai
    int get_answer()
    {
        return distinct_count;
    }

    // ── process_queries: saari queries offline Mo's order me answer karo ──
    //   1) queries ko compare() comparator se sort karo
    //   2) cur_l=0, cur_r=-1 se empty range shuru karo
    //   3) har query [L,R] ke liye 4 while loops: left/right expand phir shrink
    //   4) range match hone par answer[query.idx] = get_answer() store karo
    //   5) original idx se answers input query order me restore hote hain
    vector<int> process_queries(vector<Query> &queries)
    {
        int n = arr.size();
        int q = queries.size();

        sort(queries.begin(), queries.end(),
             [this](Query a, Query b)
             { return compare(a, b); });

        vector<int> answer(q);
        int cur_l = 0, cur_r = -1;  // shuru me empty range — koi element include nahi

        for (auto &query : queries)
        {
            int L = query.l, R = query.r;

            // Mo's pointer movement: pehle expand (add), phir shrink (remove)
            while (cur_l > L) add(--cur_l);       // left expand — cur_l ko L tak lao
            while (cur_r < R) add(++cur_r);       // right expand — cur_r ko R tak lao
            while (cur_l < L) remove(cur_l++);    // left shrink — extra left elements hatao
            while (cur_r > R) remove(cur_r--);    // right shrink — extra right elements hatao

            answer[query.idx] = get_answer();
        }

        return answer;
    }
};

// ── main: demo — sample array pe teen distinct-count queries chalao ──
//   1) fixed array aur teen range queries banao
//   2) MosAlgorithm object banao aur process_queries call karo
//   3) har query range ka distinct count print karo
int main()
{
    vector<int> arr = {1, 2, 1, 3, 2, 2, 4};
    MosAlgorithm mo(arr);

    vector<MosAlgorithm::Query> queries = {
        {0, 4, 0},
        {1, 5, 1},
        {2, 6, 2}
    };

    vector<int> answers = mo.process_queries(queries);

    cout << "Distinct elements in each query range:\n";
    for (int ans : answers)
    {
        cout << ans << "\n";
    }

    return 0;
}
