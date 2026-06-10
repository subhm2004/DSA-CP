#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// K-TH SMALLEST IN RANGE (Brute Force / Naive Approach)
// ────────────────────────────────────────────────────────────────────────────
// Problem: array ke range [L, R] me Kth smallest element kaunsa hai?
// Approach: us range ke elements nikaal ke sort karo, Kth element return karo.
// NOTE: Ye O((R-L+1) log(R-L+1)) hai — segment tree / merge sort tree se
//       O(log^2 n) me bhi ho sakta hai, yeh sirf simple demo hai.
// ════════════════════════════════════════════════════════════════════════════

// ── kthSmallest: range [L,R] me Kth smallest element dhundo ──
//   1) range [L, R] ke elements ko temp vector me copy karo (R+1 inclusive hai)
//   2) temp ko sort karo — ascending order me sabse chhota pehle aayega
//   3) K 1-indexed hai — matlab Kth smallest = sorted array me index K-1
//   4) temp[K-1] return karo — ye brute force O((R-L+1) log(R-L+1)) approach hai
//   5) NOTE: segment tree / merge sort tree se O(log² n) me bhi ho sakta hai
int kthSmallest(vector<int>& arr, int L, int R, int K) {
    // step 1: sirf query range ke elements nikaalo — baaki array ignore
    vector<int> temp(arr.begin() + L, arr.begin() + R + 1);
    
    // step 2: sort — chhote se bade order me arrange ho jaayenge
    sort(temp.begin(), temp.end());
    
    // step 3: Kth smallest = sorted me (K-1) index (K=1 → index 0 = minimum)
    return temp[K - 1];
}

int main() {
    vector<int> arr = {5, 1, 2, 3, 4};

    cout << kthSmallest(arr, 0, 4, 3) << endl; // range [0,4] me 3rd smallest = 3
    cout << kthSmallest(arr, 1, 4, 2) << endl; // range [1,4] me 2nd smallest = 2
    cout << kthSmallest(arr, 0, 2, 1) << endl; // range [0,2] me 1st smallest = 1
}
