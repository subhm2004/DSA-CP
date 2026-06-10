#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// MO'S ALGORITHM — Range Sum Query (Offline)
// ────────────────────────────────────────────────────────────────────────────
// Problem: bahut saari range sum queries [L, R] offline answer karni hain.
// Approach: Mo's algorithm — queries sort karo, cur_l/cur_r pointers se range
//           expand/shrink karte jao, current_sum maintain karo.
//
// Key idea:
//   cur_l, cur_r  -> current range [cur_l, cur_r]
//   add(idx)      -> current_sum += arr[idx]
//   remove(idx)   -> current_sum -= arr[idx]
//
// Complexity: O((n + q) * sqrt(n)) amortized
// ════════════════════════════════════════════════════════════════════════════

class MosAlgorithmSum
{
private:
    vector<int> arr;
    int current_sum;   // abhi ke range [cur_l, cur_r] ka sum
    int BLOCK_SIZE;

public:
    // ── MosAlgorithmSum: constructor — array aur block size setup ──
    //   1) input array ko member 'arr' me copy kar lo
    //   2) n = arr.size() lo aur BLOCK_SIZE = sqrt(n) set karo (Mo's block width)
    //   3) current_sum = 0 rakho kyunki shuru me koi range active nahi hoti
    MosAlgorithmSum(const vector<int> &input)
    {
        arr = input;
        int n = arr.size();
        BLOCK_SIZE = sqrt(n);
        current_sum = 0;
    }

    struct Query
    {
        int l, r, idx;  // range [l,r] + original query index
    };

    // ── compare: Mo's block-wise sorting (odd-even r optimization) ──
    //   1) dono queries ka left block nikalo: block = l / BLOCK_SIZE
    //   2) agar blocks alag hain to chhota block pehle — isse l pointer kam hilta hai
    //   3) same block me odd-even trick: odd block me r ascending, even me r descending
    //   4) is zig-zag order se cur_r pointer idhar-udhar kam bounce karta hai
    bool compare(const Query &a, const Query &b)
    {
        int block_a = a.l / BLOCK_SIZE;
        int block_b = b.l / BLOCK_SIZE;

        if (block_a != block_b)
            return block_a < block_b;

        // odd block -> r badhte hue; even block -> r ghate hue (Mo's optimization)
        if (block_a & 1)
            return a.r < b.r;
        else
            return a.r > b.r;
    }

    // ── add: index ko current Mo window me include karo ──
    //   1) arr[idx] ki value current_sum me add karo
    //   2) ye tab call hota hai jab cur_l left expand ho ya cur_r right expand ho
    //   3) O(1) operation — sirf ek element range me aaya, sum turant update
    void add(int idx)
    {
        current_sum += arr[idx];
    }

    // ── remove: index ko current Mo window se bahar nikalo ──
    //   1) arr[idx] ki value current_sum se subtract karo
    //   2) ye tab call hota hai jab cur_l right shrink ho ya cur_r left shrink ho
    //   3) O(1) operation — element range se gaya, sum se hata diya
    void remove(int idx)
    {
        current_sum -= arr[idx];
    }

    // ── get_answer: abhi active range ka sum return karo ──
    //   1) current_sum already har add/remove se maintain ho raha hai
    //   2) koi extra loop nahi — seedha stored sum return karo
    //   3) process_queries har query ke baad isse answer store karti hai
    int get_answer()
    {
        return current_sum;
    }

    // ── process_queries: Mo's order me saari queries offline answer karo ──
    //   1) queries ko compare() se sort karo taaki pointer movement kam ho
    //   2) cur_l=0, cur_r=-1 se shuru karo (empty range — kuch include nahi)
    //   3) har query [L,R] ke liye 4 while loops se range adjust karo (add/remove)
    //   4) jab range match ho jaye, answers[query.idx] me get_answer() store karo
    //   5) original idx use karke answers ko input order me wapas map karte hain
    vector<int> process_queries(vector<Query> &queries)
    {
        int n = arr.size();
        int q = queries.size();

        sort(queries.begin(), queries.end(),
             [this](Query a, Query b)
             { return compare(a, b); });

        vector<int> answers(q);
        int cur_l = 0, cur_r = -1;  // cur_r=-1 matlab abhi koi element include nahi

        for (auto &query : queries)
        {
            int L = query.l, R = query.r;

            // Mo's expand/shrink: pehle expand (add), phir shrink (remove)
            while (cur_l > L) add(--cur_l);       // left side expand — cur_l ko L tak lao
            while (cur_r < R) add(++cur_r);       // right side expand — cur_r ko R tak lao
            while (cur_l < L) remove(cur_l++);      // left shrink — extra left elements hatao
            while (cur_r > R) remove(cur_r--);      // right shrink — extra right elements hatao

            answers[query.idx] = get_answer();
        }

        return answers;
    }
};

// ── main: demo — sample array pe teen range-sum queries chalao ──
//   1) fixed array aur teen queries banao
//   2) MosAlgorithmSum object banao aur process_queries call karo
//   3) har query ka computed sum print karo
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
