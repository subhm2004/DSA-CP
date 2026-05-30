# Kirchhoff's Matrix Tree Theorem

**Code:** [`kirchhoff_theorem.cpp`](./kirchhoff_theorem.cpp)  
**Reference:** [CP-Algorithms — Kirchhoff Theorem](https://cp-algorithms.com/graph/kirchhoff-theorem.html)

---

## Problem

Connected undirected graph diya hai (multi-edges allowed). **Kitne alag spanning trees** hain?

Ye **MST weight** nahi nikalta — sirf **count** karta hai.

```
Triangle (3-cycle)     → 3 trees (har baar ek edge chhod do)
Complete graph K4      → 16 trees  (= 4^(4−2), Cayley)
Path P4                → 1 tree    (already a tree)
```

---

## Kirchhoff's theorem (1847)

Matrices banao:

| Matrix | Definition |
|--------|------------|
| **A** (adjacency) | `A[u][v]` = u aur v ke beech kitni edges (parallel edges count) |
| **D** (degree) | `D[u][u]` = degree of u (loops + multi-edges included) |
| **L** (Laplacian) | `L = D − A` |

**Theorem:** `L` ke **saare cofactors equal** hain, aur wo value = **# spanning trees**.

### Practical shortcut

Last row **aur** last column hata do → `(n−1) × (n−1)` minor ka **determinant** = answer.

```text
L = |  3  -1  -1  -1 |
    | -1   3  -1  -1 |
    | -1  -1   3  -1 |
    | -1  -1  -1   3 |     (K4 example)

Delete row 4, col 4 → det(3×3) = 16
```

---

## Algorithm steps

1. Adjacency matrix / edge list se **Laplacian** build karo  
2. Koi bhi ek row + column delete (usually index `n−1`)  
3. **Gaussian elimination** se determinant — **O(n³)**  
4. `|det|` = spanning tree count  

Large `n` ya modulo problems → **determinant mod p** (code mein `countSpanningTreesMod`).

---

## Kab use karein?

| Situation | Kirchhoff? |
|-----------|------------|
| "Count spanning trees" / "Kitne labeled trees?" | ✅ |
| Graph **connected** undirected | ✅ Required |
| Multi-edges / self-loops | ✅ Laplacian mein include |
| Minimum **weight** spanning tree | ❌ → Kruskal / Prim |
| Directed graph | ❌ (alag directed matrix tree theorem) |
| `n > 500` exact count | ⚠️ O(n³) + overflow — use mod |

---

## Kirchhoff's circuit laws (intuition)

Electrical circuits mein **Laplacian** resistances se banta hai. Matrix tree theorem ka geometric meaning: effective resistance aur spanning tree count deeply connected hain. Details: [CP-Algo section](https://cp-algorithms.com/graph/kirchhoff-theorem.html#relation-to-kirchhoffs-circuit-laws).

---

## Special case — Cayley's formula

**Complete graph `K_n`** par spanning trees:

$$\tau(K_n) = n^{n-2}$$

Example: `K_6` → `6^4 = 1296` (demo isse verify karta hai).

---

## API (is repo)

```cpp
// Edge list (0-indexed, undirected; repeat edge = multi-edge)
Kirchhoff k(n, edges);
long long exact = k.countSpanningTreesExact();      // small n
long long mod   = k.countSpanningTreesMod(1e9+7);   // contests

// Or from adjacency matrix
Kirchhoff k2 = Kirchhoff::fromAdjacency(adj);
```

---

## Compile & run

```bash
g++ -std=c++17 -O2 CP/graphs/mst/kirchhoff_theorem.cpp -o sol && ./sol
```

Expected output:

```text
Triangle (3-cycle): 3 trees
Complete K4:        16 trees
Path P4:            1 tree
Complete K6 mod MOD:1296
```

---

## Kirchhoff vs MST algorithms

| | **Kirchhoff** | **Kruskal / Prim** |
|--|---------------|---------------------|
| Output | **Count** of trees | **One** min-weight tree |
| Input weights? | No (unweighted count) | Yes |
| Complexity | O(n³) | O(E log E) |
| Multi-edges | Handled in Laplacian | Handled in Kruskal |

---

## Related files

| File | Topic |
|------|--------|
| [`krushkal_algorithm.cpp`](./krushkal_algorithm.cpp) | Build one MST |
| [`second_best_mst.cpp`](./second_best_mst.cpp) | Second minimum weight tree |
| [`../../graphs/matrix_exponentiation/`](../../graphs/matrix_exponentiation/) | Matrix ops (different use) |

---

## Practice problems (CP-Algo)

- CODECHEF: Roads in Stars  
- SPOJ: Maze  
- CODECHEF: Complement Spanning Trees  

---

## Cheat sheet

```text
L = D − A
Delete any 1 row + 1 col → det = # spanning trees
O(n³) Gaussian | mod p for contests
K_n → n^(n−2)  (Cayley)
Graph must be connected
```
