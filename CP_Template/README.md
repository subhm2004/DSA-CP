# CP_Template — contest starter

Ek hi file — contest me copy karo, `solve()` likho, submit karo.

**Path:** [`CP_Template/`](./) · [`cp_template.cpp`](./cp_template.cpp)

[← Root README](../README.md) · [CP library →](../CP/) · [DSA →](../DSA/)

---

## Contest mode

```bash
cp CP_Template/cp_template.cpp sol.cpp
# solve() me logic likho, input.txt me sample paste karo
g++ -std=c++17 -O2 -DLOCAL sol.cpp -o sol && ./sol
```

Judge pe submit karte waqt `-DLOCAL` **mat** do — file redirect aur `dbg()` apne aap band ho jaate hain.

```bash
g++ -std=c++17 -O2 sol.cpp -o sol && ./sol     # judge/verify mode
```

---

## `-DLOCAL` kya on karta hai

| Feature | `-DLOCAL` ke saath | Judge pe (bina flag) |
|---------|--------------------|----------------------|
| Input | `input.txt` se padhta hai | `stdin` |
| Output | `output.txt` me likhta hai | `stdout` |
| `dbg(...)` | `stderr` pe print | poori tarah compile out |
| Timing | `[time] N ms` stderr pe | off |

`dbg()` `stderr` pe jaata hai, isliye judge ka output kabhi corrupt nahi hota — phir bhi submit se pehle flag hatana behtar hai (compile time bachta hai).

---

## `dbg()` — usage

```cpp
int n = 5; vector<int> a{1,2,3}; pair<int,int> p{4,9};
dbg(n, a, p);
```

```
[n, a, p] = 5, [1, 2, 3], (4, 9)
```

Vector, set, map, nested containers aur pairs — sab handle ho jaate hain (generic printer).

---

## Andar kya hai

| Cheez | Kaam |
|-------|------|
| Fast I/O | `sync_with_stdio(false)` + `cin.tie(nullptr)` |
| Aliases | `ll`, `ull`, `ld`, `pii`, `pll`, `vi`, `vll` |
| Macros | `all`, `rall`, `sz`, `pb`, `eb` |
| Constants | `MOD`, `INF` (4e18), `IINF`, `PI` |
| `ckmin` / `ckmax` | `if (ckmax(best, val))` — update + bataye ki badla ya nahi |
| `power(b, e, m)` | Binary exponentiation, `__int128` se overflow-safe |
| `custom_hash` | `unordered_map` ko Codeforces anti-hash test se bachata hai |

### custom_hash kyun chahiye

Codeforces pe log `unordered_map` ke against anti-hash tests banate hain — O(1) lookup O(n) ban jaata hai aur solution TLE. Ye splitmix64 + time-based seed use karta hai:

```cpp
unordered_map<ll, int, custom_hash> mp;   // safe
gp_hash_table<ll, int, custom_hash> gp;   // PBDS ke saath bhi chalega
```

---

## Multi-test

Default me `T` testcases padhta hai (Codeforces ka normal format):

```cpp
int T = 1;
cin >> T;        // ← single-test problem ho to ye line comment kar do
while (T--) solve();
```

---

## Verify

```bash
cd CP_Template
printf '2\n3\n1 2 3\n4\n10 20 30 40\n' > input.txt
g++ -std=c++17 -O2 -DLOCAL cp_template.cpp -o sol && ./sol
cat output.txt        # → 6 aur 100
```

Default `solve()` array ka sum print karta hai — placeholder hai, apne logic se replace karo.

---

## macOS note

PBDS (`ext/pb_ds`) Apple clang me nahi hai. `ordered_set` chahiye to real GNU g++ chahiye:

```bash
brew install gcc
g++-14 -std=c++17 -O2 -DLOCAL sol.cpp -o sol
```

Template khud PBDS use nahi karta, to system `g++` se theek chalta hai. Details: [`CP/data_structures/README.md`](../CP/data_structures/README.md).
