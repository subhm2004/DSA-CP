/*
 * ============================================================================
 * TOPIC    : Backtracking — Palindrome Partitioning
 * FILE     : palindrome_partitioning.cpp
 * PROBLEM  : Partition string so every part is palindrome
 * LEETCODE : 131 — Palindrome Partitioning
 * APPROACH : Try all cuts; check palindrome for substring
 * COMPLEX  : Time: O(n * 2^n)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// PALINDROME PARTITIONING — string ko aise todo ki har part palindrome ho
// ────────────────────────────────────────────────────────────────────────────
// Funda: start se har possible end tak substring try karo
// Palindrome ho to path me add karo, baaki string par recurse
// COMPLEX: Time O(n * 2^n)  |  Space O(n)
// ════════════════════════════════════════════════════════════════════════════

class Solution {
    vector<vector<string>> ans;
    vector<string> path;

    // ── isPal: string palindrome hai ya nahi check ────────────────────────
    //   1) two pointers l=0, r=end
    //   2) l<r tak characters compare karo
    //   3) mismatch -> false, warna true
    bool isPal(const string &s) {
        int l = 0, r = s.size() - 1;
        while (l < r)
            if (s[l++] != s[r--]) return false; // aage-piche char match nahi
        return true;
    }

    // ── bt: start index se aage partition try karo ─────────────────────────
    //   1) start == end -> poora string partition ho gaya, path save
    //   2) end ko start se n-1 tak move karke har substring try
    //   3) substring palindrome nahi to skip
    //   4) valid part path me daalo, end+1 se recurse
    //   5) backtrack: pop_back karke agla cut try
    void bt(const string &s, int start) {
        if (start == (int)s.size()) {
            ans.push_back(path); // saare parts palindrome — valid partition
            return;
        }
        for (int end = start; end < (int)s.size(); end++) {
            string sub = s.substr(start, end - start + 1); // current candidate part
            if (!isPal(sub)) continue; // ye cut valid nahi — aage badhao end
            path.push_back(sub);
            bt(s, end + 1); // baaki string (end+1 se) partition karo
            path.pop_back(); // is part ko hatao — longer/shorter cut try hoga
        }
    }

public:
    // ── partition: saari valid palindrome partitions return ────────────────
    //   1) start=0 se bt chalao
    //   2) ans return
    vector<vector<string>> partition(string s) {
        bt(s, 0);
        return ans;
    }
};

// ── main: "aab" ke 2 partitions verify ─────────────────────────────────────
//   1) partition call
//   2) size print — [["a","a","b"], ["aa","b"]]
int main() {
    cout << Solution().partition("aab").size() << endl; // 2
    return 0;
}
