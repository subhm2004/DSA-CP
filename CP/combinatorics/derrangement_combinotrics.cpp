#include <iostream>
#include <chrono>

using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// DERANGEMENT — permutations jahan KOI element apni original position pe nahi
// ────────────────────────────────────────────────────────────────────────────
// Recurrence: D(n) = (n-1) * (D(n-1) + D(n-2))
//   n-th element: kisi (n-1) position pe jao × (pehle wale ka derangement)
// Base: D(0)=1 (empty), D(1)=0 (1 element apni jagah pe hi rahega)
// NOTE: ye recursive version O(2^n) — contest me DP use karo O(n)
// COMPLEX: recursive exponential  |  DP O(n)
// ════════════════════════════════════════════════════════════════════════════

// ── derangement: pure recursion (educational) ──
//   n=0 → 1 way (convention)
//   n=1 → 0 (impossible)
//   else → (n-1) * (D(n-1) + D(n-2))
int derangement(int n)
{
    if (n == 0)
        return 1;
    else if (n == 1)
        return 0;
    else
        return (n - 1) * (derangement(n - 1) + derangement(n - 2));
}

int main()
{
    int n;
    cout << "Enter the value of n: ";
    cin >> n;

    auto start = chrono::high_resolution_clock::now();
    int result = derangement(n);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double, micro> execution_time = end - start;

    cout << "Derangement of " << n << " is: " << result << endl;
    cout << "Execution time: " << execution_time.count() << " microseconds" << endl;

    return 0;
}
