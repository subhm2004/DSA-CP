# CP — Rerooting DP (Tree Rerooting)

Tree me **har node ko root** maan kar answer nikalna — 2-pass DFS se **O(n)**.

**Path:** [`CP/dp/rerooting_dp/`](./)

---

## Rerooting DP kya hai?

Normal tree DP ek fixed root (usually 0) se **subtree** answer nikalta hai.

Kabhi problem me chahiye: **har node as root** ka answer.

```
Naive: har node se DFS  →  O(n²)
Rerooting: 2 pass DFS   →  O(n)
```

### 2 Pass formula

| Pass | Naam | Order | Kya nikalta hai |
|------|------|-------|-----------------|
| **1** | `dfsDown` | Post-order (children pehle) | `down[u]` — sirf u ke subtree se answer |
| **2** | `dfsReroot` | Pre-order (parent se child) | Parent answer se child answer derive |

```
Pass 1: root=0 fixed, down[] + sz[] bharo
Pass 2: ans[root] = down[root], phir edge u→v cross karke ans[v] update
```

---

## Kab use karein?

| Signal | Example |
|--------|---------|
| "Har node se ..." | Sum of distances from each node |
| "Reroot the tree" | LC 834, tree DP reroot problems |
| "Answer for every rooting" | Max distance from each node |
| Brute force O(n²) tree | Optimize to O(n) with reroot |

### Problem words

- "sum of distances from each node"
- "for every node as root"
- "reroot" / "re-root"
- "contribution of each edge"

---

## Kab NAHI use karein?

| Situation | Better |
|-----------|--------|
| Sirf **ek root** se answer | Normal tree DP (`tree_dp/`) |
| **LCA / distance between two nodes** | Binary lifting (`LCA/`) |
| **General graph** (cycle) | Rerooting sirf **tree** pe |
| Subtree query fixed root | Single DFS enough |

---

## Kaise pata chalega? (Decision)

```
Tree problem hai?
    NO → rerooting nahi
    YES ↓

Har node as root ka alag answer chahiye?
    NO → normal tree DP / LCA
    YES ↓

Answer parent se child me "shift" ho sakta hai formula se?
    YES → Rerooting DP ✓
```

### Classic reroot formula (sum of distances)

Jab `u` se child `v` pe root shift:

```
ans[v] = ans[u] - sz[v] + (n - sz[v])
         ↑ v subtree 1 step close   ↑ baaki nodes 1 step far
```

---

## Files (3)

| File | Problem |
|------|---------|
| [tree_rerooting_template.cpp](./tree_rerooting_template.cpp) | **Master template** — down + reroot, sum of distances |
| [sum_of_distances_in_tree.cpp](./sum_of_distances_in_tree.cpp) | **LC 834** — sum of distances from each node |
| [max_distance_from_each_node.cpp](./max_distance_from_each_node.cpp) | Har node se max depth (up + down reroot) |

---

## Related folders

| Topic | Folder |
|-------|--------|
| Tree DP (fixed root) | [`../tree_dp/`](../tree_dp/) |
| LCA, distance two nodes | [`../LCA/`](../LCA/) |

---

## Ek line me yaad karo

> **Tree + har node as root + O(n²) brute force → Rerooting DP (2 DFS).**

Pehle `tree_rerooting_template.cpp` padho, phir specific problem file.

---
**Status:** 🟢 Good starter coverage
