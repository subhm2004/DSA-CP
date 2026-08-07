# CP — Competitive Programming

**237+ C++ files** | Codeforces / AtCoder / ICPC | Har topic ka apna folder + README

> Har folder ke andar `README.md` — files list, approach notes, **TODO** for missing templates.

## Core topics

| Topic | README |
|-------|--------|
| [Dynamic Programming](./dp/) | [Open →](./dp/README.md) |
| [Graphs](./graphs/) | [Open →](./graphs/README.md) |
| [Segment Tree](./segment_tree/) | [Open →](./segment_tree/README.md) |
| [Fenwick Tree](./fenwick_tree/) | [Open →](./fenwick_tree/README.md) |
| [Binary Search](./binary_search/) | [Open →](./binary_search/README.md) |
| [String Algorithms](./string_algorithms/) | [Open →](./string_algorithms/README.md) |
| [Number Theory](./number_theory/) | [Open →](./number_theory/README.md) |
| [Data Structures](./data_structures/) | [Open →](./data_structures/README.md) |
| [Mo's Algorithm](./mos_algorithm/) | [Open →](./mos_algorithm/README.md) |
| [LCA](./dp/LCA/) | [Open →](./dp/LCA/README.md) |
| [Trie](./trie/) | [Open →](./trie/README.md) |

## All folders

| Folder | README |
|--------|--------|
| [Algorithms / Math theorems](./algorithms/) | [Open →](./algorithms/README.md) |
| [Bit Manipulation](./bit_manipulation/) | [Open →](./bit_manipulation/README.md) |
| [Combinatorics](./combinatorics/) | [Open →](./combinatorics/README.md) |
| [Coordinate Compression](./coordinate_compression/) | [Open →](./coordinate_compression/README.md) |
| [Difference Array](./difference_array_technique/) | [Open →](./difference_array_technique/README.md) |
| [Euler Tour](./euler_tour/) | [Open →](./euler_tour/README.md) |
| [Geometry](./geometry/) | [Open →](./geometry/README.md) |
| [Matrix Exponentiation](./matrix_exponentiation/) | [Open →](./matrix_exponentiation/README.md) |
| [Math (FFT / NTT)](./math/) | [Open →](./math/README.md) |
| [Meet in the Middle](./bit_manipulation/meet_in_middle.cpp) | [Open →](./bit_manipulation/README.md) |
| [Monotonic Stack](./monotonic_stack/) | [Open →](./monotonic_stack/README.md) |
| [Monotonic Queue](./monotonic_queue/) | [Open →](./monotonic_queue/README.md) |
| [Numerical Methods](./numerical_methods/) | [Open →](./numerical_methods/README.md) |
| [Prefix Sum](./prefix_sum/) | [Open →](./prefix_sum/README.md) |
| [Sliding Window](./sliding_window/) | [Open →](./sliding_window/README.md) |
| [Sparse Table](./sparse_table/) | [Open →](./sparse_table/README.md) |
| [Sqrt Decomposition](./sqrt_decomposition/) | [Open →](./sqrt_decomposition/README.md) |
| [Two Pointers](./two_pointers/) | [Open →](./two_pointers/README.md) |

## TODO — contest templates to add

- [ ] `suffix_automaton.cpp`
- [ ] Stress test template (brute vs optimal)
- [ ] Game theory — Sprague-Grundy / Nim
- [ ] XOR (linear) basis
- [ ] Pollard's Rho factorization

## Added templates

- [x] `mod_int.cpp` → `number_theory/`
- [x] `ternary_search.cpp` → `binary_search/`
- [x] `aho_corasick.cpp` → `string_algorithms/`
- [x] `fft_ntt.cpp` → `math/`
- [x] `treap.cpp` (+ implicit) → `data_structures/`
- [x] `li_chao_segment_tree.cpp` → `segment_tree/`
- [x] `cp_template.cpp` (+ `custom_hash`) → [`../CP_Template/`](../CP_Template/)

## Compile

```bash
g++ -std=c++17 -O2 CP/path/to/file.cpp -o sol && ./sol
```

DSA (interviews): [`../DSA/`](../DSA/) | Template: [`../CP_Template/`](../CP_Template/)
