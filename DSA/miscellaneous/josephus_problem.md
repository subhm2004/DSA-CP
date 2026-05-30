# Josephus Problem

**Code:** [`josephus_problem.cpp`](./josephus_problem.cpp)  
**Reference:** [CP-Algorithms — Josephus problem](https://cp-algorithms.com/others/josephus_problem.html)

---

## Statement

`n` log `1..n` ek circle mein hain. `k` count karke us person ko hatao, phir agle se dubara — jab tak **ek** na bache.

**Example:** `n=7`, `k=3` → survivor = **4**

```
1 → 2 → 3 → 4 → 5 → 6 → 7 → (circle)
Remove 3, then 6, then 2, then 7, then 4, then 1 → last = 5? 

CP-Algo table: J(7,3) = 4 ✓ (code se verify)
```

---

## Approaches (is repo)

| Function | Time | Kab use |
|----------|------|---------|
| `josephusOn(n, k)` | **O(n)** | General, simple, contests |
| `josephusFast1Indexed(n, k)` | **O(k log n)** | `k` chhota, `n` bahut bada |
| `josephusK2(n)` | **O(1)** | Sirf `k = 2` |
| `josephusSimulate(n, k)` | O(n²) | Small `n` verify only |

---

## Recurrence (0-indexed)

Positions `0 .. n-1` maan kar:

$$J(1, k) = 0$$

$$J(n, k) = (J(n-1, k) + k) \bmod n$$

**1-indexed answer** = `J(n,k) + 1`

### O(n) loop (CP-Algo)

```cpp
int res = 0;
for (int i = 1; i <= n; i++)
    res = (res + k) % i;
return res + 1;
```

---

## k = 2 — closed form

$$J_{n,2} = 1 + 2\left(n - 2^{\lfloor \log_2 n \rfloor}\right)$$

Sab odd numbers sequence, har power-of-2 par reset to 1.

---

## O(k log n) idea

Jab `k << n`, ek pass mein `⌊n/k⌋` log hata sakte ho, phir recursive chhota `n'`.

Roughly **O(k log n)** iterations — [CP-Algo derivation](https://cp-algorithms.com/others/josephus_problem.html#modeling-a-o-k-log-n-solution).

---

## Compile & run

```bash
g++ -std=c++17 -O2 DSA/miscellaneous/josephus_problem.cpp -o sol && ./sol
```

---

## Related

| Topic | File |
|-------|------|
| Tortoise & Hare (cycle) | [`../linked_list/tortoise_algo.cpp`](../linked_list/tortoise_algo.cpp) |
| Old misc folder | [`../misc/`](../misc/) |

---

## Cheat sheet

```text
General     → O(n) loop: res = (res + k) % i
k = 2       → 1 + 2*(n - highestPowerOf2<=n)
k small     → josephusFast O(k log n)
Answer      → 1-indexed (person number, not index)
```
