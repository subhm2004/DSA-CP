# DSA Patterns — Progress Tracker

**Author:** [Shubham Malik](https://github.com/subhm2004) · [DSA-CP](https://github.com/subhm2004/DSA-CP)  
**Generated:** 2026-08-07 · `python3 scripts/generate_patterns.py`

**15 categories · 94 patterns · 438 problems**

### Progress — 122 / 438 solved (27%)

`████████░░░░░░░░░░░░░░░░░░░░░░`

✅ = repo me solution hai · ⬜ = pending · ⭐ = 30-day core set

---

## Categories

| # | Category | Patterns | Problems | Done | Progress |
|--:|----------|---------:|---------:|-----:|----------|
| I | [Two Pointer Patterns](#i-two-pointer-patterns) | 7 | 34 | 10 | `███░░░░░░░` 29% |
| II | [Sliding Window Patterns](#ii-sliding-window-patterns) | 4 | 31 | 7 | `██░░░░░░░░` 22% |
| III | [Tree Traversal Patterns (DFS & BFS)](#iii-tree-traversal-patterns-dfs--bfs) | 6 | 33 | 10 | `███░░░░░░░` 30% |
| IV | [Graph Traversal Patterns (DFS & BFS)](#iv-graph-traversal-patterns-dfs--bfs) | 12 | 68 | 19 | `███░░░░░░░` 27% |
| V | [Dynamic Programming (DP) Patterns](#v-dynamic-programming-dp-patterns) | 12 | 47 | 13 | `███░░░░░░░` 27% |
| VI | [Heap (Priority Queue) Patterns](#vi-heap-priority-queue-patterns) | 4 | 22 | 5 | `██░░░░░░░░` 22% |
| VII | [Backtracking Patterns](#vii-backtracking-patterns) | 7 | 19 | 10 | `█████░░░░░` 52% |
| VIII | [Greedy Patterns](#viii-greedy-patterns) | 6 | 18 | 5 | `███░░░░░░░` 27% |
| IX | [Binary Search Patterns](#ix-binary-search-patterns) | 5 | 27 | 9 | `███░░░░░░░` 33% |
| X | [Stack Patterns](#x-stack-patterns) | 6 | 26 | 9 | `███░░░░░░░` 34% |
| XI | [Bit Manipulation Patterns](#xi-bit-manipulation-patterns) | 4 | 12 | 5 | `████░░░░░░` 41% |
| XII | [Linked List Manipulation Patterns](#xii-linked-list-manipulation-patterns) | 5 | 17 | 5 | `███░░░░░░░` 29% |
| XIII | [Array/Matrix Manipulation Patterns](#xiii-arraymatrix-manipulation-patterns) | 7 | 24 | 5 | `██░░░░░░░░` 20% |
| XIV | [String Manipulation Patterns](#xiv-string-manipulation-patterns) | 7 | 20 | 3 | `██░░░░░░░░` 15% |
| XV | [Design Patterns](#xv-design-patterns) | 2 | 40 | 7 | `██░░░░░░░░` 17% |
| | **Total** | **94** | **438** | **122** | `███░░░░░░░` **27%** |

---

## I. Two Pointer Patterns

34 problems · **10 done** · `███░░░░░░░` 29%

### Pattern 1 — Converging

`███░░░░░░░` **3/9**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 11 | [Container With Most Water](https://leetcode.com/problems/container-with-most-water/) | ⭐ | [`container_with_most_water.cpp`](./CP/two_pointers/container_with_most_water.cpp) · [`container_with_most_water.cpp`](./DSA/two_pointers/container_with_most_water.cpp) |
| ✅ | 15 | [3Sum](https://leetcode.com/problems/3sum/) | ⭐ | [`three_sum.cpp`](./CP/two_pointers/three_sum.cpp) · [`three_sum.cpp`](./DSA/two_pointers/three_sum.cpp) |
| ⬜ | 16 | [3Sum Closest](https://leetcode.com/problems/3sum-closest/) |  | — |
| ⬜ | 18 | [4Sum](https://leetcode.com/problems/4sum/) |  | — |
| ✅ | 167 | [Two Sum II - Input Array Is Sorted](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/) | ⭐ | [`two_sum_sorted.cpp`](./CP/two_pointers/two_sum_sorted.cpp) · [`two_sum_sorted.cpp`](./DSA/two_pointers/two_sum_sorted.cpp) |
| ⬜ | 349 | [Intersection of Two Arrays](https://leetcode.com/problems/intersection-of-two-arrays/) |  | — |
| ⬜ | 881 | [Boats to Save People](https://leetcode.com/problems/boats-to-save-people/) |  | — |
| ⬜ | 977 | [Squares of a Sorted Array](https://leetcode.com/problems/squares-of-a-sorted-array/) |  | — |
| ⬜ | 259 | [3Sum Smaller](https://leetcode.com/problems/3sum-smaller/) |  | — |

### Pattern 2 — Fast & Slow

`█████░░░░░` **2/4**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 141 | [Linked List Cycle](https://leetcode.com/problems/linked-list-cycle/) | ⭐ | [`tortoise_algo.cpp`](./DSA/linked_list/tortoise_algo.cpp) |
| ⬜ | 202 | [Happy Number](https://leetcode.com/problems/happy-number/) |  | — |
| ✅ | 287 | [Find the Duplicate Number](https://leetcode.com/problems/find-the-duplicate-number/) | ⭐ | [`duplicate_number.cpp`](./DSA/arrays/duplicate_number.cpp) |
| ⬜ | 392 | [Is Subsequence](https://leetcode.com/problems/is-subsequence/) |  | — |

### Pattern 3 — Fixed Separation

`███░░░░░░░` **1/3**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ⬜ | 19 | [Remove Nth Node From End of List](https://leetcode.com/problems/remove-nth-node-from-end-of-list/) | ⭐ | — |
| ✅ | 876 | [Middle of the Linked List](https://leetcode.com/problems/middle-of-the-linked-list/) |  | [`middle_of_linked_list.cpp`](./DSA/linked_list/middle_of_linked_list.cpp) |
| ⬜ | 2095 | [Delete the Middle Node of a Linked List](https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/) |  | — |

### Pattern 4 — In-place Array Modification

`███░░░░░░░` **3/9**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 26 | [Remove Duplicates from Sorted Array](https://leetcode.com/problems/remove-duplicates-from-sorted-array/) | ⭐ | [`remove_duplicates_sorted_array.cpp`](./DSA/two_pointers/remove_duplicates_sorted_array.cpp) |
| ⬜ | 27 | [Remove Element](https://leetcode.com/problems/remove-element/) |  | — |
| ✅ | 75 | [Sort Colors](https://leetcode.com/problems/sort-colors/) | ⭐ | [`dutch_national_flag.cpp`](./DSA/arrays/dutch_national_flag.cpp) · [`sort_colors.cpp`](./DSA/arrays/sort_colors.cpp) |
| ⬜ | 80 | [Remove Duplicates from Sorted Array II](https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/) |  | — |
| ⬜ | 283 | [Move Zeroes](https://leetcode.com/problems/move-zeroes/) | ⭐ | — |
| ⬜ | 443 | [String Compression](https://leetcode.com/problems/string-compression/) |  | — |
| ✅ | 905 | [Sort Array By Parity](https://leetcode.com/problems/sort-array-by-parity/) |  | [`rearrange_positive_negative.cpp`](./DSA/arrays/rearrange_positive_negative.cpp) |
| ⬜ | 2337 | [Move Pieces to Obtain a String](https://leetcode.com/problems/move-pieces-to-obtain-a-string/) |  | — |
| ⬜ | 2938 | [Separate Black and White Balls](https://leetcode.com/problems/separate-black-and-white-balls/) |  | — |

### Pattern 5 — String Comparison with  special characters

`░░░░░░░░░░` **0/3**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ⬜ | 844 | [Backspace String Compare](https://leetcode.com/problems/backspace-string-compare/) |  | — |
| ⬜ | 1598 | [Crawler Log Folder](https://leetcode.com/problems/crawler-log-folder/) |  | — |
| ⬜ | 2390 | [Removing Stars From a String](https://leetcode.com/problems/removing-stars-from-a-string/) |  | — |

### Pattern 6 — Expanding From Center

`░░░░░░░░░░` **0/2**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ⬜ | 5 | [Longest Palindromic Substring](https://leetcode.com/problems/longest-palindromic-substring/) | ⭐ | — |
| ⬜ | 647 | [Palindromic Substrings](https://leetcode.com/problems/palindromic-substrings/) |  | — |

### Pattern 7 — String Reversal

`██░░░░░░░░` **1/4**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ⬜ | 151 | [Reverse Words in a String](https://leetcode.com/problems/reverse-words-in-a-string/) | ⭐ | — |
| ✅ | 344 | [Reverse String](https://leetcode.com/problems/reverse-string/) |  | [`reverse.cpp`](./DSA/arrays/reverse.cpp) |
| ⬜ | 345 | [Reverse Vowels of a String](https://leetcode.com/problems/reverse-vowels-of-a-string/) |  | — |
| ⬜ | 541 | [Reverse String II](https://leetcode.com/problems/reverse-string-ii/) |  | — |

---

## II. Sliding Window Patterns

31 problems · **7 done** · `██░░░░░░░░` 22%

### Pattern 8 — Fixed Size

`██░░░░░░░░` **1/5**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ⬜ | 346 | [Moving Average from Data Stream](https://leetcode.com/problems/moving-average-from-data-stream/) |  | — |
| ✅ | 643 | [Maximum Average Subarray I](https://leetcode.com/problems/maximum-average-subarray-i/) |  | [`max_sum_subarray_size_k.cpp`](./DSA/sliding_window/max_sum_subarray_size_k.cpp) |
| ⬜ | 2985 | [Calculate Compressed Mean](https://leetcode.com/problems/calculate-compressed-mean/) |  | — |
| ⬜ | 3254 | [Find the Power of K-Size Subarrays I](https://leetcode.com/problems/find-the-power-of-ksize-subarrays-i/) |  | — |
| ⬜ | 3318 | [Find X-Sum of All K-Long Subarrays I](https://leetcode.com/problems/find-xsum-of-all-klong-subarrays-i/) |  | — |

### Pattern 9 — Variable Size

`██░░░░░░░░` **4/20**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 3 | [Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/) | ⭐ | [`longest_substring_without_repeat.cpp`](./DSA/sliding_window/longest_substring_without_repeat.cpp) |
| ✅ | 76 | [Minimum Window Substring](https://leetcode.com/problems/minimum-window-substring/) | ⭐ | [`minimum_window_substring.cpp`](./DSA/sliding_window/minimum_window_substring.cpp) |
| ⬜ | 209 | [Minimum Size Subarray Sum](https://leetcode.com/problems/minimum-size-subarray-sum/) | ⭐ | — |
| ⬜ | 219 | [Contains Duplicate II](https://leetcode.com/problems/contains-duplicate-ii/) |  | — |
| ✅ | 424 | [Longest Repeating Character Replacement](https://leetcode.com/problems/longest-repeating-character-replacement/) | ⭐ | [`longest_repeating_char_replace.cpp`](./DSA/sliding_window/longest_repeating_char_replace.cpp) |
| ⬜ | 713 | [Subarray Product Less Than K](https://leetcode.com/problems/subarray-product-less-than-k/) |  | — |
| ✅ | 904 | [Fruit Into Baskets](https://leetcode.com/problems/fruit-into-baskets/) |  | [`fruit_into_baskets.cpp`](./DSA/sliding_window/fruit_into_baskets.cpp) |
| ⬜ | 1004 | [Max Consecutive Ones III](https://leetcode.com/problems/max-consecutive-ones-iii/) |  | — |
| ⬜ | 1438 | [Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit](https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/) |  | — |
| ⬜ | 1493 | [Longest Subarray of 1's After Deleting One Element](https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element/) |  | — |
| ⬜ | 1658 | [Minimum Operations to Reduce X to Zero](https://leetcode.com/problems/minimum-operations-to-reduce-x-to-zero/) |  | — |
| ⬜ | 1838 | [Frequency of the Most Frequent Element](https://leetcode.com/problems/frequency-of-the-most-frequent-element/) |  | — |
| ⬜ | 2461 | [Maximum Sum of Distinct Subarrays With Length K](https://leetcode.com/problems/maximum-sum-of-distinct-subarrays-with-length-k/) |  | — |
| ⬜ | 2516 | [Take K of Each Character From Left and Right](https://leetcode.com/problems/take-k-of-each-character-from-left-and-right/) |  | — |
| ⬜ | 2762 | [Continuous Subarrays](https://leetcode.com/problems/continuous-subarrays/) |  | — |
| ⬜ | 2779 | [Maximum Beauty of an Array After Applying Operation](https://leetcode.com/problems/maximum-beauty-of-an-array-after-applying-operation/) |  | — |
| ⬜ | 2981 | [Find Longest Special Substring That Occurs Thrice I](https://leetcode.com/problems/find-longest-special-substring-that-occurs-thrice-i/) |  | — |
| ⬜ | 3026 | [Maximum Good Subarray Sum](https://leetcode.com/problems/maximum-good-subarray-sum/) |  | — |
| ⬜ | 3346 | [Maximum Frequency of an Element After Performing Operations I](https://leetcode.com/problems/maximum-frequency-of-an-element-after-performing-operations-i/) |  | — |
| ⬜ | 3347 | [Maximum Frequency of an Element After Performing Operations II](https://leetcode.com/problems/maximum-frequency-of-an-element-after-performing-operations-ii/) |  | — |

### Pattern 10 — Monotonic Queue for Max/Min

`███░░░░░░░` **1/3**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 239 | [Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/) |  | [`monotonic_queue.cpp`](./CP/monotonic_queue/monotonic_queue.cpp) · [`deque_implementation.cpp`](./DSA/queues/deque_implementation.cpp) · [`sliding_window_maximum.cpp`](./DSA/queues/sliding_window_maximum.cpp) |
| ⬜ | 862 | [Shortest Subarray with Sum at Least K](https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/) |  | — |
| ⬜ | 1696 | [Jump Game VI](https://leetcode.com/problems/jump-game-vi/) |  | — |

### Pattern 11 — Character Frequency Matching

`███░░░░░░░` **1/3**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 1 | [Two Sum](https://leetcode.com/problems/two-sum/) |  | [`two_sum.cpp`](./DSA/arrays/two_sum.cpp) · [`two_sum_hashmap.cpp`](./DSA/hash_map/two_sum_hashmap.cpp) |
| ⬜ | 438 | [Find All Anagrams in a String](https://leetcode.com/problems/find-all-anagrams-in-a-string/) | ⭐ | — |
| ⬜ | 567 | [Permutation in String](https://leetcode.com/problems/permutation-in-string/) |  | — |

---

## III. Tree Traversal Patterns (DFS & BFS)

33 problems · **10 done** · `███░░░░░░░` 30%

### Pattern 12 — Level Order Traversal

`██████░░░░` **3/5**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 102 | [Binary Tree Level Order Traversal](https://leetcode.com/problems/binary-tree-level-order-traversal/) | ⭐ | [`bfs_traversal.cpp`](./DSA/graphs/bfs_traversal.cpp) |
| ✅ | 103 | [Binary Tree Zigzag Level Order Traversal](https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/) |  | [`zigzag_level_order.cpp`](./DSA/trees/zigzag_level_order.cpp) |
| ✅ | 199 | [Binary Tree Right Side View](https://leetcode.com/problems/binary-tree-right-side-view/) | ⭐ | [`left_view_binary_tree.cpp`](./DSA/trees/left_view_binary_tree.cpp) · [`right_view_binary_tree.cpp`](./DSA/trees/right_view_binary_tree.cpp) |
| ⬜ | 515 | [Find Largest Value in Each Tree Row](https://leetcode.com/problems/find-largest-value-in-each-tree-row/) |  | — |
| ⬜ | 1161 | [Maximum Level Sum of a Binary Tree](https://leetcode.com/problems/maximum-level-sum-of-a-binary-tree/) |  | — |

### Pattern 13 — Recursive Preorder Traversal

`█░░░░░░░░░` **1/7**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ⬜ | 100 | [Same Tree](https://leetcode.com/problems/same-tree/) |  | — |
| ⬜ | 101 | [Symmetric Tree](https://leetcode.com/problems/symmetric-tree/) |  | — |
| ✅ | 105 | [Construct Binary Tree from Preorder and Inorder Traversal](https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/) | ⭐ | [`build_tree_inorder_preorder.cpp`](./DSA/trees/build_tree_inorder_preorder.cpp) |
| ⬜ | 114 | [Flatten Binary Tree to Linked List](https://leetcode.com/problems/flatten-binary-tree-to-linked-list/) |  | — |
| ⬜ | 226 | [Invert Binary Tree](https://leetcode.com/problems/invert-binary-tree/) | ⭐ | — |
| ⬜ | 257 | [Binary Tree Paths](https://leetcode.com/problems/binary-tree-paths/) |  | — |
| ⬜ | 988 | [Smallest String Starting From Leaf](https://leetcode.com/problems/smallest-string-starting-from-leaf/) |  | — |

### Pattern 14 — Recursive Inorder Traversal

`██░░░░░░░░` **1/6**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 94 | [Binary Tree Inorder Traversal](https://leetcode.com/problems/binary-tree-inorder-traversal/) |  | [`morris_traversal_binary_tree.cpp`](./DSA/trees/morris_traversal_binary_tree.cpp) · [`morris_traversal_bst.cpp`](./DSA/trees/morris_traversal_bst.cpp) |
| ⬜ | 98 | [Validate Binary Search Tree](https://leetcode.com/problems/validate-binary-search-tree/) | ⭐ | — |
| ⬜ | 173 | [Binary Search Tree Iterator](https://leetcode.com/problems/binary-search-tree-iterator/) |  | — |
| ⬜ | 230 | [Kth Smallest Element in a BST](https://leetcode.com/problems/kth-smallest-element-in-a-bst/) | ⭐ | — |
| ⬜ | 501 | [Find Mode in Binary Search Tree](https://leetcode.com/problems/find-mode-in-binary-search-tree/) |  | — |
| ⬜ | 530 | [Minimum Absolute Difference in BST](https://leetcode.com/problems/minimum-absolute-difference-in-bst/) |  | — |

### Pattern 15 — Recursive Postorder Traversal

`███░░░░░░░` **3/10**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 104 | [Maximum Depth of Binary Tree](https://leetcode.com/problems/maximum-depth-of-binary-tree/) | ⭐ | [`dfs_traversal.cpp`](./DSA/graphs/dfs_traversal.cpp) · [`binary_tree_height.cpp`](./DSA/trees/binary_tree_height.cpp) |
| ✅ | 110 | [Balanced Binary Tree](https://leetcode.com/problems/balanced-binary-tree/) |  | [`balanced_binary_tree.cpp`](./DSA/trees/balanced_binary_tree.cpp) |
| ⬜ | 124 | [Binary Tree Maximum Path Sum](https://leetcode.com/problems/binary-tree-maximum-path-sum/) | ⭐ | — |
| ⬜ | 145 | [Binary Tree Postorder Traversal](https://leetcode.com/problems/binary-tree-postorder-traversal/) |  | — |
| ⬜ | 337 | [House Robber III](https://leetcode.com/problems/house-robber-iii/) |  | — |
| ⬜ | 366 | [Find Leaves of Binary Tree](https://leetcode.com/problems/find-leaves-of-binary-tree/) |  | — |
| ✅ | 543 | [Diameter of Binary Tree](https://leetcode.com/problems/diameter-of-binary-tree/) | ⭐ | [`binary_tree_diameter.cpp`](./DSA/trees/binary_tree_diameter.cpp) |
| ⬜ | 863 | [All Nodes Distance K in Binary Tree](https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/) |  | — |
| ⬜ | 1110 | [Delete Nodes And Return Forest](https://leetcode.com/problems/delete-nodes-and-return-forest/) |  | — |
| ⬜ | 2458 | [Height of Binary Tree After Subtree Removal Queries](https://leetcode.com/problems/height-of-binary-tree-after-subtree-removal-queries/) |  | — |

### Pattern 16 — Lowest Common Ancestor

`█████░░░░░` **1/2**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 235 | [Lowest Common Ancestor of a Binary Search Tree](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/) | ⭐ | [`lca_in_bst.cpp`](./DSA/bst/lca_in_bst.cpp) |
| ⬜ | 236 | [Lowest Common Ancestor of a Binary Tree](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/) | ⭐ | — |

### Pattern 17 — Serialization and Deserialization

`███░░░░░░░` **1/3**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 297 | [Serialize and Deserialize Binary Tree](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/) | ⭐ | [`serialize_deserialize_binary_tree.cpp`](./DSA/trees/serialize_deserialize_binary_tree.cpp) |
| ⬜ | 572 | [Subtree of Another Tree](https://leetcode.com/problems/subtree-of-another-tree/) |  | — |
| ⬜ | 652 | [Find Duplicate Subtrees](https://leetcode.com/problems/find-duplicate-subtrees/) |  | — |

---

## IV. Graph Traversal Patterns (DFS & BFS)

68 problems · **19 done** · `███░░░░░░░` 27%

### Pattern 18 — DFS - Connected Components / Island Counting

`██████░░░░` **7/11**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 130 | [Surrounded Regions](https://leetcode.com/problems/surrounded-regions/) |  | [`surrounded_regions.cpp`](./DSA/graphs/surrounded_regions.cpp) |
| ✅ | 200 | [Number of Islands](https://leetcode.com/problems/number-of-islands/) | ⭐ | [`number_of_islands.cpp`](./DSA/graphs/number_of_islands.cpp) |
| ✅ | 417 | [Pacific Atlantic Water Flow](https://leetcode.com/problems/pacific-atlantic-water-flow/) |  | [`pacific_atlantic_water_flow.cpp`](./DSA/graphs/pacific_atlantic_water_flow.cpp) |
| ✅ | 547 | [Number of Provinces](https://leetcode.com/problems/number-of-provinces/) | ⭐ | [`number_of_provinces.cpp`](./DSA/graphs/number_of_provinces.cpp) |
| ✅ | 695 | [Max Area of Island](https://leetcode.com/problems/max-area-of-island/) | ⭐ | [`max_area_of_island.cpp`](./DSA/graphs/max_area_of_island.cpp) |
| ✅ | 733 | [Flood Fill](https://leetcode.com/problems/flood-fill/) | ⭐ | [`flood_fill.cpp`](./DSA/graphs/flood_fill.cpp) |
| ⬜ | 841 | [Keys and Rooms](https://leetcode.com/problems/keys-and-rooms/) |  | — |
| ⬜ | 1020 | [Number of Enclaves](https://leetcode.com/problems/number-of-enclaves/) |  | — |
| ✅ | 1254 | [Number of Closed Islands](https://leetcode.com/problems/number-of-closed-islands/) |  | [`number_of_closed_islands.cpp`](./DSA/graphs/number_of_closed_islands.cpp) |
| ⬜ | 1905 | [Count Sub Islands](https://leetcode.com/problems/count-sub-islands/) |  | — |
| ⬜ | 2101 | [Detonate the Maximum Bombs](https://leetcode.com/problems/detonate-the-maximum-bombs/) |  | — |

### Pattern 19 — BFS - Connected Components / Island Counting

`███░░░░░░░` **1/3**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ⬜ | 542 | [01 Matrix](https://leetcode.com/problems/01-matrix/) |  | — |
| ✅ | 994 | [Rotting Oranges](https://leetcode.com/problems/rotting-oranges/) |  | [`rotten_oranges.cpp`](./DSA/graphs/rotten_oranges.cpp) |
| ⬜ | 1091 | [Shortest Path in Binary Matrix](https://leetcode.com/problems/shortest-path-in-binary-matrix/) |  | — |

### Pattern 20 — DFS - Cycle Detection

`█████░░░░░` **2/4**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 207 | [Course Schedule](https://leetcode.com/problems/course-schedule/) | ⭐ | [`cycle_detection_directed.cpp`](./DSA/graphs/cycle_detection_directed.cpp) |
| ✅ | 210 | [Course Schedule II](https://leetcode.com/problems/course-schedule-ii/) | ⭐ | [`topological_sort_kahn.cpp`](./DSA/graphs/topological_sort_kahn.cpp) |
| ⬜ | 802 | [Find Eventual Safe States](https://leetcode.com/problems/find-eventual-safe-states/) |  | — |
| ⬜ | 1059 | [All Paths from Source Lead to Destination](https://leetcode.com/problems/all-paths-from-source-lead-to-destination/) |  | — |

### Pattern 21 — BFS - Topological Sort(Kahn's Algorithm)

`█░░░░░░░░░` **1/9**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 210 | [Course Schedule II](https://leetcode.com/problems/course-schedule-ii/) | ⭐ | [`topological_sort_kahn.cpp`](./DSA/graphs/topological_sort_kahn.cpp) |
| ⬜ | 269 | [Alien Dictionary](https://leetcode.com/problems/alien-dictionary/) | ⭐ | — |
| ⬜ | 310 | [Minimum Height Trees](https://leetcode.com/problems/minimum-height-trees/) |  | — |
| ⬜ | 444 | [Sequence Reconstruction](https://leetcode.com/problems/sequence-reconstruction/) |  | — |
| ⬜ | 1136 | [Parallel Courses](https://leetcode.com/problems/parallel-courses/) |  | — |
| ⬜ | 1857 | [Largest Color Value in a Directed Graph](https://leetcode.com/problems/largest-color-value-in-a-directed-graph/) |  | — |
| ⬜ | 2050 | [Parallel Courses III](https://leetcode.com/problems/parallel-courses-iii/) |  | — |
| ⬜ | 2115 | [Find All Possible Recipes from Given Supplies](https://leetcode.com/problems/find-all-possible-recipes-from-given-supplies/) |  | — |
| ⬜ | 2392 | [Build a Matrix With Conditions](https://leetcode.com/problems/build-a-matrix-with-conditions/) |  | — |

### Pattern 22 — Deep Copy / Cloning

`██░░░░░░░░` **1/4**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 133 | [Clone Graph](https://leetcode.com/problems/clone-graph/) | ⭐ | [`clone_graph.cpp`](./DSA/graphs/clone_graph.cpp) |
| ⬜ | 1334 | [Find the City With the Smallest Number of Neighbors at a Threshold Distance](https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/) |  | — |
| ⬜ | 138 | [Copy List with Random Pointer](https://leetcode.com/problems/copy-list-with-random-pointer/) |  | — |
| ⬜ | 1490 | [Clone N-ary Tree](https://leetcode.com/problems/clone-nary-tree/) |  | — |

### Pattern 23 — Shortest Path

`░░░░░░░░░░` **0/10**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ⬜ | 743 | [Network Delay Time](https://leetcode.com/problems/network-delay-time/) |  | — |
| ⬜ | 778 | [Swim in Rising Water](https://leetcode.com/problems/swim-in-rising-water/) |  | — |
| ⬜ | 1514 | [Path with Maximum Probability](https://leetcode.com/problems/path-with-maximum-probability/) |  | — |
| ⬜ | 1631 | [Path With Minimum Effort](https://leetcode.com/problems/path-with-minimum-effort/) |  | — |
| ⬜ | 1976 | [Number of Ways to Arrive at Destination](https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/) |  | — |
| ⬜ | 2045 | [Second Minimum Time to Reach Destination](https://leetcode.com/problems/second-minimum-time-to-reach-destination/) |  | — |
| ⬜ | 2203 | [Minimum Weighted Subgraph With the Required Paths](https://leetcode.com/problems/minimum-weighted-subgraph-with-the-required-paths/) |  | — |
| ⬜ | 2290 | [Minimum Obstacle Removal to Reach Corner](https://leetcode.com/problems/minimum-obstacle-removal-to-reach-corner/) |  | — |
| ⬜ | 2577 | [Minimum Time to Visit a Cell In a Grid](https://leetcode.com/problems/minimum-time-to-visit-a-cell-in-a-grid/) |  | — |
| ⬜ | 2812 | [Find the Safest Path in a Grid](https://leetcode.com/problems/find-the-safest-path-in-a-grid/) |  | — |

### Pattern 24 — Shortest Path (Bellman-Ford / BFS+K)

`░░░░░░░░░░` **0/2**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ⬜ | 787 | [Cheapest Flights Within K Stops](https://leetcode.com/problems/cheapest-flights-within-k-stops/) |  | — |
| ⬜ | 1129 | [Shortest Path with Alternating Colors](https://leetcode.com/problems/shortest-path-with-alternating-colors/) |  | — |

### Pattern 25 — Union-Find

`███░░░░░░░` **4/12**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 200 | [Number of Islands](https://leetcode.com/problems/number-of-islands/) | ⭐ | [`number_of_islands.cpp`](./DSA/graphs/number_of_islands.cpp) |
| ✅ | 261 | [Graph Valid Tree](https://leetcode.com/problems/graph-valid-tree/) |  | [`cycle_detection_undirected.cpp`](./DSA/graphs/cycle_detection_undirected.cpp) |
| ⬜ | 305 | [Number of Islands II](https://leetcode.com/problems/number-of-islands-ii/) |  | — |
| ⬜ | 323 | [Number of Connected Components in an Undirected Graph](https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/) | ⭐ | — |
| ✅ | 547 | [Number of Provinces](https://leetcode.com/problems/number-of-provinces/) | ⭐ | [`number_of_provinces.cpp`](./DSA/graphs/number_of_provinces.cpp) |
| ✅ | 684 | [Redundant Connection](https://leetcode.com/problems/redundant-connection/) |  | [`union_find.cpp`](./DSA/graphs/union_find.cpp) |
| ⬜ | 721 | [Accounts Merge](https://leetcode.com/problems/accounts-merge/) |  | — |
| ⬜ | 737 | [Sentence Similarity II](https://leetcode.com/problems/sentence-similarity-ii/) |  | — |
| ⬜ | 947 | [Most Stones Removed with Same Row or Column](https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/) |  | — |
| ⬜ | 952 | [Largest Component Size by Common Factor](https://leetcode.com/problems/largest-component-size-by-common-factor/) |  | — |
| ⬜ | 959 | [Regions Cut By Slashes](https://leetcode.com/problems/regions-cut-by-slashes/) |  | — |
| ⬜ | 1101 | [The Earliest Moment When Everyone Become Friends](https://leetcode.com/problems/the-earliest-moment-when-everyone-become-friends/) |  | — |

### Pattern 26 — Strongly Connected Components (Kosaraju / Tarjan)

`█████░░░░░` **2/4**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 210 | [Course Schedule II](https://leetcode.com/problems/course-schedule-ii/) | ⭐ | [`topological_sort_kahn.cpp`](./DSA/graphs/topological_sort_kahn.cpp) |
| ✅ | 547 | [Number of Provinces](https://leetcode.com/problems/number-of-provinces/) | ⭐ | [`number_of_provinces.cpp`](./DSA/graphs/number_of_provinces.cpp) |
| ⬜ | 1192 | [Critical Connections in a Network](https://leetcode.com/problems/critical-connections-in-a-network/) |  | — |
| ⬜ | 2127 | [Maximum Employees to Be Invited to a Meeting](https://leetcode.com/problems/maximum-employees-to-be-invited-to-a-meeting/) |  | — |

### Pattern 27 — Bridges & Articulation Points (Tarjan low-link)

`░░░░░░░░░░` **0/2**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ⬜ | 1192 | [Critical Connections in a Network](https://leetcode.com/problems/critical-connections-in-a-network/) |  | — |
| ⬜ | 2360 | [Longest Cycle in a Graph](https://leetcode.com/problems/longest-cycle-in-a-graph/) |  | — |

### Pattern 28 — Minimum Spanning Tree (Kruskal / Prim / DSU + heap)

`░░░░░░░░░░` **0/4**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ⬜ | 1135 | [Connecting Cities With Minimum Cost](https://leetcode.com/problems/connecting-cities-with-minimum-cost/) |  | — |
| ⬜ | 1584 | [Min Cost to Connect All Points](https://leetcode.com/problems/min-cost-to-connect-all-points/) |  | — |
| ⬜ | 1168 | [Optimize Water Distribution in a Village](https://leetcode.com/problems/optimize-water-distribution-in-a-village/) |  | — |
| ⬜ | 1489 | [Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree](https://leetcode.com/problems/find-critical-and-pseudocritical-edges-in-minimum-spanning-tree/) |  | — |

### Pattern 29 — Bidirectional BFS

`███░░░░░░░` **1/3**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 127 | [Word Ladder](https://leetcode.com/problems/word-ladder/) | ⭐ | [`word_ladder_bfs.cpp`](./DSA/graphs/word_ladder_bfs.cpp) |
| ⬜ | 126 | [Word Ladder II](https://leetcode.com/problems/word-ladder-ii/) |  | — |
| ⬜ | 815 | [Bus Routes](https://leetcode.com/problems/bus-routes/) |  | — |

---

## V. Dynamic Programming (DP) Patterns

47 problems · **13 done** · `███░░░░░░░` 27%

### Pattern 30 — Fibonacci Style

`████░░░░░░` **3/8**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 70 | [Climbing Stairs](https://leetcode.com/problems/climbing-stairs/) | ⭐ | [`climbing_stairs.cpp`](./DSA/dynamic_programming/climbing_stairs.cpp) |
| ⬜ | 91 | [Decode Ways](https://leetcode.com/problems/decode-ways/) |  | — |
| ✅ | 198 | [House Robber](https://leetcode.com/problems/house-robber/) | ⭐ | [`house_robber.cpp`](./DSA/dynamic_programming/house_robber.cpp) · [`house_robber.cpp`](./DSA/recursion/house_robber.cpp) |
| ✅ | 213 | [House Robber II](https://leetcode.com/problems/house-robber-ii/) |  | [`house_robber_2.cpp`](./DSA/dynamic_programming/house_robber_2.cpp) |
| ⬜ | 337 | [House Robber III](https://leetcode.com/problems/house-robber-iii/) |  | — |
| ⬜ | 509 | [Fibonacci Number](https://leetcode.com/problems/fibonacci-number/) |  | — |
| ⬜ | 740 | [Delete and Earn](https://leetcode.com/problems/delete-and-earn/) |  | — |
| ⬜ | 746 | [Min Cost Climbing Stairs](https://leetcode.com/problems/min-cost-climbing-stairs/) |  | — |

### Pattern 31 — Kadane's Algorithm for Max/Min Subarray

`████░░░░░░` **2/5**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 53 | [Maximum Subarray](https://leetcode.com/problems/maximum-subarray/) | ⭐ | [`kadanes_max_subarray.cpp`](./DSA/arrays/kadanes_max_subarray.cpp) · [`maximum_sum.cpp`](./DSA/recursion/maximum_sum.cpp) |
| ⬜ | 918 | [Maximum Sum Circular Subarray](https://leetcode.com/problems/maximum-sum-circular-subarray/) |  | — |
| ⬜ | 2321 | [Maximum Score Of Spliced Array](https://leetcode.com/problems/maximum-score-of-spliced-array/) |  | — |
| ⬜ | 1749 | [Maximum Absolute Sum of Any Subarray](https://leetcode.com/problems/maximum-absolute-sum-of-any-subarray/) |  | — |
| ✅ | 152 | [Maximum Product Subarray](https://leetcode.com/problems/maximum-product-subarray/) | ⭐ | [`max_product_subarray.cpp`](./DSA/dynamic_programming/max_product_subarray.cpp) |

### Pattern 32 — Coin Change / Unbounded Knapsack Style

`███████░░░` **2/3**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 322 | [Coin Change](https://leetcode.com/problems/coin-change/) | ⭐ | [`coin_change_min_coins.cpp`](./DSA/dynamic_programming/coin_change_min_coins.cpp) · [`coin_change.cpp`](./DSA/recursion/coin_change.cpp) · [`cut_rod_max_segments.cpp`](./DSA/recursion/cut_rod_max_segments.cpp) |
| ⬜ | 377 | [Combination Sum IV](https://leetcode.com/problems/combination-sum-iv/) |  | — |
| ✅ | 518 | [Coin Change II](https://leetcode.com/problems/coin-change-ii/) |  | [`coin_change_ways.cpp`](./DSA/dynamic_programming/coin_change_ways.cpp) |

### Pattern 33 — 0/1 Knapsack, Subset Sum Style

`█████░░░░░` **1/2**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 416 | [Partition Equal Subset Sum](https://leetcode.com/problems/partition-equal-subset-sum/) | ⭐ | [`partition_equal_subset.cpp`](./DSA/dynamic_programming/partition_equal_subset.cpp) |
| ⬜ | 494 | [Target Sum](https://leetcode.com/problems/target-sum/) |  | — |

### Pattern 34 — Word Break Style

`░░░░░░░░░░` **0/2**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ⬜ | 139 | [Word Break](https://leetcode.com/problems/word-break/) | ⭐ | — |
| ⬜ | 140 | [Word Break II](https://leetcode.com/problems/word-break-ii/) |  | — |

### Pattern 35 — Longest Common Subsequence - LCS

`███░░░░░░░` **1/3**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 1143 | [Longest Common Subsequence](https://leetcode.com/problems/longest-common-subsequence/) | ⭐ | [`longest_common_subsequence.cpp`](./DSA/dynamic_programming/longest_common_subsequence.cpp) |
| ⬜ | 1092 | [Shortest Common Supersequence](https://leetcode.com/problems/shortest-common-supersequence/) |  | — |
| ⬜ | 1312 | [Minimum Insertion Steps to Make a String Palindrome](https://leetcode.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/) |  | — |

### Pattern 36 — Edit Distance / Levenshtein Distance

`███░░░░░░░` **1/3**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 72 | [Edit Distance](https://leetcode.com/problems/edit-distance/) |  | [`edit_distance.cpp`](./DSA/dynamic_programming/edit_distance.cpp) |
| ⬜ | 583 | [Delete Operation for Two Strings](https://leetcode.com/problems/delete-operation-for-two-strings/) |  | — |
| ⬜ | 712 | [Minimum ASCII Delete Sum for Two Strings](https://leetcode.com/problems/minimum-ascii-delete-sum-for-two-strings/) |  | — |

### Pattern 37 — Unique Paths on Grid

`███░░░░░░░` **2/7**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 62 | [Unique Paths](https://leetcode.com/problems/unique-paths/) | ⭐ | [`unique_paths_grid.cpp`](./DSA/dynamic_programming/unique_paths_grid.cpp) |
| ⬜ | 63 | [Unique Paths II](https://leetcode.com/problems/unique-paths-ii/) |  | — |
| ✅ | 64 | [Minimum Path Sum](https://leetcode.com/problems/minimum-path-sum/) |  | [`minimum_path_sum_grid.cpp`](./DSA/dynamic_programming/minimum_path_sum_grid.cpp) |
| ⬜ | 120 | [Triangle](https://leetcode.com/problems/triangle/) |  | — |
| ⬜ | 221 | [Maximal Square](https://leetcode.com/problems/maximal-square/) |  | — |
| ⬜ | 931 | [Minimum Falling Path Sum](https://leetcode.com/problems/minimum-falling-path-sum/) |  | — |
| ⬜ | 1277 | [Count Square Submatrices with All Ones](https://leetcode.com/problems/count-square-submatrices-with-all-ones/) |  | — |

### Pattern 38 — Interval DP

`░░░░░░░░░░` **0/2**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ⬜ | 312 | [Burst Balloons](https://leetcode.com/problems/burst-balloons/) |  | — |
| ⬜ | 546 | [Remove Boxes](https://leetcode.com/problems/remove-boxes/) |  | — |

### Pattern 39 — Catalan Numbers

`░░░░░░░░░░` **0/3**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ⬜ | 95 | [Unique Binary Search Trees II](https://leetcode.com/problems/unique-binary-search-trees-ii/) |  | — |
| ⬜ | 96 | [Unique Binary Search Trees](https://leetcode.com/problems/unique-binary-search-trees/) |  | — |
| ⬜ | 241 | [Different Ways to Add Parentheses](https://leetcode.com/problems/different-ways-to-add-parentheses/) |  | — |

### Pattern 40 — Longest Increasing Subsequence

`██░░░░░░░░` **1/4**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 300 | [Longest Increasing Subsequence](https://leetcode.com/problems/longest-increasing-subsequence/) | ⭐ | [`longest_increasing_subsequence.cpp`](./DSA/dynamic_programming/longest_increasing_subsequence.cpp) |
| ⬜ | 354 | [Russian Doll Envelopes](https://leetcode.com/problems/russian-doll-envelopes/) |  | — |
| ⬜ | 1671 | [Minimum Number of Removals to Make Mountain Array](https://leetcode.com/problems/minimum-number-of-removals-to-make-mountain-array/) |  | — |
| ⬜ | 2407 | [Longest Increasing Subsequence II](https://leetcode.com/problems/longest-increasing-subsequence-ii/) |  | — |

### Pattern 41 — Stock problems

`░░░░░░░░░░` **0/5**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ⬜ | 121 | [Best Time to Buy and Sell Stock](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/) | ⭐ | — |
| ⬜ | 122 | [Best Time to Buy and Sell Stock II](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/) |  | — |
| ⬜ | 123 | [Best Time to Buy and Sell Stock III](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/) |  | — |
| ⬜ | 188 | [Best Time to Buy and Sell Stock IV](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/) |  | — |
| ⬜ | 309 | [Best Time to Buy and Sell Stock with Cooldown](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/) |  | — |

---

## VI. Heap (Priority Queue) Patterns

22 problems · **5 done** · `██░░░░░░░░` 22%

### Pattern 42 — Top K Elements

`████░░░░░░` **3/8**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 215 | [Kth Largest Element in an Array](https://leetcode.com/problems/kth-largest-element-in-an-array/) | ⭐ | [`find_k_greatest_elements.cpp`](./DSA/heaps/find_k_greatest_elements.cpp) · [`find_k_smallest_elements.cpp`](./DSA/heaps/find_k_smallest_elements.cpp) |
| ✅ | 347 | [Top K Frequent Elements](https://leetcode.com/problems/top-k-frequent-elements/) | ⭐ | [`top_k_frequent_elements.cpp`](./DSA/hash_map/top_k_frequent_elements.cpp) |
| ⬜ | 451 | [Sort Characters By Frequency](https://leetcode.com/problems/sort-characters-by-frequency/) |  | — |
| ⬜ | 506 | [Relative Ranks](https://leetcode.com/problems/relative-ranks/) |  | — |
| ✅ | 703 | [Kth Largest Element in a Stream](https://leetcode.com/problems/kth-largest-element-in-a-stream/) |  | [`kth_smallest_using_min_heap.cpp`](./DSA/heaps/kth_smallest_using_min_heap.cpp) |
| ⬜ | 973 | [K Closest Points to Origin](https://leetcode.com/problems/k-closest-points-to-origin/) |  | — |
| ⬜ | 1046 | [Last Stone Weight](https://leetcode.com/problems/last-stone-weight/) |  | — |
| ⬜ | 2558 | [Take Gifts From the Richest Pile](https://leetcode.com/problems/take-gifts-from-the-richest-pile/) |  | — |

### Pattern 43 — Two Heaps for Median Finding

`█████░░░░░` **1/2**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 295 | [Find Median from Data Stream](https://leetcode.com/problems/find-median-from-data-stream/) | ⭐ | [`find_median_from_data_stream.cpp`](./DSA/heaps/find_median_from_data_stream.cpp) |
| ⬜ | 1825 | [Finding MK Average](https://leetcode.com/problems/finding-mk-average/) |  | — |

### Pattern 44 — K-way Merge

`░░░░░░░░░░` **0/4**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ⬜ | 23 | [Merge k Sorted Lists](https://leetcode.com/problems/merge-k-sorted-lists/) | ⭐ | — |
| ⬜ | 373 | [Find K Pairs with Smallest Sums](https://leetcode.com/problems/find-k-pairs-with-smallest-sums/) |  | — |
| ⬜ | 378 | [Kth Smallest Element in a Sorted Matrix](https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/) |  | — |
| ⬜ | 632 | [Smallest Range Covering Elements from K Lists](https://leetcode.com/problems/smallest-range-covering-elements-from-k-lists/) |  | — |

### Pattern 45 — Scheduling / Minimum Cost

`█░░░░░░░░░` **1/8**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 253 | [Meeting Rooms II](https://leetcode.com/problems/meeting-rooms-ii/) | ⭐ | [`meeting_rooms_ii.cpp`](./DSA/intervals/meeting_rooms_ii.cpp) |
| ⬜ | 767 | [Reorganize String](https://leetcode.com/problems/reorganize-string/) | ⭐ | — |
| ⬜ | 857 | [Minimum Cost to Hire K Workers](https://leetcode.com/problems/minimum-cost-to-hire-k-workers/) |  | — |
| ⬜ | 1642 | [Furthest Building You Can Reach](https://leetcode.com/problems/furthest-building-you-can-reach/) |  | — |
| ⬜ | 1792 | [Maximum Average Pass Ratio](https://leetcode.com/problems/maximum-average-pass-ratio/) |  | — |
| ⬜ | 1834 | [Single-Threaded CPU](https://leetcode.com/problems/singlethreaded-cpu/) |  | — |
| ⬜ | 1942 | [The Number of the Smallest Unoccupied Chair](https://leetcode.com/problems/the-number-of-the-smallest-unoccupied-chair/) |  | — |
| ⬜ | 2402 | [Meeting Rooms III](https://leetcode.com/problems/meeting-rooms-iii/) |  | — |

---

## VII. Backtracking Patterns

19 problems · **10 done** · `█████░░░░░` 52%

### Pattern 46 — Subsets (Include/Exclude)

`█████░░░░░` **2/4**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 17 | [Letter Combinations of a Phone Number](https://leetcode.com/problems/letter-combinations-of-a-phone-number/) |  | [`letter_combinations.cpp`](./DSA/backtracking/letter_combinations.cpp) · [`phone_keypad_problem.cpp`](./DSA/recursion/phone_keypad_problem.cpp) |
| ⬜ | 77 | [Combinations](https://leetcode.com/problems/combinations/) |  | — |
| ✅ | 78 | [Subsets](https://leetcode.com/problems/subsets/) | ⭐ | [`subsets.cpp`](./DSA/backtracking/subsets.cpp) · [`generate_subsequences.cpp`](./DSA/recursion/generate_subsequences.cpp) · [`generate_subsets.cpp`](./DSA/recursion/generate_subsets.cpp) |
| ⬜ | 90 | [Subsets II](https://leetcode.com/problems/subsets-ii/) |  | — |

### Pattern 47 — Permutations

`███░░░░░░░` **1/3**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ⬜ | 31 | [Next Permutation](https://leetcode.com/problems/next-permutation/) |  | — |
| ✅ | 46 | [Permutations](https://leetcode.com/problems/permutations/) | ⭐ | [`permutations.cpp`](./DSA/backtracking/permutations.cpp) · [`permutations_of_string.cpp`](./DSA/recursion/permutations_of_string.cpp) |
| ⬜ | 60 | [Permutation Sequence](https://leetcode.com/problems/permutation-sequence/) |  | — |

### Pattern 48 — Combination Sum

`██████████` **2/2**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 39 | [Combination Sum](https://leetcode.com/problems/combination-sum/) | ⭐ | [`combination_sum.cpp`](./DSA/backtracking/combination_sum.cpp) |
| ✅ | 40 | [Combination Sum II](https://leetcode.com/problems/combination-sum-ii/) |  | [`combination_sum_ii.cpp`](./DSA/backtracking/combination_sum_ii.cpp) |

### Pattern 49 — Parentheses Generation

`█████░░░░░` **1/2**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 22 | [Generate Parentheses](https://leetcode.com/problems/generate-parentheses/) |  | [`generate_parenthesis.cpp`](./DSA/recursion/generate_parenthesis.cpp) |
| ⬜ | 301 | [Remove Invalid Parentheses](https://leetcode.com/problems/remove-invalid-parentheses/) |  | — |

### Pattern 50 — Word Search / Path Finding in Grid

`███░░░░░░░` **1/3**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 79 | [Word Search](https://leetcode.com/problems/word-search/) | ⭐ | [`word_search.cpp`](./DSA/trie/word_search.cpp) |
| ⬜ | 212 | [Word Search II](https://leetcode.com/problems/word-search-ii/) |  | — |
| ⬜ | 2018 | [Check if Word Can Be Placed In Crossword](https://leetcode.com/problems/check-if-word-can-be-placed-in-crossword/) |  | — |

### Pattern 51 — N-Queens / Constraint Satisfaction

`██████████` **2/2**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 37 | [Sudoku Solver](https://leetcode.com/problems/sudoku-solver/) |  | [`sudoku_solver.cpp`](./DSA/backtracking/sudoku_solver.cpp) |
| ✅ | 51 | [N-Queens](https://leetcode.com/problems/nqueens/) | ⭐ | [`n_queens.cpp`](./DSA/backtracking/n_queens.cpp) |

### Pattern 52 — Palindrome Partitioning

`███░░░░░░░` **1/3**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 131 | [Palindrome Partitioning](https://leetcode.com/problems/palindrome-partitioning/) |  | [`palindrome_partitioning.cpp`](./DSA/backtracking/palindrome_partitioning.cpp) |
| ⬜ | 132 | [Palindrome Partitioning II](https://leetcode.com/problems/palindrome-partitioning-ii/) |  | — |
| ⬜ | 1457 | [Pseudo-Palindromic Paths in a Binary Tree](https://leetcode.com/problems/pseudopalindromic-paths-in-a-binary-tree/) |  | — |

---

## VIII. Greedy Patterns

18 problems · **5 done** · `███░░░░░░░` 27%

### Pattern 53 — Interval Merging/Scheduling

`████░░░░░░` **2/5**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 56 | [Merge Intervals](https://leetcode.com/problems/merge-intervals/) | ⭐ | [`merge_intervals.cpp`](./DSA/intervals/merge_intervals.cpp) |
| ✅ | 57 | [Insert Interval](https://leetcode.com/problems/insert-interval/) | ⭐ | [`insert_interval.cpp`](./DSA/intervals/insert_interval.cpp) |
| ⬜ | 759 | [Employee Free Time](https://leetcode.com/problems/employee-free-time/) |  | — |
| ⬜ | 986 | [Interval List Intersections](https://leetcode.com/problems/interval-list-intersections/) |  | — |
| ⬜ | 2406 | [Divide Intervals Into Minimum Number of Groups](https://leetcode.com/problems/divide-intervals-into-minimum-number-of-groups/) |  | — |

### Pattern 54 — Jump Game Reachability/Minimization

`██████████` **2/2**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 45 | [Jump Game II](https://leetcode.com/problems/jump-game-ii/) |  | [`jump_game_2.cpp`](./DSA/greedy/jump_game_2.cpp) |
| ✅ | 55 | [Jump Game](https://leetcode.com/problems/jump-game/) | ⭐ | [`jump_game.cpp`](./DSA/greedy/jump_game.cpp) |

### Pattern 55 — Buy/Sell Stock

`░░░░░░░░░░` **0/2**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ⬜ | 121 | [Best Time to Buy and Sell Stock](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/) | ⭐ | — |
| ⬜ | 122 | [Best Time to Buy and Sell Stock II](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/) |  | — |

### Pattern 56 — Gas Station Circuit

`░░░░░░░░░░` **0/2**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ⬜ | 134 | [Gas Station](https://leetcode.com/problems/gas-station/) |  | — |
| ⬜ | 2202 | [Maximize the Topmost Element After K Moves](https://leetcode.com/problems/maximize-the-topmost-element-after-k-moves/) |  | — |

### Pattern 57 — Task Scheduling

`░░░░░░░░░░` **0/3**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ⬜ | 621 | [Task Scheduler](https://leetcode.com/problems/task-scheduler/) |  | — |
| ⬜ | 767 | [Reorganize String](https://leetcode.com/problems/reorganize-string/) | ⭐ | — |
| ⬜ | 1054 | [Distant Barcodes](https://leetcode.com/problems/distant-barcodes/) |  | — |

### Pattern 58 — Sorting Based

`██░░░░░░░░` **1/4**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 455 | [Assign Cookies](https://leetcode.com/problems/assign-cookies/) |  | [`assign_cookies.cpp`](./DSA/greedy/assign_cookies.cpp) |
| ⬜ | 135 | [Candy](https://leetcode.com/problems/candy/) |  | — |
| ⬜ | 406 | [Queue Reconstruction by Height](https://leetcode.com/problems/queue-reconstruction-by-height/) |  | — |
| ⬜ | 1029 | [Two City Scheduling](https://leetcode.com/problems/two-city-scheduling/) |  | — |

---

## IX. Binary Search Patterns

27 problems · **9 done** · `███░░░░░░░` 33%

### Pattern 59 — On Sorted Array/List

`█████░░░░░` **4/8**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ⬜ | 35 | [Search Insert Position](https://leetcode.com/problems/search-insert-position/) |  | — |
| ✅ | 69 | [Sqrt(x)](https://leetcode.com/problems/sqrtx/) |  | [`square_root_binary_search.cpp`](./DSA/binary_search/square_root_binary_search.cpp) |
| ✅ | 74 | [Search a 2D Matrix](https://leetcode.com/problems/search-a-2d-matrix/) | ⭐ | [`search_2d_matrix.cpp`](./DSA/binary_search/search_2d_matrix.cpp) |
| ⬜ | 278 | [First Bad Version](https://leetcode.com/problems/first-bad-version/) |  | — |
| ⬜ | 374 | [Guess Number Higher or Lower](https://leetcode.com/problems/guess-number-higher-or-lower/) |  | — |
| ✅ | 540 | [Single Element in a Sorted Array](https://leetcode.com/problems/single-element-in-a-sorted-array/) |  | [`odd_occurrence_binary_search.cpp`](./DSA/binary_search/odd_occurrence_binary_search.cpp) · [`search_nearly_sorted.cpp`](./DSA/binary_search/search_nearly_sorted.cpp) |
| ✅ | 704 | [Binary Search](https://leetcode.com/problems/binary-search/) |  | [`binary_search.cpp`](./DSA/arrays/binary_search.cpp) · [`exponential_search.cpp`](./DSA/binary_search/exponential_search.cpp) · [`unbounded_binary_search.cpp`](./DSA/binary_search/unbounded_binary_search.cpp) |
| ⬜ | 1539 | [Kth Missing Positive Number](https://leetcode.com/problems/kth-missing-positive-number/) |  | — |

### Pattern 60 — Find Min/Max in Rotated Sorted Array

`███░░░░░░░` **2/6**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 33 | [Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/) | ⭐ | [`pivot_element.cpp`](./DSA/binary_search/pivot_element.cpp) |
| ⬜ | 81 | [Search in Rotated Sorted Array II](https://leetcode.com/problems/search-in-rotated-sorted-array-ii/) |  | — |
| ⬜ | 153 | [Find Minimum in Rotated Sorted Array](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/) | ⭐ | — |
| ✅ | 162 | [Find Peak Element](https://leetcode.com/problems/find-peak-element/) |  | [`peak_element.cpp`](./DSA/binary_search/peak_element.cpp) |
| ⬜ | 852 | [Peak Index in a Mountain Array](https://leetcode.com/problems/peak-index-in-a-mountain-array/) |  | — |
| ⬜ | 1095 | [Find in Mountain Array](https://leetcode.com/problems/find-in-mountain-array/) |  | — |

### Pattern 61 — On Answer / Condition Function

`█░░░░░░░░░` **1/8**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 410 | [Split Array Largest Sum](https://leetcode.com/problems/split-array-largest-sum/) |  | [`aggressive_cows.cpp`](./DSA/binary_search/aggressive_cows.cpp) · [`book_allocation.cpp`](./DSA/binary_search/book_allocation.cpp) · [`ekos_spoj.cpp`](./DSA/binary_search/ekos_spoj.cpp) · [`painter_partition.cpp`](./DSA/binary_search/painter_partition.cpp) · [`pratas_poj.cpp`](./DSA/binary_search/pratas_poj.cpp) |
| ⬜ | 774 | [Minimize Max Distance to Gas Station](https://leetcode.com/problems/minimize-max-distance-to-gas-station/) |  | — |
| ⬜ | 875 | [Koko Eating Bananas](https://leetcode.com/problems/koko-eating-bananas/) | ⭐ | — |
| ⬜ | 1011 | [Capacity To Ship Packages Within D Days](https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/) |  | — |
| ⬜ | 1482 | [Minimum Number of Days to Make m Bouquets](https://leetcode.com/problems/minimum-number-of-days-to-make-m-bouquets/) |  | — |
| ⬜ | 1760 | [Minimum Limit of Balls in a Bag](https://leetcode.com/problems/minimum-limit-of-balls-in-a-bag/) |  | — |
| ⬜ | 2064 | [Minimized Maximum of Products Distributed to Any Store](https://leetcode.com/problems/minimized-maximum-of-products-distributed-to-any-store/) |  | — |
| ⬜ | 2226 | [Maximum Candies Allocated to K Children](https://leetcode.com/problems/maximum-candies-allocated-to-k-children/) |  | — |

### Pattern 62 — Find First/Last Occurrence

`██████████` **2/2**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 34 | [Find First and Last Position of Element in Sorted Array](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/) |  | [`first_occurrence.cpp`](./DSA/arrays/first_occurrence.cpp) · [`total_occurrences.cpp`](./DSA/binary_search/total_occurrences.cpp) |
| ✅ | 658 | [Find K Closest Elements](https://leetcode.com/problems/find-k-closest-elements/) |  | [`k_closest_elements.cpp`](./DSA/binary_search/k_closest_elements.cpp) |

### Pattern 63 — Median / Kth across Two Sorted Arrays

`░░░░░░░░░░` **0/3**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ⬜ | 4 | [Median of Two Sorted Arrays](https://leetcode.com/problems/median-of-two-sorted-arrays/) |  | — |
| ⬜ | 719 | [Find K-th Smallest Pair Distance](https://leetcode.com/problems/find-kth-smallest-pair-distance/) |  | — |
| ⬜ | 378 | [Kth Smallest Element in a Sorted Matrix](https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/) |  | — |

---

## X. Stack Patterns

26 problems · **9 done** · `███░░░░░░░` 34%

### Pattern 64 — Valid Parentheses Matching

`████░░░░░░` **2/5**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 20 | [Valid Parentheses](https://leetcode.com/problems/valid-parentheses/) | ⭐ | [`valid_parentheses.cpp`](./DSA/stacks/valid_parentheses.cpp) |
| ⬜ | 32 | [Longest Valid Parentheses](https://leetcode.com/problems/longest-valid-parentheses/) |  | — |
| ⬜ | 921 | [Minimum Add to Make Parentheses Valid](https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/) |  | — |
| ✅ | 1249 | [Minimum Remove to Make Valid Parentheses](https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/) |  | [`minimum_bracket_reversals.cpp`](./DSA/stacks/minimum_bracket_reversals.cpp) |
| ⬜ | 1963 | [Minimum Number of Swaps to Make the String Balanced](https://leetcode.com/problems/minimum-number-of-swaps-to-make-the-string-balanced/) |  | — |

### Pattern 65 — Monotonic Stack

`███░░░░░░░` **3/9**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ⬜ | 402 | [Remove K Digits](https://leetcode.com/problems/remove-k-digits/) |  | — |
| ✅ | 496 | [Next Greater Element I](https://leetcode.com/problems/next-greater-element-i/) |  | [`monotonic_stack.cpp`](./CP/monotonic_stack/monotonic_stack.cpp) · [`next_smaller_element.cpp`](./DSA/stacks/next_smaller_element.cpp) |
| ✅ | 503 | [Next Greater Element II](https://leetcode.com/problems/next-greater-element-ii/) |  | [`previous_smaller_element.cpp`](./DSA/stacks/previous_smaller_element.cpp) |
| ⬜ | 739 | [Daily Temperatures](https://leetcode.com/problems/daily-temperatures/) | ⭐ | — |
| ✅ | 901 | [Online Stock Span](https://leetcode.com/problems/online-stock-span/) |  | [`online_stock_span.cpp`](./DSA/stacks/online_stock_span.cpp) |
| ⬜ | 907 | [Sum of Subarray Minimums](https://leetcode.com/problems/sum-of-subarray-minimums/) |  | — |
| ⬜ | 962 | [Maximum Width Ramp](https://leetcode.com/problems/maximum-width-ramp/) |  | — |
| ⬜ | 1475 | [Final Prices With a Special Discount in a Shop](https://leetcode.com/problems/final-prices-with-a-special-discount-in-a-shop/) |  | — |
| ⬜ | 1673 | [Find the Most Competitive Subsequence](https://leetcode.com/problems/find-the-most-competitive-subsequence/) |  | — |

### Pattern 66 — Expression Evaluation

`░░░░░░░░░░` **0/4**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ⬜ | 150 | [Evaluate Reverse Polish Notation](https://leetcode.com/problems/evaluate-reverse-polish-notation/) |  | — |
| ⬜ | 224 | [Basic Calculator](https://leetcode.com/problems/basic-calculator/) |  | — |
| ⬜ | 227 | [Basic Calculator II](https://leetcode.com/problems/basic-calculator-ii/) |  | — |
| ⬜ | 772 | [Basic Calculator III](https://leetcode.com/problems/basic-calculator-iii/) |  | — |

### Pattern 67 — Simulation / Backtracking Helper

`███░░░░░░░` **1/3**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ⬜ | 71 | [Simplify Path](https://leetcode.com/problems/simplify-path/) |  | — |
| ⬜ | 394 | [Decode String](https://leetcode.com/problems/decode-string/) |  | — |
| ✅ | 735 | [Asteroid Collision](https://leetcode.com/problems/asteroid-collision/) |  | [`asteroid_collision.cpp`](./DSA/stacks/asteroid_collision.cpp) |

### Pattern 68 — Min Stack Design

`███████░░░` **2/3**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 155 | [Min Stack](https://leetcode.com/problems/min-stack/) |  | [`min_stack.cpp`](./DSA/stacks/min_stack.cpp) · [`two_stacks_in_array.cpp`](./DSA/stacks/two_stacks_in_array.cpp) |
| ⬜ | 895 | [Maximum Frequency Stack](https://leetcode.com/problems/maximum-frequency-stack/) |  | — |
| ✅ | 901 | [Online Stock Span](https://leetcode.com/problems/online-stock-span/) |  | [`online_stock_span.cpp`](./DSA/stacks/online_stock_span.cpp) |

### Pattern 69 — Largest Rectangle in Histogram

`█████░░░░░` **1/2**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 84 | [Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/) | ⭐ | [`largest_rectangle_histogram.cpp`](./DSA/stacks/largest_rectangle_histogram.cpp) |
| ⬜ | 85 | [Maximal Rectangle](https://leetcode.com/problems/maximal-rectangle/) |  | — |

---

## XI. Bit Manipulation Patterns

12 problems · **5 done** · `████░░░░░░` 41%

### Pattern 70 — Bitwise XOR - Finding Single/Missing Number

`█████░░░░░` **2/4**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 136 | [Single Number](https://leetcode.com/problems/single-number/) | ⭐ | [`single_number.cpp`](./DSA/bit_manipulation/single_number.cpp) |
| ⬜ | 137 | [Single Number II](https://leetcode.com/problems/single-number-ii/) |  | — |
| ✅ | 268 | [Missing Number](https://leetcode.com/problems/missing-number/) | ⭐ | [`missing_element.cpp`](./DSA/binary_search/missing_element.cpp) |
| ⬜ | 389 | [Find the Difference](https://leetcode.com/problems/find-the-difference/) |  | — |

### Pattern 71 — Bitwise AND - Counting Set Bits (Hamming Weight)

`███░░░░░░░` **1/3**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ⬜ | 191 | [Number of 1 Bits](https://leetcode.com/problems/number-of-1-bits/) | ⭐ | — |
| ✅ | 231 | [Power of Two](https://leetcode.com/problems/power-of-two/) |  | [`power_of_two.cpp`](./DSA/bit_manipulation/power_of_two.cpp) |
| ⬜ | 477 | [Total Hamming Distance](https://leetcode.com/problems/total-hamming-distance/) |  | — |

### Pattern 72 — Bitwise DP - Counting Bits Optimization

`███░░░░░░░` **1/3**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 338 | [Counting Bits](https://leetcode.com/problems/counting-bits/) | ⭐ | [`counting_bits.cpp`](./DSA/bit_manipulation/counting_bits.cpp) |
| ⬜ | 1494 | [Parallel Courses II](https://leetcode.com/problems/parallel-courses-ii/) |  | — |
| ⬜ | 1442 | [Count Triplets That Can Form Two Arrays of Equal XOR](https://leetcode.com/problems/count-triplets-that-can-form-two-arrays-of-equal-xor/) |  | — |

### Pattern 73 — Bitwise Operations - Power of Two/Four Check

`█████░░░░░` **1/2**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 231 | [Power of Two](https://leetcode.com/problems/power-of-two/) |  | [`power_of_two.cpp`](./DSA/bit_manipulation/power_of_two.cpp) |
| ⬜ | 342 | [Power of Four](https://leetcode.com/problems/power-of-four/) |  | — |

---

## XII. Linked List Manipulation Patterns

17 problems · **5 done** · `███░░░░░░░` 29%

### Pattern 74 — In-place Reversal

`█████░░░░░` **3/6**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ⬜ | 83 | [Remove Duplicates from Sorted List](https://leetcode.com/problems/remove-duplicates-from-sorted-list/) |  | — |
| ⬜ | 92 | [Reverse Linked List II](https://leetcode.com/problems/reverse-linked-list-ii/) | ⭐ | — |
| ✅ | 206 | [Reverse Linked List](https://leetcode.com/problems/reverse-linked-list/) | ⭐ | [`reverse_linked_list.cpp`](./DSA/linked_list/reverse_linked_list.cpp) · [`reverse_queue.cpp`](./DSA/queues/reverse_queue.cpp) |
| ✅ | 25 | [Reverse Nodes in k-Group](https://leetcode.com/problems/reverse-nodes-in-kgroup/) |  | [`k_group_reversal.cpp`](./DSA/linked_list/k_group_reversal.cpp) · [`reverse_k_queue_elements.cpp`](./DSA/queues/reverse_k_queue_elements.cpp) |
| ✅ | 234 | [Palindrome Linked List](https://leetcode.com/problems/palindrome-linked-list/) |  | [`palindrome_linked_list.cpp`](./DSA/linked_list/palindrome_linked_list.cpp) |
| ⬜ | 82 | [Remove Duplicates from Sorted List II](https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/) |  | — |

### Pattern 75 — Merging Two Sorted Lists

`░░░░░░░░░░` **0/2**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ⬜ | 21 | [Merge Two Sorted Lists](https://leetcode.com/problems/merge-two-sorted-lists/) | ⭐ | — |
| ⬜ | 23 | [Merge k Sorted Lists](https://leetcode.com/problems/merge-k-sorted-lists/) | ⭐ | — |

### Pattern 76 — Addition of Numbers

`██████████` **2/2**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 2 | [Add Two Numbers](https://leetcode.com/problems/add-two-numbers/) |  | [`add_two_linked_lists.cpp`](./DSA/linked_list/add_two_linked_lists.cpp) |
| ✅ | 369 | [Plus One Linked List](https://leetcode.com/problems/plus-one-linked-list/) |  | [`addone.cpp`](./DSA/linked_list/addone.cpp) |

### Pattern 77 — Intersection Detection

`░░░░░░░░░░` **0/2**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ⬜ | 160 | [Intersection of Two Linked Lists](https://leetcode.com/problems/intersection-of-two-linked-lists/) |  | — |
| ⬜ | 599 | [Minimum Index Sum of Two Lists](https://leetcode.com/problems/minimum-index-sum-of-two-lists/) |  | — |

### Pattern 78 — Reordering / Partitioning

`░░░░░░░░░░` **0/5**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ⬜ | 24 | [Swap Nodes in Pairs](https://leetcode.com/problems/swap-nodes-in-pairs/) |  | — |
| ⬜ | 61 | [Rotate List](https://leetcode.com/problems/rotate-list/) |  | — |
| ⬜ | 86 | [Partition List](https://leetcode.com/problems/partition-list/) |  | — |
| ⬜ | 143 | [Reorder List](https://leetcode.com/problems/reorder-list/) |  | — |
| ⬜ | 328 | [Odd Even Linked List](https://leetcode.com/problems/odd-even-linked-list/) |  | — |

---

## XIII. Array/Matrix Manipulation Patterns

24 problems · **5 done** · `██░░░░░░░░` 20%

### Pattern 79 — In-place Rotation

`██████████` **3/3**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 48 | [Rotate Image](https://leetcode.com/problems/rotate-image/) | ⭐ | [`rotate_matrix.cpp`](./DSA/arrays/rotate_matrix.cpp) |
| ✅ | 189 | [Rotate Array](https://leetcode.com/problems/rotate-array/) |  | [`rotate_array.cpp`](./DSA/arrays/rotate_array.cpp) · [`shift_one.cpp`](./DSA/arrays/shift_one.cpp) |
| ✅ | 867 | [Transpose Matrix](https://leetcode.com/problems/transpose-matrix/) |  | [`transpose_matrix.cpp`](./DSA/arrays/transpose_matrix.cpp) |

### Pattern 80 — Spiral Traversal

`░░░░░░░░░░` **0/4**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ⬜ | 54 | [Spiral Matrix](https://leetcode.com/problems/spiral-matrix/) | ⭐ | — |
| ⬜ | 59 | [Spiral Matrix II](https://leetcode.com/problems/spiral-matrix-ii/) |  | — |
| ⬜ | 885 | [Spiral Matrix III](https://leetcode.com/problems/spiral-matrix-iii/) |  | — |
| ⬜ | 2326 | [Spiral Matrix IV](https://leetcode.com/problems/spiral-matrix-iv/) |  | — |

### Pattern 81 — In-place Marking

`░░░░░░░░░░` **0/3**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ⬜ | 73 | [Set Matrix Zeroes](https://leetcode.com/problems/set-matrix-zeroes/) | ⭐ | — |
| ⬜ | 289 | [Game of Life](https://leetcode.com/problems/game-of-life/) |  | — |
| ⬜ | 498 | [Diagonal Traverse](https://leetcode.com/problems/diagonal-traverse/) |  | — |

### Pattern 82 — Prefix/Suffix Products

`░░░░░░░░░░` **0/3**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ⬜ | 238 | [Product of Array Except Self](https://leetcode.com/problems/product-of-array-except-self/) | ⭐ | — |
| ⬜ | 845 | [Longest Mountain in Array](https://leetcode.com/problems/longest-mountain-in-array/) |  | — |
| ⬜ | 2483 | [Minimum Penalty for a Shop](https://leetcode.com/problems/minimum-penalty-for-a-shop/) |  | — |

### Pattern 83 — Plus One

`░░░░░░░░░░` **0/4**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ⬜ | 66 | [Plus One](https://leetcode.com/problems/plus-one/) |  | — |
| ⬜ | 43 | [Multiply Strings](https://leetcode.com/problems/multiply-strings/) |  | — |
| ⬜ | 989 | [Add to Array-Form of Integer](https://leetcode.com/problems/add-to-arrayform-of-integer/) |  | — |
| ⬜ | 67 | [Add Binary](https://leetcode.com/problems/add-binary/) |  | — |

### Pattern 84 — In-place from End

`░░░░░░░░░░` **0/2**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ⬜ | 88 | [Merge Sorted Array](https://leetcode.com/problems/merge-sorted-array/) |  | — |
| ⬜ | 977 | [Squares of a Sorted Array](https://leetcode.com/problems/squares-of-a-sorted-array/) |  | — |

### Pattern 85 — Cyclic Sort

`████░░░░░░` **2/5**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ⬜ | 41 | [First Missing Positive](https://leetcode.com/problems/first-missing-positive/) |  | — |
| ✅ | 268 | [Missing Number](https://leetcode.com/problems/missing-number/) | ⭐ | [`missing_element.cpp`](./DSA/binary_search/missing_element.cpp) |
| ✅ | 287 | [Find the Duplicate Number](https://leetcode.com/problems/find-the-duplicate-number/) | ⭐ | [`duplicate_number.cpp`](./DSA/arrays/duplicate_number.cpp) |
| ⬜ | 442 | [Find All Duplicates in an Array](https://leetcode.com/problems/find-all-duplicates-in-an-array/) |  | — |
| ⬜ | 448 | [Find All Numbers Disappeared in an Array](https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/) |  | — |

---

## XIV. String Manipulation Patterns

20 problems · **3 done** · `██░░░░░░░░` 15%

### Pattern 86 — Palindrome Check

`███░░░░░░░` **1/3**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ⬜ | 9 | [Palindrome Number](https://leetcode.com/problems/palindrome-number/) |  | — |
| ✅ | 125 | [Valid Palindrome](https://leetcode.com/problems/valid-palindrome/) |  | [`palindrome_string.cpp`](./DSA/recursion/palindrome_string.cpp) · [`palindrome_string.cpp`](./DSA/strings/palindrome_string.cpp) |
| ⬜ | 680 | [Valid Palindrome II](https://leetcode.com/problems/valid-palindrome-ii/) |  | — |

### Pattern 87 — Anagram Check

`██████████` **2/2**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 49 | [Group Anagrams](https://leetcode.com/problems/group-anagrams/) | ⭐ | [`group_anagrams.cpp`](./DSA/hash_map/group_anagrams.cpp) |
| ✅ | 242 | [Valid Anagram](https://leetcode.com/problems/valid-anagram/) | ⭐ | [`valid_anagram.cpp`](./DSA/hash_map/valid_anagram.cpp) |

### Pattern 88 — Roman to Integer Conversion

`░░░░░░░░░░` **0/2**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ⬜ | 13 | [Roman to Integer](https://leetcode.com/problems/roman-to-integer/) |  | — |
| ⬜ | 12 | [Integer to Roman](https://leetcode.com/problems/integer-to-roman/) |  | — |

### Pattern 89 — String to Integer (atoi)

`░░░░░░░░░░` **0/2**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ⬜ | 8 | [String to Integer (atoi)](https://leetcode.com/problems/string-to-integer-atoi/) |  | — |
| ⬜ | 65 | [Valid Number](https://leetcode.com/problems/valid-number/) |  | — |

### Pattern 90 — Manual Simulation

`░░░░░░░░░░` **0/3**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ⬜ | 43 | [Multiply Strings](https://leetcode.com/problems/multiply-strings/) |  | — |
| ⬜ | 415 | [Add Strings](https://leetcode.com/problems/add-strings/) |  | — |
| ⬜ | 67 | [Add Binary](https://leetcode.com/problems/add-binary/) |  | — |

### Pattern 91 — String Matching - Naive / KMP / Rabin-Karp

`░░░░░░░░░░` **0/5**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ⬜ | 28 | [Find the Index of the First Occurrence in a String](https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/) |  | — |
| ⬜ | 214 | [Shortest Palindrome](https://leetcode.com/problems/shortest-palindrome/) |  | — |
| ⬜ | 686 | [Repeated String Match](https://leetcode.com/problems/repeated-string-match/) |  | — |
| ⬜ | 796 | [Rotate String](https://leetcode.com/problems/rotate-string/) |  | — |
| ⬜ | 3008 | [Find Beautiful Indices in the Given Array II](https://leetcode.com/problems/find-beautiful-indices-in-the-given-array-ii/) |  | — |

### Pattern 92 — Repeated Substring Pattern Detection

`░░░░░░░░░░` **0/3**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ⬜ | 459 | [Repeated Substring Pattern](https://leetcode.com/problems/repeated-substring-pattern/) |  | — |
| ⬜ | 28 | [Find the Index of the First Occurrence in a String](https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/) |  | — |
| ⬜ | 686 | [Repeated String Match](https://leetcode.com/problems/repeated-string-match/) |  | — |

---

## XV. Design Patterns

40 problems · **7 done** · `██░░░░░░░░` 17%

### Pattern 93 — Design (General/Specific)

`██░░░░░░░░` **6/33**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 146 | [LRU Cache](https://leetcode.com/problems/lru-cache/) | ⭐ | [`lru_cache.cpp`](./DSA/design/lru_cache.cpp) · [`doubly_linked_list.cpp`](./DSA/linked_list/doubly_linked_list.cpp) |
| ✅ | 155 | [Min Stack](https://leetcode.com/problems/min-stack/) |  | [`min_stack.cpp`](./DSA/stacks/min_stack.cpp) · [`two_stacks_in_array.cpp`](./DSA/stacks/two_stacks_in_array.cpp) |
| ✅ | 225 | [Implement Stack using Queues](https://leetcode.com/problems/implement-stack-using-queues/) |  | [`insert_at_bottom_of_stack.cpp`](./DSA/stacks/insert_at_bottom_of_stack.cpp) |
| ✅ | 232 | [Implement Queue using Stacks](https://leetcode.com/problems/implement-queue-using-stacks/) |  | [`queue_using_two_stacks.cpp`](./DSA/queues/queue_using_two_stacks.cpp) |
| ⬜ | 251 | [Flatten 2D Vector](https://leetcode.com/problems/flatten-2d-vector/) |  | — |
| ⬜ | 271 | [Encode and Decode Strings](https://leetcode.com/problems/encode-and-decode-strings/) |  | — |
| ✅ | 295 | [Find Median from Data Stream](https://leetcode.com/problems/find-median-from-data-stream/) | ⭐ | [`find_median_from_data_stream.cpp`](./DSA/heaps/find_median_from_data_stream.cpp) |
| ⬜ | 341 | [Flatten Nested List Iterator](https://leetcode.com/problems/flatten-nested-list-iterator/) |  | — |
| ⬜ | 346 | [Moving Average from Data Stream](https://leetcode.com/problems/moving-average-from-data-stream/) |  | — |
| ⬜ | 353 | [Design Snake Game](https://leetcode.com/problems/design-snake-game/) |  | — |
| ⬜ | 359 | [Logger Rate Limiter](https://leetcode.com/problems/logger-rate-limiter/) |  | — |
| ⬜ | 362 | [Design Hit Counter](https://leetcode.com/problems/design-hit-counter/) |  | — |
| ⬜ | 379 | [Design Phone Directory](https://leetcode.com/problems/design-phone-directory/) |  | — |
| ⬜ | 380 | [Insert Delete GetRandom O(1)](https://leetcode.com/problems/insert-delete-getrandom-o1/) | ⭐ | — |
| ⬜ | 432 | [All O`one Data Structure](https://leetcode.com/problems/all-oone-data-structure/) |  | — |
| ⬜ | 460 | [LFU Cache](https://leetcode.com/problems/lfu-cache/) |  | — |
| ⬜ | 604 | [Design Compressed String Iterator](https://leetcode.com/problems/design-compressed-string-iterator/) |  | — |
| ✅ | 622 | [Design Circular Queue](https://leetcode.com/problems/design-circular-queue/) |  | [`circular_queue_implementation.cpp`](./DSA/queues/circular_queue_implementation.cpp) |
| ⬜ | 641 | [Design Circular Deque](https://leetcode.com/problems/design-circular-deque/) |  | — |
| ⬜ | 642 | [Design Search Autocomplete System](https://leetcode.com/problems/design-search-autocomplete-system/) |  | — |
| ⬜ | 706 | [Design HashMap](https://leetcode.com/problems/design-hashmap/) |  | — |
| ⬜ | 715 | [Range Module](https://leetcode.com/problems/range-module/) |  | — |
| ⬜ | 900 | [RLE Iterator](https://leetcode.com/problems/rle-iterator/) |  | — |
| ⬜ | 981 | [Time Based Key-Value Store](https://leetcode.com/problems/time-based-keyvalue-store/) |  | — |
| ⬜ | 1146 | [Snapshot Array](https://leetcode.com/problems/snapshot-array/) |  | — |
| ⬜ | 1348 | [Tweet Counts Per Frequency](https://leetcode.com/problems/tweet-counts-per-frequency/) |  | — |
| ⬜ | 1352 | [Product of the Last K Numbers](https://leetcode.com/problems/product-of-the-last-k-numbers/) |  | — |
| ⬜ | 1381 | [Design a Stack With Increment Operation](https://leetcode.com/problems/design-a-stack-with-increment-operation/) |  | — |
| ⬜ | 1756 | [Design Most Recently Used Queue](https://leetcode.com/problems/design-most-recently-used-queue/) |  | — |
| ⬜ | 2013 | [Detect Squares](https://leetcode.com/problems/detect-squares/) |  | — |
| ⬜ | 2034 | [Stock Price Fluctuation](https://leetcode.com/problems/stock-price-fluctuation/) |  | — |
| ⬜ | 2296 | [Design a Text Editor](https://leetcode.com/problems/design-a-text-editor/) |  | — |
| ⬜ | 2336 | [Smallest Number in Infinite Set](https://leetcode.com/problems/smallest-number-in-infinite-set/) |  | — |

### Pattern 94 — Tries

`█░░░░░░░░░` **1/7**

| Status | LC | Problem | 30-day | Solution |
|:------:|---:|---------|:------:|----------|
| ✅ | 208 | [Implement Trie (Prefix Tree)](https://leetcode.com/problems/implement-trie-prefix-tree/) | ⭐ | [`trie_insert_search.cpp`](./DSA/trie/trie_insert_search.cpp) |
| ⬜ | 211 | [Design Add and Search Words Data Structure](https://leetcode.com/problems/design-add-and-search-words-data-structure/) | ⭐ | — |
| ⬜ | 720 | [Longest Word in Dictionary](https://leetcode.com/problems/longest-word-in-dictionary/) |  | — |
| ⬜ | 648 | [Replace Words](https://leetcode.com/problems/replace-words/) |  | — |
| ⬜ | 425 | [Word Squares](https://leetcode.com/problems/word-squares/) |  | — |
| ⬜ | 642 | [Design Search Autocomplete System](https://leetcode.com/problems/design-search-autocomplete-system/) |  | — |
| ⬜ | 745 | [Prefix and Suffix Search](https://leetcode.com/problems/prefix-and-suffix-search/) |  | — |

---

<sub>Auto-generated — edit karne ke bajaye `python3 scripts/generate_patterns.py` dobara chalao. Status `LEETCODE : N` header comment se match hota hai.</sub>
