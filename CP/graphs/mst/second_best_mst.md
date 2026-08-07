# Second Best Minimum Spanning Tree

**Code:** [`second_best_mst.cpp`](./second_best_mst.cpp)  
**Reference:** [CP-Algorithms — Second best MST](https://cp-algorithms.com/graph/second_best_mst.html)

---

## Problem

Graph `G` diya hai. **MST** = minimum total weight spanning tree.

**Second best MST** = doosra sabse chhota spanning tree — MST se strictly bada, baaki sab se chhota.

```
MST weight = 19          Second best = 20
    0 ----10---- 1           (same graph, one edge swap)
    |\          /|
    6 5        15
    |  \      / |
    2---4-----3
```

---

## Key observation

Second-best MST **MST se exactly ek edge swap** se milta hai:

- Ek edge **hatao** jo MST mein hai → `e_old`
- Ek edge **lagao** jo MST mein nahi → `e_new`
- Naya tree spanning hai aur weight = `MST + w(e_new) - w(e_old)`

Isliye har non-MST edge try karo: cycle banega, us cycle ki **sabse bhari MST edge** nikalo, swap karo.

---

## Approach 1 — Naive (Kruskal repeat)

[CP-Algo naive method](https://cp-algorithms.com/graph/second_best_mst.html#using-kruskals-algorithm):

1. Kruskal se MST nikalo — **O(E log E)**
2. Har MST edge ko ek ek karke hatao, baaki edges se dubara MST — **O(V · E)**

**Total:** O(V · E) — chhote graphs / learning ke liye OK.

---

## Approach 2 — Kruskal + LCA (is repo)

**O(E log V)** — contest / large graphs ke liye.

| Step | Kya | Time |
|------|-----|------|
| 1 | Kruskal → MST tree + total weight | O(E log E) |
| 2 | MST ko root karo, **binary lifting** + har jump par **top-2 max edge weight** store | O(V log V) |
| 3 | Har **non-MST** edge `(u,v,w)`: tree path `u↔v` par max edge `k` nikalo | O(E log V) |
| 4 | Candidate = `MST + w - k`; minimum lo | O(E) |

### Kyon LCA?

Non-MST edge `(u,v)` add karo → **exactly ek cycle** banta hai = tree path `u` se `v` + ye edge.

Cycle se hataane wali sabse bhari MST edge = path par **maximum weight edge**.

Binary lifting se path max query **O(log V)**.

### Top-2 max kyon?

Agar non-MST edge ka weight **path ke max ke barabar** ho (multiple same-weight edges), to max ko hata kar swap invalid ho sakta hai — isliye **second maximum** bhi check karte hain (CP-Algo implementation).

---

## Kab use karein?

| Situation | Use? |
|-----------|------|
| "Second smallest spanning tree weight?" | ✅ |
| Har edge ke liye MST agar us edge **mandatory** ho | Related: CF "MST for each edge" |
| Normal MST only chahiye | ❌ [`krushkal_algorithm.cpp`](./krushkal_algorithm.cpp) / [`prims_algorithm.cpp`](./prims_algorithm.cpp) |
| Graph disconnected | ❌ spanning tree exist nahi karta |

---

## API (is repo)

```cpp
SecondBestMST solver(n);
auto [mstWeight, secondBest] = solver.solve(edges);
// edges: vector<Edge{u, v, w, id}> — 0-indexed vertices, unique id per edge
```

---

## Compile & run

```bash
g++ -std=c++17 -O2 CP/graphs/mst/second_best_mst.cpp -o sol && ./sol
```

Demo output:
- MST = **19**
- Second best = **20**

---

## Related files

| File | Topic |
|------|--------|
| [`krushkal_algorithm.cpp`](./krushkal_algorithm.cpp) | MST — Kruskal |
| [`prims_algorithm.cpp`](./prims_algorithm.cpp) | MST — Prim |
| [`../../dp/LCA/LCA_Binary_Lifting.cpp`](../../dp/LCA/LCA_Binary_Lifting.cpp) | LCA preprocessing |

---

## Practice

- [Codeforces — Minimum spanning tree for each edge](https://codeforces.com/contest/1178/problem/E) (related technique)

---

## Cheat sheet

```text
Observation : second best = MST − one edge + one non-MST edge
Naive       : O(V·E)  — remove each MST edge, re-Kruskal
Fast        : O(E log V) — LCA max edge on tree path
Check       : top-2 max on path (equal weight tie)
```
