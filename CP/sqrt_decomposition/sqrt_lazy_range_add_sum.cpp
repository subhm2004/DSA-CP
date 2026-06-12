#include <bits/stdc++.h>
using namespace std;

/*
 * ════════════════════════════════════════════════════════════════════════════
 * SQRT LAZY — Range Add + Range Sum Query
 * ════════════════════════════════════════════════════════════════════════════
 *
 * PROBLEM (FAANG variant — jab lazy seg tree overkill ho):
 *   1) rangeAdd(L, R, val) — [L,R] me sabko +val
 *   2) rangeSum(L, R)      — [L,R] ka sum
 *
 * APPROACH:
 *   Blocks ~sqrt(n):
 *     - FULL block → lazy tag (poora block +v pending)
 *     - PARTIAL block → elements individually update
 *
 * Query:
 *   partial scan + full blocks (blockSum + lazy*len)
 *
 * Time: build O(n) | rangeAdd O(sqrt n) | rangeSum O(sqrt n)
 * ════════════════════════════════════════════════════════════════════════════
 */

class SqrtLazyRangeSum {
private:
    vector<long long> arr;
    vector<long long> blockSum;
    vector<long long> lazy;  // pending add on full block
    int n, blockSize, numBlocks;

    int blockId(int i) const { return i / blockSize; }
    int blockStart(int b) const { return b * blockSize; }
    int blockEnd(int b) const { return min(n, (b + 1) * blockSize) - 1; }

    /*
     * pushBlock(b)
     * Full block b pe pending lazy ko elements + blockSum me apply karo.
     */
    void pushBlock(int b) {
        if (lazy[b] == 0) return;
        int s = blockStart(b), e = blockEnd(b);
        for (int i = s; i <= e; i++)
            arr[i] += lazy[b];
        blockSum[b] += lazy[b] * (e - s + 1);
        lazy[b] = 0;
    }

    /*
     * rebuildBlockSum(b)
     * Block ka sum arr se fresh nikaalo (partial update ke baad).
     */
    void rebuildBlockSum(int b) {
        blockSum[b] = 0;
        for (int i = blockStart(b); i <= blockEnd(b); i++)
            blockSum[b] += arr[i];
    }

public:
    SqrtLazyRangeSum(const vector<int>& a) {
        arr.assign(a.begin(), a.end());
        n = (int)arr.size();
        blockSize = max(1, (int)sqrt(n));
        numBlocks = (n + blockSize - 1) / blockSize;
        blockSum.assign(numBlocks, 0);
        lazy.assign(numBlocks, 0);
        for (int b = 0; b < numBlocks; b++)
            rebuildBlockSum(b);
    }

    /*
     * rangeAdd(L, R, val)
     * Left partial → element wise
     * Full blocks → lazy[b] += val
     * Right partial → element wise
     */
    void rangeAdd(int L, int R, long long val) {
        int bl = blockId(L), br = blockId(R);

        if (bl == br) {
            pushBlock(bl);
            for (int i = L; i <= R; i++) arr[i] += val;
            rebuildBlockSum(bl);
            return;
        }

        pushBlock(bl);
        for (int i = L; i <= blockEnd(bl); i++) arr[i] += val;
        rebuildBlockSum(bl);

        for (int b = bl + 1; b <= br - 1; b++)
            lazy[b] += val;

        pushBlock(br);
        for (int i = blockStart(br); i <= R; i++) arr[i] += val;
        rebuildBlockSum(br);
    }

    /*
     * rangeSum(L, R)
     * Partial scan + full blocks (blockSum + lazy*size)
     */
    long long rangeSum(int L, int R) {
        long long ans = 0;
        int bl = blockId(L), br = blockId(R);

        if (bl == br) {
            pushBlock(bl);
            for (int i = L; i <= R; i++) ans += arr[i];
            return ans;
        }

        pushBlock(bl);
        for (int i = L; i <= blockEnd(bl); i++) ans += arr[i];

        for (int b = bl + 1; b <= br - 1; b++)
            ans += blockSum[b] + lazy[b] * (blockEnd(b) - blockStart(b) + 1);

        pushBlock(br);
        for (int i = blockStart(br); i <= R; i++) ans += arr[i];

        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    SqrtLazyRangeSum st(a);

    cout << "Initial sum(0,8) = " << st.rangeSum(0, 8) << " (45)\n";

    st.rangeAdd(2, 6, 10);
    cout << "After add(2,6,+10):\n";
    cout << "  sum(0,8) = " << st.rangeSum(0, 8) << " (95)\n";
    cout << "  sum(2,6) = " << st.rangeSum(2, 6) << " (75)\n";
    cout << "  sum(0,1) = " << st.rangeSum(0, 1) << " (3, unchanged)\n";

    st.rangeAdd(0, 8, 1);
    cout << "After add(0,8,+1): sum(0,8) = " << st.rangeSum(0, 8) << "\n";

    return 0;
}
