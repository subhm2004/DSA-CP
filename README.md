# DSA & Competitive Programming — C++ Repository

> A personal collection of **400+ C++ implementations** covering Data Structures, Algorithms, and Competitive Programming topics — from basics to advanced.

**Author:** [Shubham Malik](https://github.com/subhm2004)  
**GitHub:** [subhm2004/DSA](https://github.com/subhm2004/DSA)

---

## Table of Contents

- [About This Repository](#about-this-repository)
- [Quick Start](#quick-start)
- [Repository Layout](#repository-layout)
- [Index — Root Level Files](#index--root-level-files)
- [Index — Folder-wise](#index--folder-wise)
  - [arrays.cpp](#arrayscpp)
  - [basic DSA.cpp](#basic-dsacpp)
  - [basicmaths.cpp](#basicmathscpp)
  - [basicpattern.cpp](#basicpatterncpp)
  - [binarysearch.cpp](#binarysearchcpp)
  - [BST.cpp](#bstcpp)
  - [chararray.cpp](#chararraycpp)
  - [CP_Algorithms](#cp_algorithms)
  - [DSA.cpp](#dsacpp)
  - [Graphs](#graphs)
  - [Greedy](#greedy)
  - [heaps.cpp](#heapscpp)
  - [linkedlist.cpp](#linkedlistcpp)
  - [OOP's.cpp](#oopscpp)
  - [queues.cpp](#queuescpp)
  - [recursion.cpp](#recursioncpp)
  - [segment_tree](#segment_tree)
  - [stacks.cpp](#stackscpp)
  - [strings.cpp](#stringscpp)
  - [trees.cpp](#treescpp)
  - [vector.cpp](#vectorcpp)
- [Topic Coverage Summary](#topic-coverage-summary)
- [VS Code Setup](#vs-code-setup)
- [Contributing](#contributing)
- [License](#license)

---

## About This Repository

This repo is a **learning and reference library** for DSA and CP in C++. Each file typically contains a self-contained solution or template for a specific concept or problem.

**What's inside:**
- Fundamentals — arrays, strings, linked lists, stacks, queues, heaps, trees, BST
- Classic algorithms — sorting, searching, recursion, DP, greedy
- Advanced CP — graphs, segment trees, Fenwick trees, Mo's algorithm, string hashing, geometry
- OOP basics in C++

**Note:** Most topic folders are named with a `.cpp` suffix (e.g. `arrays.cpp/`, `Graphs/`). This is the author's convention — treat them as regular directories.

---

## Quick Start

```bash
# Clone the repository
git clone https://github.com/subhm2004/DSA.git
cd DSA

# Compile and run any file (example)
g++ -std=c++17 Graphs/Dijkstra_algo.cpp -o dijkstra
./dijkstra
```

**Requirements:** C++ compiler (`g++` / `clang++`), C++11 or later recommended.

---

## Repository Layout

```
C++/
├── arrays.cpp/          # Array problems & 2D matrix operations
├── basic DSA.cpp/       # Beginner DSA — sorting, strings, basics
├── basicmaths.cpp/      # Number theory — primes, GCD, sieve
├── basicpattern.cpp/    # Pattern printing problems
├── binarysearch.cpp/    # Binary search variants & problems
├── BST.cpp/             # Binary Search Tree operations
├── chararray.cpp/       # C-style char array basics
├── CP_Algorithms/       # Competitive programming math & theorems
├── DSA.cpp/             # Mixed DSA practice
├── Graphs/              # Graph algorithms (65+ files)
├── Greedy/              # Greedy algorithms
├── heaps.cpp/           # Heap data structure & problems
├── linkedlist.cpp/      # Linked list operations
├── OOP's.cpp/           # Object-Oriented Programming in C++
├── queues.cpp/          # Queue, Deque, circular queue
├── recursion.cpp/       # Recursion & backtracking
├── segment_tree/        # Segment tree, Fenwick tree, Mo's algo
├── stacks.cpp/          # Stack problems & monotonic stack
├── strings.cpp/         # String manipulation
├── trees.cpp/           # Binary tree traversals & problems
├── vector.cpp/          # STL vector usage
└── *.cpp                # Standalone advanced topic files (root)
```

---

## Index — Root Level Files

Standalone implementations at the repository root, grouped by topic.

### String Algorithms & Hashing

| File | Description |
|------|-------------|
| `KMP_string_matching_algo.cpp` | KMP pattern matching algorithm |
| `Z_algorithm_string_matching.cpp` | Z-algorithm for string matching |
| `Rabin_karp_single_hashing_string_matching.cpp` | Rabin-Karp with single hash |
| `Rabin_karp_double_hashing_String_matching.cpp` | Rabin-Karp with double hashing |
| `Rabin_karp_double_hashing_multiple_occurences.cpp` | Rabin-Karp — multiple occurrences |
| `Rabin_karp_dynamic_window_size.cpp` | Rabin-Karp with dynamic window |
| `Rolling_hash_dynamic_window_Size.cpp` | Rolling hash with dynamic window |
| `Rolling_hash_palindrom_check.cpp` | Palindrome check via rolling hash |
| `dynamic_rolling_hash_of_a_sub_String.cpp` | Dynamic rolling hash for substrings |
| `generate_palindromes.cpp` | Generate palindromes |

### Range Queries & Data Structures

| File | Description |
|------|-------------|
| `Fenwick_tree.cpp` | Fenwick tree (Binary Indexed Tree) |
| `lazy_propogation.cpp` | Lazy propagation on segment tree |
| `Mo_s_algorithm_distinct_element_in_range_query.cpp` | Mo's algorithm — distinct elements in range |
| `Mos_algo_range_query_sum.cpp` | Mo's algorithm — range sum query |
| `Mos_algo_with_update.cpp` | Mo's algorithm with point updates |
| `prefix_sum_2D_array.cpp` | 2D prefix sum |
| `coordinate_compression` | Coordinate compression (binary) |

### Trees & Graphs (Advanced)

| File | Description |
|------|-------------|
| `Euler_tour_on_trees.cpp` | Euler tour technique on trees |
| `euler.cpp` | Euler-related implementation |
| `Hierholzers_algorithm.cpp` | Hierholzer's algorithm for Euler path/circuit |
| `lca_some_Adv_functions.cpp` | LCA — advanced helper functions |
| `convex_hull.cpp` | Convex hull (computational geometry) |

### Math, Number Theory & Combinatorics

| File | Description |
|------|-------------|
| `Base_n.cpp` | Base-N number conversion |
| `binay_expo.cpp` | Binary exponentiation |
| `matrix_expo.cpp` | Matrix exponentiation |
| `newton_raphson_method.cpp` | Newton-Raphson method |
| `Kth_root_of_a_number_newton_rapson.cpp` | Kth root via Newton-Raphson |
| `derrangement_combinotrics.cpp` | Derangements & combinatorics |
| `BitsQuestion2.cpp` | Bit manipulation problems |
| `Tower_of_hanoi.cpp` | Tower of Hanoi |

### Dynamic Programming & Sorting

| File | Description |
|------|-------------|
| `lis_dp.cpp` | Longest Increasing Subsequence (DP) |
| `merge_Sort.cpp` | Merge sort |
| `sorting.cpp` | Sorting algorithms |

### Misc / Practice

| File | Description |
|------|-------------|
| `basicpractice.cpp` | General practice |
| `practice1.cpp` | Practice problems |
| `loops.cpp` | Loop basics |
| `queuebasics.cpp` | Queue basics |
| `stack.cpp` | Stack basics |

---

## Index — Folder-wise

### `arrays.cpp/`

Array fundamentals, 2D arrays, and classic array problems.

| File | Topic |
|------|-------|
| `array1.cpp` – `array4.cpp` | Basic array operations |
| `2darray.cpp`, `2Darraylec2.cpp`, `2Darraylec3.cpp` | 2D array basics |
| `linearsearch.cpp`, `binarysearch.cpp` | Search in arrays |
| `twosum.cpp`, `printpairs.cpp` | Pair sum problems |
| `reverse.cpp`, `rotatearray.cpp`, `shiftone.cpp` | Array rotation & reversal |
| `rotatematrix.cpp`, `transposematrix.cpp` | Matrix operations |
| `duplicateno.cpp`, `uniqueoccur.cpp`, `firstoccur.cpp` | Frequency & duplicates |
| `dutchnationalflag.cpp`, `sortcolors.cpp`, `sortnegatives.cpp`, `sortinarray.cpp` | Sorting/partitioning arrays |
| `pivotindex.cpp`, `maximumones.cpp`, `rearrange+and-.cpp`, `alterswap.cpp` | Rearrangement problems |
| `extremeprint.cpp` | Print extremes |
| `arraypractice1.cpp`, `arraypractice2.cpp`, `practice1.cpp` | Practice problems |

---

### `basic DSA.cpp/`

Beginner-level DSA — good starting point for newcomers.

| File | Topic |
|------|-------|
| `basicDSA.cpp` | Core DSA basics |
| `practiceDSA.cpp`, `practiceDSA1.cpp`, `practice1.cpp` | Practice |
| `insertionsort.cpp`, `selectionsort.cpp`, `sort2.cpp`, `sorting3.cpp` | Sorting algorithms |
| `palindrome.cpp`, `reversestring.cpp`, `replacestring.cpp` | String basics |
| `uppercase.cpp`, `lowercase.cpp` | Character conversion |
| `oddoccurnce.cpp`, `binaryquotient.cpp` | Bit/count problems |
| `sqrt.cpp` | Square root |

---

### `basicmaths.cpp/`

Number theory and mathematical foundations.

| File | Topic |
|------|-------|
| `gcd.cpp` | GCD / Euclidean algorithm |
| `primenumber.cpp`, `prime2.cpp` | Prime checking |
| `seieve.cpp`, `segmented_seieve.cpp` | Sieve of Eratosthenes (normal & segmented) |
| `exponentiation.cpp` | Fast exponentiation |
| `practicebasics.cpp` | Math practice |

---

### `basicpattern.cpp/`

Pattern printing — useful for building loop logic.

| File | Pattern |
|------|---------|
| `halfpyramid.cpp`, `fullpyramids.cpp` | Half & full pyramids |
| `hollowpyramid.cpp`, `hollowrectangular.cpp` | Hollow patterns |
| `invertedhalfpyramid.cpp`, `invertedpyramid.cpp` | Inverted pyramids |
| `numeric.cpp`, `numericpyramid.cpp`, `numerichollow.cpp` | Numeric patterns |
| `squarepattern.cpp`, `soliddiamond.cpp` | Square & diamond |
| `practice1.cpp`, `practice2.cpp`, `practice3.cpp` | Practice |

---

### `binarysearch.cpp/`

Binary search templates and classic BS problems.

| File | Problem / Concept |
|------|-------------------|
| `practicebs.cpp` | BS practice |
| `peakelement.cpp`, `pivotelement.cpp` | Peak / pivot element |
| `sqrt.cpp`, `findquotient.cpp` | Square root & division via BS |
| `oddocc.cpp`, `totalocc.cpp`, `missingelement.cpp` | Occurrence & missing element |
| `2dmatrixsearch.cpp` | Search in 2D matrix |
| `aggressivecow.cpp`, `bookalloc.cpp`, `painterpartition.cpp` | Allocation problems |
| `ekospoj.cpp`, `prataspoj.cpp` | SPOJ problems |
| `kclosestelements.cpp`, `kdiffpairs.cpp` | K-closest & K-diff pairs |
| `nearlysorted.cpp`, `unboundedbs.cpp` | Variants |
| `exponentialsearch.cpp` | Exponential search |

---

### `BST.cpp/`

Binary Search Tree — creation, traversal, conversion, and problems.

| File | Topic |
|------|-------|
| `creationBST.cpp`, `inorderBSTcreate.cpp` | BST creation |
| `inorderBST.cpp`, `searchBST.cpp`, `deletionBST.cpp` | Traversal, search, delete |
| `LCAinBST.cpp`, `twosumBST.cpp` | LCA & two-sum in BST |
| `largestBST.cpp` | Largest BST in a binary tree |
| `BSTtoDLL.cpp`, `bsttodllcreate.cpp`, `dlltobstcreate.cpp` | BST ↔ Doubly Linked List conversion |
| `practicetree.cpp` | BST practice |

---

### `chararray.cpp/`

| File | Topic |
|------|-------|
| `basicsofchararray.cpp` | Char array fundamentals |
| `checkpallindrome.cpp` | Palindrome check |

---

### `CP_Algorithms/`

Competitive programming math and classic theorems.

| File | Topic |
|------|-------|
| `Kadanes_algo.cpp` | Kadane's maximum subarray |
| `Eulers_totient_function.cpp` | Euler's totient φ(n) |
| `euler_theorem.cpp` | Euler's theorem |
| `number_and_sum_of_divisors.cpp` | Divisors count & sum |
| `Handshaking_Theorem.cpp` | Handshaking lemma (graph theory) |
| `rank_of_a_matrix.cpp` | Matrix rank |
| `kth_ancestor_of_a_tree.cpp` | Kth ancestor on tree |
| `hanoi.cpp` | Tower of Hanoi |

---

### `DSA.cpp/`

Mixed DSA implementations.

| File | Topic |
|------|-------|
| `arraysques.cpp` | Array questions |
| `dynamic2D.cpp` | Dynamic 2D arrays |
| `mergearray.cpp` | Merge two arrays |
| `mergesort.cpp`, `quicksort.cpp` | Sorting |

---

### `Graphs/`

The largest folder — **65 graph algorithm implementations**, organized below by category.

#### Traversal (BFS / DFS)

| File | Topic |
|------|-------|
| `bfs_dfs.cpp` | BFS & DFS combined |
| `multi_source_bfs.cpp` | Multi-source BFS |
| `shortest_distance_dfs.cpp` | Shortest path via DFS |
| `rotten_oranges.cpp` | Multi-source BFS (rotten oranges) |
| `all_path_from_source_to_target.cpp` | All paths (BFS) |
| `all_path_from_source_to_target_dfs.cpp` | All paths (DFS) |

#### Shortest Path

| File | Topic |
|------|-------|
| `Dijkstra_algo.cpp`, `Dijkstra_path.cpp` | Dijkstra's algorithm |
| `bellmann_ford_algorithm.cpp` | Bellman-Ford |
| `floyd_warshall_algorithm.cpp` | Floyd-Warshall (all pairs) |
| `a_star.cpp` | A* search algorithm |

#### Minimum Spanning Tree (MST)

| File | Topic |
|------|-------|
| `Prims_algorithm.cpp`, `print_prims.cpp` | Prim's algorithm |
| `Krushkal_algorithm.cpp`, `printing_mst_krushkal_algo.cpp` | Kruskal's algorithm |

#### Union-Find / DSU

| File | Topic |
|------|-------|
| `DSU.cpp`, `Union_find.cpp` | Disjoint Set Union |
| `connected_components_DSU.cpp` | Connected components via DSU |
| `cycle_detection_using_DSU.cpp` | Cycle detection with DSU |
| `dsu_bipartite_graph.cpp`, `bipetrate_graph_union_find.cpp` | Bipartite check via DSU |

#### LCA & Binary Lifting

| File | Topic |
|------|-------|
| `binary_lifting.cpp` | Binary lifting template |
| `LCA_Binary_lifting_kth_ancestor.cpp` | LCA & Kth ancestor |

#### Tree Algorithms

| File | Topic |
|------|-------|
| `center_of_a_tree.cpp` | Tree center |
| `diameter_of_a_tree.cpp`, `diameter_of_a_tree_bfs.cpp`, `diameter_of_tree_1.cpp` | Tree diameter |
| `two_nodes_on_same_path_of_graph.cpp` | Same path check |

#### Topological Sort & DAG

| File | Topic |
|------|-------|
| `topological_sort.cpp`, `kahns_algo.cpp` | Topological sort (Kahn's) |
| `all_ancestors_of_a_node_in_DAG.cpp` | All ancestors in DAG |

#### Cycle Detection

| File | Topic |
|------|-------|
| `cycle_detection.cpp` | General cycle detection |
| `Cycle_detection_color_method.cpp` | Cycle detection (coloring) |

#### Euler Path / Circuit

| File | Topic |
|------|-------|
| `Hierholzers_algorithm.cpp` | Hierholzer's algorithm |
| `Printing_euler_path_undirected.cpp` | Print Euler path (undirected) |
| `directed_eulerian_path.cpp` | Directed Eulerian path |
| `euler_path_directed_indegree.cpp`, `euler_path_undirected_degree.cpp` | Degree conditions |

#### Strongly Connected Components & Articulation

| File | Topic |
|------|-------|
| `tarjans_algo.cpp`, `kosaraju_algorithm.cpp` | SCC algorithms |
| `Articulation_point.cpp` | Articulation points |

#### Bipartite & Graph Coloring

| File | Topic |
|------|-------|
| `Bipetrate_graph_bfs_se.cpp`, `Bipetrate_graph_dfs_se.cpp` | Bipartite check (BFS/DFS) |
| `graph_coloring.cpp`, `chromatic_number.cpp` | Graph coloring |

#### Network Flow

| File | Topic |
|------|-------|
| `Maximum_flow_ford_fulkerson.cpp` | Ford-Fulkerson max flow |

#### Matrix Exponentiation & Math on Graphs

| File | Topic |
|------|-------|
| `matrix_exponentiation.cpp` | Matrix exponentiation |
| `Fibo_series_using_matrix_exponentiation.cpp` | Fibonacci via matrix expo |
| `combinotrics.cpp`, `sum_of_subset.cpp` | Combinatorics & subset sum |
| `kadanes_algo.cpp`, `count_inversion.cpp` | Array algorithms |
| `segmented_sieve.cpp`, `prime_no.cpp` | Prime sieve |

#### Graph Representation & Utilities

| File | Topic |
|------|-------|
| `list_to_matrix.cpp`, `matrix_to_list.cpp` | Adjacency conversions |
| `reversed_graph.cpp` | Reverse a graph |
| `Base_N.cpp` | Base-N conversion |
| `Substring_of_a_string.cpp`, `Sum_of_substring.cpp` | String on graph context |
| `ray_casting_algorithm.cpp`, `winding_number.cpp` | Computational geometry |
| `merge_sortt.cpp` | Merge sort |

---

### `Greedy/`

| File | Topic |
|------|-------|
| `job_sequencing.cpp` | Job sequencing with deadlines |

---

### `heaps.cpp/`

Heap data structure — min/max heap, heap sort, and heap problems.

| File | Topic |
|------|-------|
| `MinHeap.cpp`, `MaxHeap.cpp` | Min & max heap implementation |
| `createheap.cpp`, `buildheap.cpp`, `deleteHeap.cpp` | Heap operations |
| `heapsort.cpp` | Heap sort |
| `STLheaps.cpp` | STL `priority_queue` usage |
| `IsCBT.cpp`, `ValidHeapfromCBT.cpp`, `checkmaxheap.cpp` | Complete binary tree & heap validation |
| `BSTtoMaxHeap.cpp` | Convert BST to max heap |
| `kgreatest.cpp`, `findingsmallest.cpp` | K greatest / smallest elements |
| `practice.cpp` | Heap practice |

---

### `linkedlist.cpp/`

Singly, doubly linked lists and classic LL problems.

| File | Topic |
|------|-------|
| `basicsofLL.cpp`, `doublyLL.cpp` | Singly & doubly LL basics |
| `reversell.cpp`, `kgrpreversal.cpp` | Reverse LL (full & K-group) |
| `middleLL.cpp`, `add2ll.cpp`, `addone.cpp` | Middle element, add numbers |
| `deletionLL.cpp`, `linkedlistdelete.cpp` | Deletion |
| `pallindromell.cpp` | Palindrome linked list |
| `startofloop.cpp`, `tortoisealgo.cpp` | Cycle detection (Floyd's) |
| `Binary_lifting_LCA.cpp` | LCA via binary lifting (on LL) |
| `MCM_partition_dp.cpp` | Matrix chain multiplication (DP) |
| `practiceLL.cpp`, `practicelinkedl.cpp` | Practice |

---

### `OOP's.cpp/`

Object-Oriented Programming concepts in C++.

| File | Topic |
|------|-------|
| `basicsoops.cpp`, `basicsoops2.cpp`, `practiceoops.cpp` | OOP basics |
| `constructor.cpp` | Constructors |
| `thiskeyword.cpp` | `this` keyword |
| `fourpillars.cpp`, `practicefourpillars.cpp` | Four pillars of OOP |
| `inheritance.cpp` | Inheritance |
| `polymorphism.cpp` | Polymorphism |
| `diamondprblm.cpp` | Diamond problem |

---

### `queues.cpp/`

Queue, deque, circular queue, and queue-based problems.

| File | Topic |
|------|-------|
| `arrayimpln.cpp`, `practicequeue.cpp` | Queue basics |
| `DEqueue.cpp`, `implementDEqueue.cpp`, `implementcqueue.cpp` | Deque & circular queue |
| `queuefromstacks.cpp` | Queue using stacks |
| `reversequeue.cpp`, `reversekelements.cpp` | Reverse queue / K elements |
| `interleavequeue.cpp` | Interleave queue |
| `slidingwindow.cpp` | Sliding window maximum |
| `nonrepeatingchar.cpp` | First non-repeating character |

---

### `recursion.cpp/`

Recursion, backtracking, and recursive sorting/searching.

| File | Topic |
|------|-------|
| `factorial.cpp`, `fibonacci.cpp`, `apowerb.cpp` | Classic recursion |
| `linearsearch.cpp`, `binarysearch.cpp` | Recursive search |
| `maxelement.cpp`, `minelement.cpp`, `sortedarray.cpp` | Array via recursion |
| `reversestring.cpp`, `pallindromestr.cpp`, `saydigits.cpp`, `digitsrec.cpp` | String recursion |
| `mergesort.cpp`, `quicksort.cpp`, `bubblesort.cpp`, `inplacesort.cpp`, `gapmethod.cpp` | Recursive sorting |
| `subsequences.cpp`, `setsubsets.cpp`, `permutationofstr.cpp` | Subsets & permutations |
| `generateparenthesis.cpp` | Generate valid parentheses |
| `coinchangeprblm.cpp`, `houserobber.cpp`, `maximumsum.cpp` | DP-style recursion |
| `ratinmazeprblm.cpp`, `phnkeypadprblm.cpp`, `cutinsegment.cpp` | Backtracking |
| `countinversion.cpp`, `mergearray.cpp` | Merge & inversion count |
| `headandtail.cpp`, `printsum.cpp`, `stringelement.cpp` | Basics |
| `practicerecursion.cpp`, `pracrec2.cpp`, `practicesorting.cpp` | Practice |

---

### `segment_tree/`

Segment trees, Fenwick trees, sqrt decomposition, and related range query techniques.

> See also: [`segment_tree/important.txt`](segment_tree/important.txt) — a detailed **Segment Tree vs Fenwick Tree decision guide** (Hindi + English).

| File | Topic |
|------|-------|
| `min_max_segment_tree.cpp` | Min/max segment tree |
| `lazy_propogation.cpp` | Lazy propagation (range update) |
| `dynamic_segment_tree.cpp` | Dynamic segment tree |
| `2D_segment_tree.cpp`, `2D_Segment_tree_important.cpp` | 2D segment tree |
| `variations_in_seg_tree.cpp`, `gcd_problem_segment_tree.cpp` | Seg tree variations & GCD |
| `fenwick_tree_variations_types.cpp`, `fenwick_tree_xor.cpp`, `xor_fenwick_tree.cpp` | Fenwick tree variants |
| `2d_fenwick_tree.cpp` | 2D Fenwick tree |
| `count_inversion_fenwick_tree.cpp` | Inversion count via Fenwick |
| `Count_of_number_in_array_less_than_x_using_fenwick_tree.cpp` | Count smaller elements |
| `coordinate_compression.cpp` | Coordinate compression |
| `sqrt_decomposition.cpp` | Square root decomposition |
| `euler_tour_+_segment_tree.cpp` | Euler tour + segment tree on trees |
| `subtree_query_problems.cpp` | Subtree queries |
| `k_smallest_number_in_range.cpp` | K-th smallest in range |
| `all_trees.cpp` | Tree-related segment tree problems |
| `Leetcode_315_fenwick_tree.cpp` | LeetCode 315 (count of smaller numbers) |
| `Leetcode_3636_Mos_algo.cpp` | LeetCode 3636 (Mo's algorithm) |

---

### `stacks.cpp/`

Stack implementations and monotonic stack problems.

| File | Topic |
|------|-------|
| `stackbasics.cpp`, `stackarray.cpp`, `practicestacks.cpp`, `practicestacks2.cpp` | Stack basics |
| `validbrackets.cpp`, `checkredbracket.cpp`, `bracketreversal.cpp` | Bracket problems |
| `minstack.cpp` | Min stack |
| `nextsmaller.cpp`, `prevsmallelement.cpp` | Next/previous smaller element |
| `histogramarea.cpp` | Largest rectangle in histogram |
| `insertatbottom.cpp`, `reversestack.cpp`, `removedup.cpp` | Stack operations |
| `implement2stacks.cpp`, `twostackarray.cpp`, `nstackarray.cpp` | N stacks in one array |
| `celebrityprblm.cpp`, `onlinestockprblm.cpp`, `asteroidcollision.cpp` | Classic stack problems |
| `leetcode1003.cpp` | LeetCode 1003 (valid parentheses after delete) |

---

### `strings.cpp/`

| File | Topic |
|------|-------|
| `basicstring.cpp`, `inbuiltstr.cpp` | String basics & STL |
| `pallindrome.cpp` | Palindrome |
| `removeduplicate.cpp`, `removekdup.cpp`, `removeoccrnce.cpp` | Remove duplicates/occurrences |
| `practicestring.cpp`, `practicestrings.cpp` | Practice |

---

### `trees.cpp/`

Binary tree creation, traversals, views, and advanced tree techniques.

| File | Topic |
|------|-------|
| `basictrees.cpp`, `make_binary_tree.cpp`, `practiceBT.cpp` | Tree basics & creation |
| `inpretreecreate.cpp`, `inposttreecreate.cpp` | Build tree from traversals |
| `heightBT.cpp`, `diameterBT.cpp`, `balancedBT.cpp` | Height, diameter, balance check |
| `LCA.cpp` | Lowest Common Ancestor |
| `leftview.cpp`, `rightview.cpp`, `topview.cpp` | Tree views |
| `boundarytraversal.cpp`, `zigzagtraversal.cpp`, `diagonaltraversal.cpp` | Traversals |
| `pathsum.cpp`, `tree_leaf.cpp` | Path sum & leaf nodes |
| `making_bst.cpp` | BST construction |
| `morris_binary_tree.cpp`, `morris_bst.cpp` | Morris traversal (O(1) space) |
| `revised.cpp` | Revised tree problems |

---

### `vector.cpp/`

| File | Topic |
|------|-------|
| `basicvector.cpp` | STL vector basics |
| `pairsum.cpp`, `uniqueelement.cpp` | Pair sum & unique elements |
| `jaggedarray.cpp` | Jagged array via vector |
| `practice1.cpp` | Practice |

---

## Topic Coverage Summary

| Category | Topics |
|----------|--------|
| **Fundamentals** | Arrays, Strings, Vectors, Char arrays, Patterns |
| **Linear DS** | Linked List, Stack, Queue, Deque, Heap |
| **Trees** | Binary Tree, BST, Morris traversal, LCA, Euler tour |
| **Graphs** | BFS, DFS, Dijkstra, Bellman-Ford, Floyd-Warshall, MST, DSU, SCC, Topo sort, Flow, A* |
| **Searching** | Linear, Binary, Exponential search |
| **Sorting** | Bubble, Insertion, Selection, Merge, Quick, Heap sort |
| **Recursion & BT** | Subsets, Permutations, N-Queens style, Rat in maze, Parentheses |
| **DP** | LIS, Coin change, House robber, MCM, Kadane's |
| **Range Queries** | Segment tree, Lazy propagation, Fenwick tree, Mo's algo, Sqrt decomposition |
| **String Algo** | KMP, Z-algo, Rabin-Karp, Rolling hash |
| **Math / NT** | GCD, Sieve, Totient, Matrix expo, Newton-Raphson, Convex hull |
| **Greedy** | Job sequencing |
| **OOP** | Encapsulation, Inheritance, Polymorphism, Constructors |

---

## VS Code Setup

This repo includes `.vscode/` configuration for one-click build:

- **`tasks.json`** — builds the active `.cpp` file with `clang`
- **`launch.json`** — debug configuration

Press `Cmd+Shift+B` (Mac) or `Ctrl+Shift+B` (Windows/Linux) to build the current file.

---

## Contributing

Contributions are welcome! Feel free to:

- Add optimized solutions
- Fix bugs or improve existing code
- Add new problems or topics

Open a Pull Request on [GitHub](https://github.com/subhm2004/DSA).

---

## License

This repository is open-source under the **MIT License**.

---

**Happy Coding!**
