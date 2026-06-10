#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// TOWER OF HANOI — Recursive Solution
// ────────────────────────────────────────────────────────────────────────────
// n disks: source(s) -> destination(d), helper(h) use karke
// Steps:
//   1) top n-1 disks s -> h (d as helper)
//   2) nth disk s -> d print karo
//   3) n-1 disks h -> d (s as helper)
// Total moves = 2^n - 1
// Complexity: O(2^n) moves
// ════════════════════════════════════════════════════════════════════════════

// ── tower: recursive Hanoi moves print karo ───────────────────────────────
//   1) base: n==0 -> kuch nahi karna
//   2) n-1 disks source se helper pe (destination ko temp helper banao)
//   3) nth disk source se destination move print
//   4) n-1 disks helper se destination pe (source ko temp helper banao)
void tower(int n, char s, char h, char d) {
  if (n == 0) {
    return;
  }
  tower(n - 1, s, d, h); // step 1: upper stack ko side me rakho
  cout << "Move disk " << n << " from " << s << " to " << d << endl;
  tower(n - 1, h, s, d); // step 3: side wale stack ko destination pe lao
}

int main() {
  int n;
  cout << "Enter the number of disks: ";
  cin >> n;
  cout << "Total moves: " << (1 << n) - 1 << endl; // 2^n - 1

  cout << "The moves are:\n";

  auto start = chrono::high_resolution_clock::now();
  tower(n, 'A', 'C', 'B'); // A=source, B=helper, C=destination
  auto end = chrono::high_resolution_clock::now();

  double duration = chrono::duration<double>(end - start).count();
  cout << "Execution time: " << duration << " seconds" << endl;

  return 0;
}
