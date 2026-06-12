# CP — Merge Sort Tree

Segment tree jahan har node apne range ka **sorted vector** rakhta hai.

**Path:** [`CP/segment_tree/merge_sort_tree/`](./)

---

## Merge Sort Tree kya hai?

Normal segment tree node me **ek number** hota hai (sum, min, max).

Merge Sort Tree me har node me **sorted list** hoti hai — us segment ke saare elements sorted order me.

```
Array: [3, 1, 4, 2]

         [1,2,3,4]          ← root: poori array sorted
        /         \
   [1,3]           [2,4]    ← left/right halves sorted
   /   \           /   \
 [1]  [3]        [2]  [4]  ← leaves
```

Query time par `lower_bound` / `upper_bound` se count nikalte ho — isliye **order statistics** (rank, k-th, count by value) possible hai.

---

## Kab use karein? (Signals — problem padhte hi pehchano)

Merge Sort Tree tab socho jab **teen cheezein ek saath** dikhein:

| Signal | Matlab |
|--------|--------|
| **1. Range query** | `[L, R]` subarray par answer chahiye |
| **2. Value / order matter** | Element ki **value** se compare/count karna hai — sum/min/max se kaam nahi chalega |
| **3. Static ya kam updates** | Array build ke baad mostly **queries** — heavy point updates nahi |

### Problem statement me ye words dikhein → Merge Sort Tree try karo

- "K-th smallest / largest **in range**"
- "Kitne elements **< K** / **> K** / **[A, B]** me hain range me"
- "Range **median**"
- "**Inversions** in subarray `[L, R]`"
- "Count pairs/triplets with **value condition** in range"
- "Order statistic", "rank in range", "count smaller elements"

### Example — haan, Merge Sort Tree

```
Array [5,1,3,2,4]. Q queries:
  (L,R,K) → K-th smallest in [L,R]           → kth_smallest_in_range.cpp
  (L,R,K) → count of elements < K in [L,R]   → count_smaller_than_k_in_range.cpp
  (L,R)   → inversions only inside [L,R]     → count_inversions_in_range.cpp
```

---

## Kab NAHI use karein? (Alternatives)

| Situation | Better choice | Kyun |
|-----------|---------------|------|
| Sirf **sum / min / max** range chahiye | Normal seg tree / Fenwick | Order ki zarurat nahi |
| **Bahut saare point updates** + order queries | Merge Sort Tree slow ho jata | Rebuild ya advanced DS chahiye |
| Sirf **poori array** me inversions (ek baar) | Fenwick Tree / Merge Sort | O(n log n), zyada simple |
| **Prefix** me k-th smallest (0..i) | Persistent Seg Tree | Merge sort tree range-fixed hai |
| **Distinct count** heavy queries, static array | Mo's Algorithm | Amortized faster kabhi-kabhi |
| Values **1..n** range me, sirf count | Fenwick on compressed values | O(log n) per query, kam memory |
| **2D** grid queries | 2D seg tree / wavelet | Merge sort tree 1D hai |

### Quick rule

```
Value/rank/count by value in [L,R]?  → Merge Sort Tree socho
Sirf aggregate (sum/min/max)?        → Normal seg tree
Sirf prefix, versions?               → Persistent seg tree / BIT
```

---

## Kaise pata chalega? (Decision flow)

```
Problem padho
    │
    ├─ Query [L, R] range par hai?
    │       NO  → merge sort tree nahi (ya poori array = L=0, R=n-1)
    │       YES ↓
    │
    ├─ Answer element ki VALUE / ORDER se nikalta hai?
    │   (count < X, k-th, median, inversions, value range count)
    │       NO  → sum/min/max seg tree ya Fenwick
    │       YES ↓
    │
    ├─ Updates kitne hain?
    │       Bahut point updates → merge sort tree avoid (rebuild costly)
    │       Static / offline     → merge sort tree ✓
    │
    └─ Kaunsa exact query?
            ├─ K-th smallest        → kth_smallest_in_range.cpp
            ├─ count < K            → count_smaller_than_k_in_range.cpp
            ├─ count > K            → count_greater_than_k_in_range.cpp
            ├─ count in [A, B]      → count_in_value_range.cpp
            ├─ distinct in range    → count_unique_in_range.cpp
            ├─ inversions in range  → count_inversions_in_range.cpp
            ├─ triplet inversions   → count_triplet_inversions.cpp
            ├─ range median         → range_median.cpp
            └─ poori array inversions → inversion_count.cpp
```

---

## Problem type → File map

| Problem me kya maang rahe ho | File | Core function |
|------------------------------|------|---------------|
| K-th smallest in `[L,R]` | `kth_smallest_in_range.cpp` | `kthSmallest(L,R,K)` — BS on value + `countLessEqual` |
| Kitne `< K` in `[L,R]` | `count_smaller_than_k_in_range.cpp` | `countLess(L,R,K)` |
| Kitne `> K` in `[L,R]` | `count_greater_than_k_in_range.cpp` | `size - upper_bound(K)` |
| Kitne values in `[A,B]` | `count_in_value_range.cpp` | `countInRange(L,R,A,B)` |
| Kitne **unique** in `[L,R]` | `count_unique_in_range.cpp` | collect + sort (Mo's bhi option) |
| Inversions in poori array | `inversion_count.cpp` | Fenwick bhi chalega; yahan MST se |
| Inversions in `[L,R]` only | `count_inversions_in_range.cpp` | har `i` ke liye `countLessEqual` |
| Triplets `i<j<k`, `arr[i]>arr[j]>arr[k]` | `count_triplet_inversions.cpp` | middle `j` fix, left×right |
| Median of `[L,R]` | `range_median.cpp` | `kthSmallest` se middle element |
| Sab kuch ek class me | `merge_sort_tree_template.cpp` | master template |

---

## Normal Seg Tree vs Merge Sort Tree

| | Normal Seg Tree | Merge Sort Tree |
|--|-----------------|-----------------|
| Node stores | 1 number (sum/min/max) | Sorted vector |
| Build | O(n) | O(n log n) |
| Query | O(log n) | O(log² n) |
| Space | O(n) | O(n log n) |
| K-th smallest | ❌ | ✅ |
| Count by value | ❌ | ✅ |
| Sum / min / max | ✅ | Overkill |

---

## Complexity (yaad rakho)

| Operation | Time |
|-----------|------|
| Build | O(n log n) |
| Query (count / k-th) | O(log² n) — log n nodes × log n binary search |
| Space | O(n log n) |
| Point update | O(log n) vector edit — **practically rebuild better** agar updates zyada hon |

Interview / contest me complexity bolna: **"Build n log n, query log squared n, space n log n"**.

---

## 3 Query Cases (har function me same)

Node `[l, r]` vs query `[ql, qr]`:

1. **No overlap** → return 0 / skip  
2. **Full overlap** → seedha is node ke sorted vector par `lower_bound` / `upper_bound`  
3. **Partial** → left child + right child, result merge (count add / XOR nahi, sum of counts)

Yahi pattern `countLess`, `countLessEqual`, `kthSmallest` sab me repeat hota hai.

---

## Files (10)

| File | Problem / Use |
|------|----------------|
| [merge_sort_tree_template.cpp](./merge_sort_tree_template.cpp) | **Master template** — poora class + saari queries |
| [kth_smallest_in_range.cpp](./kth_smallest_in_range.cpp) | Range `[L,R]` me K-th smallest |
| [count_smaller_than_k_in_range.cpp](./count_smaller_than_k_in_range.cpp) | W queries `[L,R,K]` — kitne elements `< K` in `[L,R]` |
| [count_greater_than_k_in_range.cpp](./count_greater_than_k_in_range.cpp) | W queries `[L,R,K]` — kitne elements `> K` in `[L,R]` |
| [count_unique_in_range.cpp](./count_unique_in_range.cpp) | Q queries `[L,R]` — kitne **unique** elements in `[L,R]` |
| [count_in_value_range.cpp](./count_in_value_range.cpp) | Range me kitne elements `[A,B]` value range me |
| [inversion_count.cpp](./inversion_count.cpp) | Poori array me inversion pairs |
| [count_inversions_in_range.cpp](./count_inversions_in_range.cpp) | Q queries `[L,R]` — inversions sirf range ke andar |
| [count_triplet_inversions.cpp](./count_triplet_inversions.cpp) | Triplets `i<j<k` with `arr[i]>arr[j]>arr[k]` |
| [range_median.cpp](./range_median.cpp) | Range ka median |

---

## Ek line me yaad karo

> **Range `[L,R]` + value/order/count chahiye + array mostly static → Merge Sort Tree.**

Pehle `merge_sort_tree_template.cpp` padho, phir specific problem wali file kholo.

---
**Status:** 🟢 Good coverage
