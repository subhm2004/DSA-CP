# CP — Euler Path / Circuit

Eulerian path & circuit — degree checks + Hierholzer's algorithm.

**Path:** [`CP/graphs/euler_path/`](./)

## Files (5)

| File | LeetCode / Notes |
|------|------------------|
| [Hierholzers_algorithm.cpp](./Hierholzers_algorithm.cpp) | **Directed** — Hierholzer trail construction (canonical) |
| [directed_eulerian_path.cpp](./directed_eulerian_path.cpp) | Directed — check + Hierholzer (legacy) |
| [euler_path_directed_indegree.cpp](./euler_path_directed_indegree.cpp) | Directed — in/out degree check only |
| [euler_path_undirected_degree.cpp](./euler_path_undirected_degree.cpp) | Undirected — degree check |
| [printing_euler_path_undirected.cpp](./printing_euler_path_undirected.cpp) | **Undirected** — Hierholzer print |

## Quick reference — Directed graph

| Type | Degree condition |
|------|------------------|
| **Circuit** | Har node: `inDeg == outDeg` |
| **Path** | 1 start: `outDeg = inDeg + 1`, 1 end: `inDeg = outDeg + 1`, baaki equal |
| **Connectivity** | Weakly connected (direction ignore karke) |

**Start here:** [`Hierholzers_algorithm.cpp`](./Hierholzers_algorithm.cpp)

---
**Status:** ✅ Good coverage
