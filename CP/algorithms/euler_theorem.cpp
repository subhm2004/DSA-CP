#include <bits/stdc++.h>
using namespace std;

// ── gcd: Euclidean algorithm — coprime check ke liye ────────────────────────
int gcd(int a, int b) {
  a = abs(a);
  b = abs(b);
  while (b) {
    a %= b;
    swap(a, b);
  }
  return a;
}

// ════════════════════════════════════════════════════════════════════════════
// EULER'S THEOREM — a^φ(n) ≡ 1 (mod n) jab gcd(a,n) = 1
// ────────────────────────────────────────────────────────────────────────────
// φ(n) = 1 se n-1 tak kitne numbers n ke saath coprime hain
// Fermat's little theorem ka generalization (n composite bhi ho sakta hai)
// modExp se bada exponent efficiently compute karte hain
// ════════════════════════════════════════════════════════════════════════════

// ── eulerTotient: φ(n) nikalo prime factorization se ────────────────────────
//   1) result = n se shuru
//   2) har prime factor p ke liye: result -= result/p  (formula: n * Π(1 -
//   1/p)) 3) n ko p se completely divide karo 4) last me agar n > 1 (bacha
//   prime) -> result -= result/n
int eulerTotient(int n) {
  int result = n;
  for (int i = 2; i * i <= n; ++i) {
    if (n % i == 0) {
      while (n % i == 0)
        n /= i;
      result -= result / i; // i ke saare multiples count se hatao
    }
  }
  if (n > 1)
    result -= result / n;

  return result;
}

// ── modExp: a^b % mod binary exponentiation se ──────────────────────────────
//   1) result = 1, a = a % mod
//   2) b odd ho -> result = result * a % mod
//   3) a = a*a % mod, b /= 2 — exponent half karo
//   4) b > 0 tak repeat
int modExp(int a, int b, int mod) {
  int result = 1;
  a = a % mod;

  while (b > 0) {
    if (b % 2 == 1)
      result = (result * a) % mod;
    a = (a * a) % mod;
    b /= 2;
  }

  return result;
}

// ── eulerTheorem: verify a^φ(n) % n == 1 ──────────────────────────────────
//   1) phi_n = eulerTotient(n) compute karo
//   2) agar gcd(a,n) != 1 -> theorem apply nahi hoti, false
//   3) modExp(a, phi_n, n) == 1 check karo
bool eulerTheorem(int a, int n) {
  int phi_n = eulerTotient(n);

  if (gcd(a, n) == 1) {
    int result = modExp(a, phi_n, n);
    return result == 1;
  } else {
    return false;
  }
}

int main() {
  int a, n;
  cout << "Enter two numbers (a and n): ";
  cin >> a >> n;

  if (eulerTheorem(a, n)) {
    cout << "Euler's Theorem holds: a^φ(n) ≡ 1 (mod n)" << endl;
  } else {
    cout << "Euler's Theorem does not hold" << endl;
  }

  return 0;
}
