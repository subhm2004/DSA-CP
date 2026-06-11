# CP — LCA (Lowest Common Ancestor)

Tree par LCA aur related queries — C++ templates with demos.

**Path:** [`CP/dp/LCA/`](./)

## Files (4)

| File | Approach | Preprocess | Query | Notes |
|------|----------|------------|-------|-------|
| [LCA_Binary_Lifting.cpp](./LCA_Binary_Lifting.cpp) | Binary Lifting | O(n log n) | O(log n) | LCA + Kth ancestor, detailed Hinglish comments |
| [LCA_Euler_Tour_RMQ.cpp](./LCA_Euler_Tour_RMQ.cpp) | Euler Tour + Sparse Table | O(n log n) | **O(1)** | Static tree, zyada LCA queries hon to best |
| [LCA_from_adjacency.cpp](./LCA_from_adjacency.cpp) | Edges → DFS → Binary Lifting | O(n log n) | O(log n) | **1-indexed**, `vector<vector<int>> edges` se direct build |
| [tree_distance_and_path.cpp](./tree_distance_and_path.cpp) | Binary Lifting extension | O(n log n) | O(log n) | `distance(u,v)` + `kthOnPath(u,v,k)` |

## Kab kaunsa use karein?

| Situation | Use |
|-----------|-----|
| LCA + kth ancestor dono chahiye | Binary Lifting |
| Sirf LCA, bahut saari queries | Euler Tour + RMQ |
| Input edges mein hai | `LCA_from_adjacency.cpp` |
| Path length / k-th node on path | `tree_distance_and_path.cpp` |

## Key formulas

```
distance(u, v) = depth[u] + depth[v] - 2 * depth[lca(u, v)]

kthOnPath(u, v, k):
  distToLca = depth[u] - depth[lca(u, v)]
  if k <= distToLca  -> getKthAncestor(u, k)
  else               -> getKthAncestor(v, distance(u,v) - k)
```

## Related (repo mein aur kahan)

| Topic | Path |
|-------|------|
| Virtual Tree (key nodes + LCAs) | [`CP/graphs/virtual_tree/`](../../graphs/virtual_tree/) |
| Euler Tour (subtree queries) | [`CP/euler_tour/`](../../euler_tour/) |
| Sparse Table (RMQ building block) | [`CP/sparse_table/`](../../sparse_table/) |
| LCA in BST (sorted property) | [`DSA/bst/lca_in_bst.cpp`](../../../DSA/bst/lca_in_bst.cpp) |

## TODO

- [ ] Path min/max/sum with binary lifting (`maxUp[node][j]`)
- [ ] HLD for path updates

---
**Status:** 🟢 Good coverage
