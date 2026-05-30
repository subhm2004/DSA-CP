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

**Tip:** README side mein rakho, **Code** column mein `Open →` pe click karo — file editor mein khul jayegi. (Cursor / VS Code: `Cmd+Click` Mac pe, `Ctrl+Click` Windows pe)

---

## Quick Start

```bash
# Clone the repository
git clone https://github.com/subhm2004/DSA.git
cd DSA

# Compile and run any file (example)
g++ -std=c++17 Graphs/Dijkstra_algo.cpp -o dijkstra && ./dijkstra

```

**Requirements:** C++ compiler (`g++` / `clang++`), C++11 or later recommended.

**Example file:** [Graphs/Dijkstra_algo.cpp](./Graphs/Dijkstra_algo.cpp) · [Open Code →](./Graphs/Dijkstra_algo.cpp)

---

## Repository Layout

| Folder | Description | Open |
|--------|-------------|------|
| [arrays.cpp/](./arrays.cpp/) | Array problems & 2D matrix operations | [Browse →](./arrays.cpp/) |
| [basic DSA.cpp/](./basic%20DSA.cpp/) | Beginner DSA — sorting, strings, basics | [Browse →](./basic%20DSA.cpp/) |
| [basicmaths.cpp/](./basicmaths.cpp/) | Number theory — primes, GCD, sieve | [Browse →](./basicmaths.cpp/) |
| [basicpattern.cpp/](./basicpattern.cpp/) | Pattern printing problems | [Browse →](./basicpattern.cpp/) |
| [binarysearch.cpp/](./binarysearch.cpp/) | Binary search variants & problems | [Browse →](./binarysearch.cpp/) |
| [BST.cpp/](./BST.cpp/) | Binary Search Tree operations | [Browse →](./BST.cpp/) |
| [chararray.cpp/](./chararray.cpp/) | C-style char array basics | [Browse →](./chararray.cpp/) |
| [CP_Algorithms/](./CP_Algorithms/) | Competitive programming math & theorems | [Browse →](./CP_Algorithms/) |
| [DSA.cpp/](./DSA.cpp/) | Mixed DSA practice | [Browse →](./DSA.cpp/) |
| [Graphs/](./Graphs/) | Graph algorithms (65+ files) | [Browse →](./Graphs/) |
| [Greedy/](./Greedy/) | Greedy algorithms | [Browse →](./Greedy/) |
| [heaps.cpp/](./heaps.cpp/) | Heap data structure & problems | [Browse →](./heaps.cpp/) |
| [linkedlist.cpp/](./linkedlist.cpp/) | Linked list operations | [Browse →](./linkedlist.cpp/) |
| [OOP's.cpp/](./OOP's.cpp/) | Object-Oriented Programming in C++ | [Browse →](./OOP's.cpp/) |
| [queues.cpp/](./queues.cpp/) | Queue, Deque, circular queue | [Browse →](./queues.cpp/) |
| [recursion.cpp/](./recursion.cpp/) | Recursion & backtracking | [Browse →](./recursion.cpp/) |
| [segment_tree/](./segment_tree/) | Segment tree, Fenwick tree, Mo's algo | [Browse →](./segment_tree/) |
| [stacks.cpp/](./stacks.cpp/) | Stack problems & monotonic stack | [Browse →](./stacks.cpp/) |
| [strings.cpp/](./strings.cpp/) | String manipulation | [Browse →](./strings.cpp/) |
| [trees.cpp/](./trees.cpp/) | Binary tree traversals & problems | [Browse →](./trees.cpp/) |
| [vector.cpp/](./vector.cpp/) | STL vector usage | [Browse →](./vector.cpp/) |
| Root `*.cpp` files | Standalone advanced topic files | [See Index ↓](#index--root-level-files) |

---

## Index — Root Level Files

Standalone implementations at the repository root, grouped by topic.

### String Algorithms & Hashing

| File | Description | Code |
|------|-------------|------|
| [KMP_string_matching_algo.cpp](./KMP_string_matching_algo.cpp) | KMP pattern matching algorithm | [Open →](./KMP_string_matching_algo.cpp) |
| [Z_algorithm_string_matching.cpp](./Z_algorithm_string_matching.cpp) | Z-algorithm for string matching | [Open →](./Z_algorithm_string_matching.cpp) |
| [Rabin_karp_single_hashing_string_matching.cpp](./Rabin_karp_single_hashing_string_matching.cpp) | Rabin-Karp with single hash | [Open →](./Rabin_karp_single_hashing_string_matching.cpp) |
| [Rabin_karp_double_hashing_String_matching.cpp](./Rabin_karp_double_hashing_String_matching.cpp) | Rabin-Karp with double hashing | [Open →](./Rabin_karp_double_hashing_String_matching.cpp) |
| [Rabin_karp_double_hashing_multiple_occurences.cpp](./Rabin_karp_double_hashing_multiple_occurences.cpp) | Rabin-Karp — multiple occurrences | [Open →](./Rabin_karp_double_hashing_multiple_occurences.cpp) |
| [Rabin_karp_dynamic_window_size.cpp](./Rabin_karp_dynamic_window_size.cpp) | Rabin-Karp with dynamic window | [Open →](./Rabin_karp_dynamic_window_size.cpp) |
| [Rolling_hash_dynamic_window_Size.cpp](./Rolling_hash_dynamic_window_Size.cpp) | Rolling hash with dynamic window | [Open →](./Rolling_hash_dynamic_window_Size.cpp) |
| [Rolling_hash_palindrom_check.cpp](./Rolling_hash_palindrom_check.cpp) | Palindrome check via rolling hash | [Open →](./Rolling_hash_palindrom_check.cpp) |
| [dynamic_rolling_hash_of_a_sub_String.cpp](./dynamic_rolling_hash_of_a_sub_String.cpp) | Dynamic rolling hash for substrings | [Open →](./dynamic_rolling_hash_of_a_sub_String.cpp) |
| [generate_palindromes.cpp](./generate_palindromes.cpp) | Generate palindromes | [Open →](./generate_palindromes.cpp) |

### Range Queries & Data Structures

| File | Description | Code |
|------|-------------|------|
| [Fenwick_tree.cpp](./Fenwick_tree.cpp) | Fenwick tree (Binary Indexed Tree) | [Open →](./Fenwick_tree.cpp) |
| [lazy_propogation.cpp](./lazy_propogation.cpp) | Lazy propagation on segment tree | [Open →](./lazy_propogation.cpp) |
| [Mo_s_algorithm_distinct_element_in_range_query.cpp](./Mo_s_algorithm_distinct_element_in_range_query.cpp) | Mo's algorithm — distinct elements in range | [Open →](./Mo_s_algorithm_distinct_element_in_range_query.cpp) |
| [Mos_algo_range_query_sum.cpp](./Mos_algo_range_query_sum.cpp) | Mo's algorithm — range sum query | [Open →](./Mos_algo_range_query_sum.cpp) |
| [Mos_algo_with_update.cpp](./Mos_algo_with_update.cpp) | Mo's algorithm with point updates | [Open →](./Mos_algo_with_update.cpp) |
| [prefix_sum_2D_array.cpp](./prefix_sum_2D_array.cpp) | 2D prefix sum | [Open →](./prefix_sum_2D_array.cpp) |
| [coordinate_compression](./coordinate_compression) | Coordinate compression (binary) | [Open →](./coordinate_compression) |

### Trees & Graphs (Advanced)

| File | Description | Code |
|------|-------------|------|
| [Euler_tour_on_trees.cpp](./Euler_tour_on_trees.cpp) | Euler tour technique on trees | [Open →](./Euler_tour_on_trees.cpp) |
| [euler.cpp](./euler.cpp) | Euler-related implementation | [Open →](./euler.cpp) |
| [Hierholzers_algorithm.cpp](./Hierholzers_algorithm.cpp) | Hierholzer's algorithm for Euler path/circuit | [Open →](./Hierholzers_algorithm.cpp) |
| [lca_some_Adv_functions.cpp](./lca_some_Adv_functions.cpp) | LCA — advanced helper functions | [Open →](./lca_some_Adv_functions.cpp) |
| [convex_hull.cpp](./convex_hull.cpp) | Convex hull (computational geometry) | [Open →](./convex_hull.cpp) |

### Math, Number Theory & Combinatorics

| File | Description | Code |
|------|-------------|------|
| [Base_n.cpp](./Base_n.cpp) | Base-N number conversion | [Open →](./Base_n.cpp) |
| [binay_expo.cpp](./binay_expo.cpp) | Binary exponentiation | [Open →](./binay_expo.cpp) |
| [matrix_expo.cpp](./matrix_expo.cpp) | Matrix exponentiation | [Open →](./matrix_expo.cpp) |
| [newton_raphson_method.cpp](./newton_raphson_method.cpp) | Newton-Raphson method | [Open →](./newton_raphson_method.cpp) |
| [Kth_root_of_a_number_newton_rapson.cpp](./Kth_root_of_a_number_newton_rapson.cpp) | Kth root via Newton-Raphson | [Open →](./Kth_root_of_a_number_newton_rapson.cpp) |
| [derrangement_combinotrics.cpp](./derrangement_combinotrics.cpp) | Derangements & combinatorics | [Open →](./derrangement_combinotrics.cpp) |
| [BitsQuestion2.cpp](./BitsQuestion2.cpp) | Bit manipulation problems | [Open →](./BitsQuestion2.cpp) |
| [Tower_of_hanoi.cpp](./Tower_of_hanoi.cpp) | Tower of Hanoi | [Open →](./Tower_of_hanoi.cpp) |

### Dynamic Programming & Sorting

| File | Description | Code |
|------|-------------|------|
| [lis_dp.cpp](./lis_dp.cpp) | Longest Increasing Subsequence (DP) | [Open →](./lis_dp.cpp) |
| [merge_Sort.cpp](./merge_Sort.cpp) | Merge sort | [Open →](./merge_Sort.cpp) |
| [sorting.cpp](./sorting.cpp) | Sorting algorithms | [Open →](./sorting.cpp) |

### Misc / Practice

| File | Description | Code |
|------|-------------|------|
| [basicpractice.cpp](./basicpractice.cpp) | General practice | [Open →](./basicpractice.cpp) |
| [practice1.cpp](./practice1.cpp) | Practice problems | [Open →](./practice1.cpp) |
| [loops.cpp](./loops.cpp) | Loop basics | [Open →](./loops.cpp) |
| [queuebasics.cpp](./queuebasics.cpp) | Queue basics | [Open →](./queuebasics.cpp) |
| [stack.cpp](./stack.cpp) | Stack basics | [Open →](./stack.cpp) |

---

## Index — Folder-wise

### `arrays.cpp/`

Array fundamentals, 2D arrays, and classic array problems.

| File | Topic | Code |
|------|-------|------|
| [array1.cpp](./arrays.cpp/array1.cpp) – [array4.cpp](./arrays.cpp/array4.cpp) | Basic array operations | [Open →](./arrays.cpp/array1.cpp) · [Open →](./arrays.cpp/array4.cpp) |
| [2darray.cpp](./arrays.cpp/2darray.cpp), [2Darraylec2.cpp](./arrays.cpp/2Darraylec2.cpp), [2Darraylec3.cpp](./arrays.cpp/2Darraylec3.cpp) | 2D array basics | [Open →](./arrays.cpp/2darray.cpp) · [Open →](./arrays.cpp/2Darraylec2.cpp) · [Open →](./arrays.cpp/2Darraylec3.cpp) |
| [linearsearch.cpp](./arrays.cpp/linearsearch.cpp), [binarysearch.cpp](./arrays.cpp/binarysearch.cpp) | Search in arrays | [Open →](./arrays.cpp/linearsearch.cpp) · [Open →](./arrays.cpp/binarysearch.cpp) |
| [twosum.cpp](./arrays.cpp/twosum.cpp), [printpairs.cpp](./arrays.cpp/printpairs.cpp) | Pair sum problems | [Open →](./arrays.cpp/twosum.cpp) · [Open →](./arrays.cpp/printpairs.cpp) |
| [reverse.cpp](./arrays.cpp/reverse.cpp), [rotatearray.cpp](./arrays.cpp/rotatearray.cpp), [shiftone.cpp](./arrays.cpp/shiftone.cpp) | Array rotation & reversal | [Open →](./arrays.cpp/reverse.cpp) · [Open →](./arrays.cpp/rotatearray.cpp) · [Open →](./arrays.cpp/shiftone.cpp) |
| [rotatematrix.cpp](./arrays.cpp/rotatematrix.cpp), [transposematrix.cpp](./arrays.cpp/transposematrix.cpp) | Matrix operations | [Open →](./arrays.cpp/rotatematrix.cpp) · [Open →](./arrays.cpp/transposematrix.cpp) |
| [duplicateno.cpp](./arrays.cpp/duplicateno.cpp), [uniqueoccur.cpp](./arrays.cpp/uniqueoccur.cpp), [firstoccur.cpp](./arrays.cpp/firstoccur.cpp) | Frequency & duplicates | [Open →](./arrays.cpp/duplicateno.cpp) · [Open →](./arrays.cpp/uniqueoccur.cpp) · [Open →](./arrays.cpp/firstoccur.cpp) |
| [dutchnationalflag.cpp](./arrays.cpp/dutchnationalflag.cpp), [sortcolors.cpp](./arrays.cpp/sortcolors.cpp), [sortnegatives.cpp](./arrays.cpp/sortnegatives.cpp), [sortinarray.cpp](./arrays.cpp/sortinarray.cpp) | Sorting/partitioning arrays | [Open →](./arrays.cpp/dutchnationalflag.cpp) · [Open →](./arrays.cpp/sortcolors.cpp) · [Open →](./arrays.cpp/sortnegatives.cpp) · [Open →](./arrays.cpp/sortinarray.cpp) |
| [pivotindex.cpp](./arrays.cpp/pivotindex.cpp), [maximumones.cpp](./arrays.cpp/maximumones.cpp), [rearrange+and-.cpp](./arrays.cpp/rearrange+and-.cpp), [alterswap.cpp](./arrays.cpp/alterswap.cpp) | Rearrangement problems | [Open →](./arrays.cpp/pivotindex.cpp) · [Open →](./arrays.cpp/maximumones.cpp) · [Open →](./arrays.cpp/rearrange+and-.cpp) · [Open →](./arrays.cpp/alterswap.cpp) |
| [extremeprint.cpp](./arrays.cpp/extremeprint.cpp) | Print extremes | [Open →](./arrays.cpp/extremeprint.cpp) |
| [arraypractice1.cpp](./arrays.cpp/arraypractice1.cpp), [arraypractice2.cpp](./arrays.cpp/arraypractice2.cpp), [practice1.cpp](./arrays.cpp/practice1.cpp) | Practice problems | [Open →](./arrays.cpp/arraypractice1.cpp) · [Open →](./arrays.cpp/arraypractice2.cpp) · [Open →](./arrays.cpp/practice1.cpp) |

---

### `basic DSA.cpp/`

Beginner-level DSA — good starting point for newcomers.

| File | Topic | Code |
|------|-------|------|
| [basicDSA.cpp](./basic DSA.cpp/basicDSA.cpp) | Core DSA basics | [Open →](./basic DSA.cpp/basicDSA.cpp) |
| [practiceDSA.cpp](./basic DSA.cpp/practiceDSA.cpp), [practiceDSA1.cpp](./basic DSA.cpp/practiceDSA1.cpp), [practice1.cpp](./basic DSA.cpp/practice1.cpp) | Practice | [Open →](./basic DSA.cpp/practiceDSA.cpp) · [Open →](./basic DSA.cpp/practiceDSA1.cpp) · [Open →](./basic DSA.cpp/practice1.cpp) |
| [insertionsort.cpp](./basic DSA.cpp/insertionsort.cpp), [selectionsort.cpp](./basic DSA.cpp/selectionsort.cpp), [sort2.cpp](./basic DSA.cpp/sort2.cpp), [sorting3.cpp](./basic DSA.cpp/sorting3.cpp) | Sorting algorithms | [Open →](./basic DSA.cpp/insertionsort.cpp) · [Open →](./basic DSA.cpp/selectionsort.cpp) · [Open →](./basic DSA.cpp/sort2.cpp) · [Open →](./basic DSA.cpp/sorting3.cpp) |
| [palindrome.cpp](./basic DSA.cpp/palindrome.cpp), [reversestring.cpp](./basic DSA.cpp/reversestring.cpp), [replacestring.cpp](./basic DSA.cpp/replacestring.cpp) | String basics | [Open →](./basic DSA.cpp/palindrome.cpp) · [Open →](./basic DSA.cpp/reversestring.cpp) · [Open →](./basic DSA.cpp/replacestring.cpp) |
| [uppercase.cpp](./basic DSA.cpp/uppercase.cpp), [lowercase.cpp](./basic DSA.cpp/lowercase.cpp) | Character conversion | [Open →](./basic DSA.cpp/uppercase.cpp) · [Open →](./basic DSA.cpp/lowercase.cpp) |
| [oddoccurnce.cpp](./basic DSA.cpp/oddoccurnce.cpp), [binaryquotient.cpp](./basic DSA.cpp/binaryquotient.cpp) | Bit/count problems | [Open →](./basic DSA.cpp/oddoccurnce.cpp) · [Open →](./basic DSA.cpp/binaryquotient.cpp) |
| [sqrt.cpp](./basic DSA.cpp/sqrt.cpp) | Square root | [Open →](./basic DSA.cpp/sqrt.cpp) |

---

### `basicmaths.cpp/`

Number theory and mathematical foundations.

| File | Topic | Code |
|------|-------|------|
| [gcd.cpp](./basicmaths.cpp/gcd.cpp) | GCD / Euclidean algorithm | [Open →](./basicmaths.cpp/gcd.cpp) |
| [primenumber.cpp](./basicmaths.cpp/primenumber.cpp), [prime2.cpp](./basicmaths.cpp/prime2.cpp) | Prime checking | [Open →](./basicmaths.cpp/primenumber.cpp) · [Open →](./basicmaths.cpp/prime2.cpp) |
| [seieve.cpp](./basicmaths.cpp/seieve.cpp), [segmented_seieve.cpp](./basicmaths.cpp/segmented_seieve.cpp) | Sieve of Eratosthenes (normal & segmented) | [Open →](./basicmaths.cpp/seieve.cpp) · [Open →](./basicmaths.cpp/segmented_seieve.cpp) |
| [exponentiation.cpp](./basicmaths.cpp/exponentiation.cpp) | Fast exponentiation | [Open →](./basicmaths.cpp/exponentiation.cpp) |
| [practicebasics.cpp](./basicmaths.cpp/practicebasics.cpp) | Math practice | [Open →](./basicmaths.cpp/practicebasics.cpp) |

---

### `basicpattern.cpp/`

Pattern printing — useful for building loop logic.

| File | Pattern | Code |
|------|---------|------|
| [halfpyramid.cpp](./basicpattern.cpp/halfpyramid.cpp), [fullpyramids.cpp](./basicpattern.cpp/fullpyramids.cpp) | Half & full pyramids | [Open →](./basicpattern.cpp/halfpyramid.cpp) · [Open →](./basicpattern.cpp/fullpyramids.cpp) |
| [hollowpyramid.cpp](./basicpattern.cpp/hollowpyramid.cpp), [hollowrectangular.cpp](./basicpattern.cpp/hollowrectangular.cpp) | Hollow patterns | [Open →](./basicpattern.cpp/hollowpyramid.cpp) · [Open →](./basicpattern.cpp/hollowrectangular.cpp) |
| [invertedhalfpyramid.cpp](./basicpattern.cpp/invertedhalfpyramid.cpp), [invertedpyramid.cpp](./basicpattern.cpp/invertedpyramid.cpp) | Inverted pyramids | [Open →](./basicpattern.cpp/invertedhalfpyramid.cpp) · [Open →](./basicpattern.cpp/invertedpyramid.cpp) |
| [numeric.cpp](./basicpattern.cpp/numeric.cpp), [numericpyramid.cpp](./basicpattern.cpp/numericpyramid.cpp), [numerichollow.cpp](./basicpattern.cpp/numerichollow.cpp) | Numeric patterns | [Open →](./basicpattern.cpp/numeric.cpp) · [Open →](./basicpattern.cpp/numericpyramid.cpp) · [Open →](./basicpattern.cpp/numerichollow.cpp) |
| [squarepattern.cpp](./basicpattern.cpp/squarepattern.cpp), [soliddiamond.cpp](./basicpattern.cpp/soliddiamond.cpp) | Square & diamond | [Open →](./basicpattern.cpp/squarepattern.cpp) · [Open →](./basicpattern.cpp/soliddiamond.cpp) |
| [practice1.cpp](./basicpattern.cpp/practice1.cpp), [practice2.cpp](./basicpattern.cpp/practice2.cpp), [practice3.cpp](./basicpattern.cpp/practice3.cpp) | Practice | [Open →](./basicpattern.cpp/practice1.cpp) · [Open →](./basicpattern.cpp/practice2.cpp) · [Open →](./basicpattern.cpp/practice3.cpp) |

---

### `binarysearch.cpp/`

Binary search templates and classic BS problems.

| File | Problem / Concept | Code |
|------|-------------------|------|
| [practicebs.cpp](./binarysearch.cpp/practicebs.cpp) | BS practice | [Open →](./binarysearch.cpp/practicebs.cpp) |
| [peakelement.cpp](./binarysearch.cpp/peakelement.cpp), [pivotelement.cpp](./binarysearch.cpp/pivotelement.cpp) | Peak / pivot element | [Open →](./binarysearch.cpp/peakelement.cpp) · [Open →](./binarysearch.cpp/pivotelement.cpp) |
| [sqrt.cpp](./binarysearch.cpp/sqrt.cpp), [findquotient.cpp](./binarysearch.cpp/findquotient.cpp) | Square root & division via BS | [Open →](./binarysearch.cpp/sqrt.cpp) · [Open →](./binarysearch.cpp/findquotient.cpp) |
| [oddocc.cpp](./binarysearch.cpp/oddocc.cpp), [totalocc.cpp](./binarysearch.cpp/totalocc.cpp), [missingelement.cpp](./binarysearch.cpp/missingelement.cpp) | Occurrence & missing element | [Open →](./binarysearch.cpp/oddocc.cpp) · [Open →](./binarysearch.cpp/totalocc.cpp) · [Open →](./binarysearch.cpp/missingelement.cpp) |
| [2dmatrixsearch.cpp](./binarysearch.cpp/2dmatrixsearch.cpp) | Search in 2D matrix | [Open →](./binarysearch.cpp/2dmatrixsearch.cpp) |
| [aggressivecow.cpp](./binarysearch.cpp/aggressivecow.cpp), [bookalloc.cpp](./binarysearch.cpp/bookalloc.cpp), [painterpartition.cpp](./binarysearch.cpp/painterpartition.cpp) | Allocation problems | [Open →](./binarysearch.cpp/aggressivecow.cpp) · [Open →](./binarysearch.cpp/bookalloc.cpp) · [Open →](./binarysearch.cpp/painterpartition.cpp) |
| [ekospoj.cpp](./binarysearch.cpp/ekospoj.cpp), [prataspoj.cpp](./binarysearch.cpp/prataspoj.cpp) | SPOJ problems | [Open →](./binarysearch.cpp/ekospoj.cpp) · [Open →](./binarysearch.cpp/prataspoj.cpp) |
| [kclosestelements.cpp](./binarysearch.cpp/kclosestelements.cpp), [kdiffpairs.cpp](./binarysearch.cpp/kdiffpairs.cpp) | K-closest & K-diff pairs | [Open →](./binarysearch.cpp/kclosestelements.cpp) · [Open →](./binarysearch.cpp/kdiffpairs.cpp) |
| [nearlysorted.cpp](./binarysearch.cpp/nearlysorted.cpp), [unboundedbs.cpp](./binarysearch.cpp/unboundedbs.cpp) | Variants | [Open →](./binarysearch.cpp/nearlysorted.cpp) · [Open →](./binarysearch.cpp/unboundedbs.cpp) |
| [exponentialsearch.cpp](./binarysearch.cpp/exponentialsearch.cpp) | Exponential search | [Open →](./binarysearch.cpp/exponentialsearch.cpp) |

---

### `BST.cpp/`

Binary Search Tree — creation, traversal, conversion, and problems.

| File | Topic | Code |
|------|-------|------|
| [creationBST.cpp](./BST.cpp/creationBST.cpp), [inorderBSTcreate.cpp](./BST.cpp/inorderBSTcreate.cpp) | BST creation | [Open →](./BST.cpp/creationBST.cpp) · [Open →](./BST.cpp/inorderBSTcreate.cpp) |
| [inorderBST.cpp](./BST.cpp/inorderBST.cpp), [searchBST.cpp](./BST.cpp/searchBST.cpp), [deletionBST.cpp](./BST.cpp/deletionBST.cpp) | Traversal, search, delete | [Open →](./BST.cpp/inorderBST.cpp) · [Open →](./BST.cpp/searchBST.cpp) · [Open →](./BST.cpp/deletionBST.cpp) |
| [LCAinBST.cpp](./BST.cpp/LCAinBST.cpp), [twosumBST.cpp](./BST.cpp/twosumBST.cpp) | LCA & two-sum in BST | [Open →](./BST.cpp/LCAinBST.cpp) · [Open →](./BST.cpp/twosumBST.cpp) |
| [largestBST.cpp](./BST.cpp/largestBST.cpp) | Largest BST in a binary tree | [Open →](./BST.cpp/largestBST.cpp) |
| [BSTtoDLL.cpp](./BST.cpp/BSTtoDLL.cpp), [bsttodllcreate.cpp](./BST.cpp/bsttodllcreate.cpp), [dlltobstcreate.cpp](./BST.cpp/dlltobstcreate.cpp) | BST ↔ Doubly Linked List conversion | [Open →](./BST.cpp/BSTtoDLL.cpp) · [Open →](./BST.cpp/bsttodllcreate.cpp) · [Open →](./BST.cpp/dlltobstcreate.cpp) |
| [practicetree.cpp](./BST.cpp/practicetree.cpp) | BST practice | [Open →](./BST.cpp/practicetree.cpp) |

---

### `chararray.cpp/`

| File | Topic | Code |
|------|-------|------|
| [basicsofchararray.cpp](./chararray.cpp/basicsofchararray.cpp) | Char array fundamentals | [Open →](./chararray.cpp/basicsofchararray.cpp) |
| [checkpallindrome.cpp](./chararray.cpp/checkpallindrome.cpp) | Palindrome check | [Open →](./chararray.cpp/checkpallindrome.cpp) |

---

### `CP_Algorithms/`

Competitive programming math and classic theorems.

| File | Topic | Code |
|------|-------|------|
| [Kadanes_algo.cpp](./CP_Algorithms/Kadanes_algo.cpp) | Kadane's maximum subarray | [Open →](./CP_Algorithms/Kadanes_algo.cpp) |
| [Eulers_totient_function.cpp](./CP_Algorithms/Eulers_totient_function.cpp) | Euler's totient φ(n) | [Open →](./CP_Algorithms/Eulers_totient_function.cpp) |
| [euler_theorem.cpp](./CP_Algorithms/euler_theorem.cpp) | Euler's theorem | [Open →](./CP_Algorithms/euler_theorem.cpp) |
| [number_and_sum_of_divisors.cpp](./CP_Algorithms/number_and_sum_of_divisors.cpp) | Divisors count & sum | [Open →](./CP_Algorithms/number_and_sum_of_divisors.cpp) |
| [Handshaking_Theorem.cpp](./CP_Algorithms/Handshaking_Theorem.cpp) | Handshaking lemma (graph theory) | [Open →](./CP_Algorithms/Handshaking_Theorem.cpp) |
| [rank_of_a_matrix.cpp](./CP_Algorithms/rank_of_a_matrix.cpp) | Matrix rank | [Open →](./CP_Algorithms/rank_of_a_matrix.cpp) |
| [kth_ancestor_of_a_tree.cpp](./CP_Algorithms/kth_ancestor_of_a_tree.cpp) | Kth ancestor on tree | [Open →](./CP_Algorithms/kth_ancestor_of_a_tree.cpp) |
| [hanoi.cpp](./CP_Algorithms/hanoi.cpp) | Tower of Hanoi | [Open →](./CP_Algorithms/hanoi.cpp) |

---

### `DSA.cpp/`

Mixed DSA implementations.

| File | Topic | Code |
|------|-------|------|
| [arraysques.cpp](./DSA.cpp/arraysques.cpp) | Array questions | [Open →](./DSA.cpp/arraysques.cpp) |
| [dynamic2D.cpp](./DSA.cpp/dynamic2D.cpp) | Dynamic 2D arrays | [Open →](./DSA.cpp/dynamic2D.cpp) |
| [mergearray.cpp](./DSA.cpp/mergearray.cpp) | Merge two arrays | [Open →](./DSA.cpp/mergearray.cpp) |
| [mergesort.cpp](./DSA.cpp/mergesort.cpp), [quicksort.cpp](./DSA.cpp/quicksort.cpp) | Sorting | [Open →](./DSA.cpp/mergesort.cpp) · [Open →](./DSA.cpp/quicksort.cpp) |

---

### `Graphs/`

The largest folder — **65 graph algorithm implementations**, organized below by category.

#### Traversal (BFS / DFS)

| File | Topic | Code |
|------|-------|------|
| [bfs_dfs.cpp](./Graphs/bfs_dfs.cpp) | BFS & DFS combined | [Open →](./Graphs/bfs_dfs.cpp) |
| [multi_source_bfs.cpp](./Graphs/multi_source_bfs.cpp) | Multi-source BFS | [Open →](./Graphs/multi_source_bfs.cpp) |
| [shortest_distance_dfs.cpp](./Graphs/shortest_distance_dfs.cpp) | Shortest path via DFS | [Open →](./Graphs/shortest_distance_dfs.cpp) |
| [rotten_oranges.cpp](./Graphs/rotten_oranges.cpp) | Multi-source BFS (rotten oranges) | [Open →](./Graphs/rotten_oranges.cpp) |
| [all_path_from_source_to_target.cpp](./Graphs/all_path_from_source_to_target.cpp) | All paths (BFS) | [Open →](./Graphs/all_path_from_source_to_target.cpp) |
| [all_path_from_source_to_target_dfs.cpp](./Graphs/all_path_from_source_to_target_dfs.cpp) | All paths (DFS) | [Open →](./Graphs/all_path_from_source_to_target_dfs.cpp) |

#### Shortest Path

| File | Topic | Code |
|------|-------|------|
| [Dijkstra_algo.cpp](./Graphs/Dijkstra_algo.cpp), [Dijkstra_path.cpp](./Graphs/Dijkstra_path.cpp) | Dijkstra's algorithm | [Open →](./Graphs/Dijkstra_algo.cpp) · [Open →](./Graphs/Dijkstra_path.cpp) |
| [bellmann_ford_algorithm.cpp](./Graphs/bellmann_ford_algorithm.cpp) | Bellman-Ford | [Open →](./Graphs/bellmann_ford_algorithm.cpp) |
| [floyd_warshall_algorithm.cpp](./Graphs/floyd_warshall_algorithm.cpp) | Floyd-Warshall (all pairs) | [Open →](./Graphs/floyd_warshall_algorithm.cpp) |
| [a_star.cpp](./Graphs/a_star.cpp) | A* search algorithm | [Open →](./Graphs/a_star.cpp) |

#### Minimum Spanning Tree (MST)

| File | Topic | Code |
|------|-------|------|
| [Prims_algorithm.cpp](./Graphs/Prims_algorithm.cpp), [print_prims.cpp](./Graphs/print_prims.cpp) | Prim's algorithm | [Open →](./Graphs/Prims_algorithm.cpp) · [Open →](./Graphs/print_prims.cpp) |
| [Krushkal_algorithm.cpp](./Graphs/Krushkal_algorithm.cpp), [printing_mst_krushkal_algo.cpp](./Graphs/printing_mst_krushkal_algo.cpp) | Kruskal's algorithm | [Open →](./Graphs/Krushkal_algorithm.cpp) · [Open →](./Graphs/printing_mst_krushkal_algo.cpp) |

#### Union-Find / DSU

| File | Topic | Code |
|------|-------|------|
| [DSU.cpp](./Graphs/DSU.cpp), [Union_find.cpp](./Graphs/Union_find.cpp) | Disjoint Set Union | [Open →](./Graphs/DSU.cpp) · [Open →](./Graphs/Union_find.cpp) |
| [connected_components_DSU.cpp](./Graphs/connected_components_DSU.cpp) | Connected components via DSU | [Open →](./Graphs/connected_components_DSU.cpp) |
| [cycle_detection_using_DSU.cpp](./Graphs/cycle_detection_using_DSU.cpp) | Cycle detection with DSU | [Open →](./Graphs/cycle_detection_using_DSU.cpp) |
| [dsu_bipartite_graph.cpp](./Graphs/dsu_bipartite_graph.cpp), [bipetrate_graph_union_find.cpp](./Graphs/bipetrate_graph_union_find.cpp) | Bipartite check via DSU | [Open →](./Graphs/dsu_bipartite_graph.cpp) · [Open →](./Graphs/bipetrate_graph_union_find.cpp) |

#### LCA & Binary Lifting

| File | Topic | Code |
|------|-------|------|
| [binary_lifting.cpp](./Graphs/binary_lifting.cpp) | Binary lifting template | [Open →](./Graphs/binary_lifting.cpp) |
| [LCA_Binary_lifting_kth_ancestor.cpp](./Graphs/LCA_Binary_lifting_kth_ancestor.cpp) | LCA & Kth ancestor | [Open →](./Graphs/LCA_Binary_lifting_kth_ancestor.cpp) |

#### Tree Algorithms

| File | Topic | Code |
|------|-------|------|
| [center_of_a_tree.cpp](./Graphs/center_of_a_tree.cpp) | Tree center | [Open →](./Graphs/center_of_a_tree.cpp) |
| [diameter_of_a_tree.cpp](./Graphs/diameter_of_a_tree.cpp), [diameter_of_a_tree_bfs.cpp](./Graphs/diameter_of_a_tree_bfs.cpp), [diameter_of_tree_1.cpp](./Graphs/diameter_of_tree_1.cpp) | Tree diameter | [Open →](./Graphs/diameter_of_a_tree.cpp) · [Open →](./Graphs/diameter_of_a_tree_bfs.cpp) · [Open →](./Graphs/diameter_of_tree_1.cpp) |
| [two_nodes_on_same_path_of_graph.cpp](./Graphs/two_nodes_on_same_path_of_graph.cpp) | Same path check | [Open →](./Graphs/two_nodes_on_same_path_of_graph.cpp) |

#### Topological Sort & DAG

| File | Topic | Code |
|------|-------|------|
| [topological_sort.cpp](./Graphs/topological_sort.cpp), [kahns_algo.cpp](./Graphs/kahns_algo.cpp) | Topological sort (Kahn's) | [Open →](./Graphs/topological_sort.cpp) · [Open →](./Graphs/kahns_algo.cpp) |
| [all_ancestors_of_a_node_in_DAG.cpp](./Graphs/all_ancestors_of_a_node_in_DAG.cpp) | All ancestors in DAG | [Open →](./Graphs/all_ancestors_of_a_node_in_DAG.cpp) |

#### Cycle Detection

| File | Topic | Code |
|------|-------|------|
| [cycle_detection.cpp](./Graphs/cycle_detection.cpp) | General cycle detection | [Open →](./Graphs/cycle_detection.cpp) |
| [Cycle_detection_color_method.cpp](./Graphs/Cycle_detection_color_method.cpp) | Cycle detection (coloring) | [Open →](./Graphs/Cycle_detection_color_method.cpp) |

#### Euler Path / Circuit

| File | Topic | Code |
|------|-------|------|
| [Hierholzers_algorithm.cpp](./Graphs/Hierholzers_algorithm.cpp) | Hierholzer's algorithm | [Open →](./Graphs/Hierholzers_algorithm.cpp) |
| [Printing_euler_path_undirected.cpp](./Graphs/Printing_euler_path_undirected.cpp) | Print Euler path (undirected) | [Open →](./Graphs/Printing_euler_path_undirected.cpp) |
| [directed_eulerian_path.cpp](./Graphs/directed_eulerian_path.cpp) | Directed Eulerian path | [Open →](./Graphs/directed_eulerian_path.cpp) |
| [euler_path_directed_indegree.cpp](./Graphs/euler_path_directed_indegree.cpp), [euler_path_undirected_degree.cpp](./Graphs/euler_path_undirected_degree.cpp) | Degree conditions | [Open →](./Graphs/euler_path_directed_indegree.cpp) · [Open →](./Graphs/euler_path_undirected_degree.cpp) |

#### Strongly Connected Components & Articulation

| File | Topic | Code |
|------|-------|------|
| [tarjans_algo.cpp](./Graphs/tarjans_algo.cpp), [kosaraju_algorithm.cpp](./Graphs/kosaraju_algorithm.cpp) | SCC algorithms | [Open →](./Graphs/tarjans_algo.cpp) · [Open →](./Graphs/kosaraju_algorithm.cpp) |
| [Articulation_point.cpp](./Graphs/Articulation_point.cpp) | Articulation points | [Open →](./Graphs/Articulation_point.cpp) |

#### Bipartite & Graph Coloring

| File | Topic | Code |
|------|-------|------|
| [Bipetrate_graph_bfs_se.cpp](./Graphs/Bipetrate_graph_bfs_se.cpp), [Bipetrate_graph_dfs_se.cpp](./Graphs/Bipetrate_graph_dfs_se.cpp) | Bipartite check (BFS/DFS) | [Open →](./Graphs/Bipetrate_graph_bfs_se.cpp) · [Open →](./Graphs/Bipetrate_graph_dfs_se.cpp) |
| [graph_coloring.cpp](./Graphs/graph_coloring.cpp), [chromatic_number.cpp](./Graphs/chromatic_number.cpp) | Graph coloring | [Open →](./Graphs/graph_coloring.cpp) · [Open →](./Graphs/chromatic_number.cpp) |

#### Network Flow

| File | Topic | Code |
|------|-------|------|
| [Maximum_flow_ford_fulkerson.cpp](./Graphs/Maximum_flow_ford_fulkerson.cpp) | Ford-Fulkerson max flow | [Open →](./Graphs/Maximum_flow_ford_fulkerson.cpp) |

#### Matrix Exponentiation & Math on Graphs

| File | Topic | Code |
|------|-------|------|
| [matrix_exponentiation.cpp](./Graphs/matrix_exponentiation.cpp) | Matrix exponentiation | [Open →](./Graphs/matrix_exponentiation.cpp) |
| [Fibo_series_using_matrix_exponentiation.cpp](./Graphs/Fibo_series_using_matrix_exponentiation.cpp) | Fibonacci via matrix expo | [Open →](./Graphs/Fibo_series_using_matrix_exponentiation.cpp) |
| [combinotrics.cpp](./Graphs/combinotrics.cpp), [sum_of_subset.cpp](./Graphs/sum_of_subset.cpp) | Combinatorics & subset sum | [Open →](./Graphs/combinotrics.cpp) · [Open →](./Graphs/sum_of_subset.cpp) |
| [kadanes_algo.cpp](./Graphs/kadanes_algo.cpp), [count_inversion.cpp](./Graphs/count_inversion.cpp) | Array algorithms | [Open →](./Graphs/kadanes_algo.cpp) · [Open →](./Graphs/count_inversion.cpp) |
| [segmented_sieve.cpp](./Graphs/segmented_sieve.cpp), [prime_no.cpp](./Graphs/prime_no.cpp) | Prime sieve | [Open →](./Graphs/segmented_sieve.cpp) · [Open →](./Graphs/prime_no.cpp) |

#### Graph Representation & Utilities

| File | Topic | Code |
|------|-------|------|
| [list_to_matrix.cpp](./Graphs/list_to_matrix.cpp), [matrix_to_list.cpp](./Graphs/matrix_to_list.cpp) | Adjacency conversions | [Open →](./Graphs/list_to_matrix.cpp) · [Open →](./Graphs/matrix_to_list.cpp) |
| [reversed_graph.cpp](./Graphs/reversed_graph.cpp) | Reverse a graph | [Open →](./Graphs/reversed_graph.cpp) |
| [Base_N.cpp](./Graphs/Base_N.cpp) | Base-N conversion | [Open →](./Graphs/Base_N.cpp) |
| [Substring_of_a_string.cpp](./Graphs/Substring_of_a_string.cpp), [Sum_of_substring.cpp](./Graphs/Sum_of_substring.cpp) | String on graph context | [Open →](./Graphs/Substring_of_a_string.cpp) · [Open →](./Graphs/Sum_of_substring.cpp) |
| [ray_casting_algorithm.cpp](./Graphs/ray_casting_algorithm.cpp), [winding_number.cpp](./Graphs/winding_number.cpp) | Computational geometry | [Open →](./Graphs/ray_casting_algorithm.cpp) · [Open →](./Graphs/winding_number.cpp) |
| [merge_sortt.cpp](./Graphs/merge_sortt.cpp) | Merge sort | [Open →](./Graphs/merge_sortt.cpp) |

---

### `Greedy/`

| File | Topic | Code |
|------|-------|------|
| [job_sequencing.cpp](./Greedy/job_sequencing.cpp) | Job sequencing with deadlines | [Open →](./Greedy/job_sequencing.cpp) |

---

### `heaps.cpp/`

Heap data structure — min/max heap, heap sort, and heap problems.

| File | Topic | Code |
|------|-------|------|
| [MinHeap.cpp](./heaps.cpp/MinHeap.cpp), [MaxHeap.cpp](./heaps.cpp/MaxHeap.cpp) | Min & max heap implementation | [Open →](./heaps.cpp/MinHeap.cpp) · [Open →](./heaps.cpp/MaxHeap.cpp) |
| [createheap.cpp](./heaps.cpp/createheap.cpp), [buildheap.cpp](./heaps.cpp/buildheap.cpp), [deleteHeap.cpp](./heaps.cpp/deleteHeap.cpp) | Heap operations | [Open →](./heaps.cpp/createheap.cpp) · [Open →](./heaps.cpp/buildheap.cpp) · [Open →](./heaps.cpp/deleteHeap.cpp) |
| [heapsort.cpp](./heaps.cpp/heapsort.cpp) | Heap sort | [Open →](./heaps.cpp/heapsort.cpp) |
| [STLheaps.cpp](./heaps.cpp/STLheaps.cpp) | STL `priority_queue` usage | [Open →](./heaps.cpp/STLheaps.cpp) |
| [IsCBT.cpp](./heaps.cpp/IsCBT.cpp), [ValidHeapfromCBT.cpp](./heaps.cpp/ValidHeapfromCBT.cpp), [checkmaxheap.cpp](./heaps.cpp/checkmaxheap.cpp) | Complete binary tree & heap validation | [Open →](./heaps.cpp/IsCBT.cpp) · [Open →](./heaps.cpp/ValidHeapfromCBT.cpp) · [Open →](./heaps.cpp/checkmaxheap.cpp) |
| [BSTtoMaxHeap.cpp](./heaps.cpp/BSTtoMaxHeap.cpp) | Convert BST to max heap | [Open →](./heaps.cpp/BSTtoMaxHeap.cpp) |
| [kgreatest.cpp](./heaps.cpp/kgreatest.cpp), [findingsmallest.cpp](./heaps.cpp/findingsmallest.cpp) | K greatest / smallest elements | [Open →](./heaps.cpp/kgreatest.cpp) · [Open →](./heaps.cpp/findingsmallest.cpp) |
| [practice.cpp](./heaps.cpp/practice.cpp) | Heap practice | [Open →](./heaps.cpp/practice.cpp) |

---

### `linkedlist.cpp/`

Singly, doubly linked lists and classic LL problems.

| File | Topic | Code |
|------|-------|------|
| [basicsofLL.cpp](./linkedlist.cpp/basicsofLL.cpp), [doublyLL.cpp](./linkedlist.cpp/doublyLL.cpp) | Singly & doubly LL basics | [Open →](./linkedlist.cpp/basicsofLL.cpp) · [Open →](./linkedlist.cpp/doublyLL.cpp) |
| [reversell.cpp](./linkedlist.cpp/reversell.cpp), [kgrpreversal.cpp](./linkedlist.cpp/kgrpreversal.cpp) | Reverse LL (full & K-group) | [Open →](./linkedlist.cpp/reversell.cpp) · [Open →](./linkedlist.cpp/kgrpreversal.cpp) |
| [middleLL.cpp](./linkedlist.cpp/middleLL.cpp), [add2ll.cpp](./linkedlist.cpp/add2ll.cpp), [addone.cpp](./linkedlist.cpp/addone.cpp) | Middle element, add numbers | [Open →](./linkedlist.cpp/middleLL.cpp) · [Open →](./linkedlist.cpp/add2ll.cpp) · [Open →](./linkedlist.cpp/addone.cpp) |
| [deletionLL.cpp](./linkedlist.cpp/deletionLL.cpp), [linkedlistdelete.cpp](./linkedlist.cpp/linkedlistdelete.cpp) | Deletion | [Open →](./linkedlist.cpp/deletionLL.cpp) · [Open →](./linkedlist.cpp/linkedlistdelete.cpp) |
| [pallindromell.cpp](./linkedlist.cpp/pallindromell.cpp) | Palindrome linked list | [Open →](./linkedlist.cpp/pallindromell.cpp) |
| [startofloop.cpp](./linkedlist.cpp/startofloop.cpp), [tortoisealgo.cpp](./linkedlist.cpp/tortoisealgo.cpp) | Cycle detection (Floyd's) | [Open →](./linkedlist.cpp/startofloop.cpp) · [Open →](./linkedlist.cpp/tortoisealgo.cpp) |
| [Binary_lifting_LCA.cpp](./linkedlist.cpp/Binary_lifting_LCA.cpp) | LCA via binary lifting (on LL) | [Open →](./linkedlist.cpp/Binary_lifting_LCA.cpp) |
| [MCM_partition_dp.cpp](./linkedlist.cpp/MCM_partition_dp.cpp) | Matrix chain multiplication (DP) | [Open →](./linkedlist.cpp/MCM_partition_dp.cpp) |
| [practiceLL.cpp](./linkedlist.cpp/practiceLL.cpp), [practicelinkedl.cpp](./linkedlist.cpp/practicelinkedl.cpp) | Practice | [Open →](./linkedlist.cpp/practiceLL.cpp) · [Open →](./linkedlist.cpp/practicelinkedl.cpp) |

---

### `OOP's.cpp/`

Object-Oriented Programming concepts in C++.

| File | Topic | Code |
|------|-------|------|
| [basicsoops.cpp](./OOP's.cpp/basicsoops.cpp), [basicsoops2.cpp](./OOP's.cpp/basicsoops2.cpp), [practiceoops.cpp](./OOP's.cpp/practiceoops.cpp) | OOP basics | [Open →](./OOP's.cpp/basicsoops.cpp) · [Open →](./OOP's.cpp/basicsoops2.cpp) · [Open →](./OOP's.cpp/practiceoops.cpp) |
| [constructor.cpp](./OOP's.cpp/constructor.cpp) | Constructors | [Open →](./OOP's.cpp/constructor.cpp) |
| [thiskeyword.cpp](./OOP's.cpp/thiskeyword.cpp) | `this` keyword | [Open →](./OOP's.cpp/thiskeyword.cpp) |
| [fourpillars.cpp](./OOP's.cpp/fourpillars.cpp), [practicefourpillars.cpp](./OOP's.cpp/practicefourpillars.cpp) | Four pillars of OOP | [Open →](./OOP's.cpp/fourpillars.cpp) · [Open →](./OOP's.cpp/practicefourpillars.cpp) |
| [inheritance.cpp](./OOP's.cpp/inheritance.cpp) | Inheritance | [Open →](./OOP's.cpp/inheritance.cpp) |
| [polymorphism.cpp](./OOP's.cpp/polymorphism.cpp) | Polymorphism | [Open →](./OOP's.cpp/polymorphism.cpp) |
| [diamondprblm.cpp](./OOP's.cpp/diamondprblm.cpp) | Diamond problem | [Open →](./OOP's.cpp/diamondprblm.cpp) |

---

### `queues.cpp/`

Queue, deque, circular queue, and queue-based problems.

| File | Topic | Code |
|------|-------|------|
| [arrayimpln.cpp](./queues.cpp/arrayimpln.cpp), [practicequeue.cpp](./queues.cpp/practicequeue.cpp) | Queue basics | [Open →](./queues.cpp/arrayimpln.cpp) · [Open →](./queues.cpp/practicequeue.cpp) |
| [DEqueue.cpp](./queues.cpp/DEqueue.cpp), [implementDEqueue.cpp](./queues.cpp/implementDEqueue.cpp), [implementcqueue.cpp](./queues.cpp/implementcqueue.cpp) | Deque & circular queue | [Open →](./queues.cpp/DEqueue.cpp) · [Open →](./queues.cpp/implementDEqueue.cpp) · [Open →](./queues.cpp/implementcqueue.cpp) |
| [queuefromstacks.cpp](./queues.cpp/queuefromstacks.cpp) | Queue using stacks | [Open →](./queues.cpp/queuefromstacks.cpp) |
| [reversequeue.cpp](./queues.cpp/reversequeue.cpp), [reversekelements.cpp](./queues.cpp/reversekelements.cpp) | Reverse queue / K elements | [Open →](./queues.cpp/reversequeue.cpp) · [Open →](./queues.cpp/reversekelements.cpp) |
| [interleavequeue.cpp](./queues.cpp/interleavequeue.cpp) | Interleave queue | [Open →](./queues.cpp/interleavequeue.cpp) |
| [slidingwindow.cpp](./queues.cpp/slidingwindow.cpp) | Sliding window maximum | [Open →](./queues.cpp/slidingwindow.cpp) |
| [nonrepeatingchar.cpp](./queues.cpp/nonrepeatingchar.cpp) | First non-repeating character | [Open →](./queues.cpp/nonrepeatingchar.cpp) |

---

### `recursion.cpp/`

Recursion, backtracking, and recursive sorting/searching.

| File | Topic | Code |
|------|-------|------|
| [factorial.cpp](./recursion.cpp/factorial.cpp), [fibonacci.cpp](./recursion.cpp/fibonacci.cpp), [apowerb.cpp](./recursion.cpp/apowerb.cpp) | Classic recursion | [Open →](./recursion.cpp/factorial.cpp) · [Open →](./recursion.cpp/fibonacci.cpp) · [Open →](./recursion.cpp/apowerb.cpp) |
| [linearsearch.cpp](./recursion.cpp/linearsearch.cpp), [binarysearch.cpp](./recursion.cpp/binarysearch.cpp) | Recursive search | [Open →](./recursion.cpp/linearsearch.cpp) · [Open →](./recursion.cpp/binarysearch.cpp) |
| [maxelement.cpp](./recursion.cpp/maxelement.cpp), [minelement.cpp](./recursion.cpp/minelement.cpp), [sortedarray.cpp](./recursion.cpp/sortedarray.cpp) | Array via recursion | [Open →](./recursion.cpp/maxelement.cpp) · [Open →](./recursion.cpp/minelement.cpp) · [Open →](./recursion.cpp/sortedarray.cpp) |
| [reversestring.cpp](./recursion.cpp/reversestring.cpp), [pallindromestr.cpp](./recursion.cpp/pallindromestr.cpp), [saydigits.cpp](./recursion.cpp/saydigits.cpp), [digitsrec.cpp](./recursion.cpp/digitsrec.cpp) | String recursion | [Open →](./recursion.cpp/reversestring.cpp) · [Open →](./recursion.cpp/pallindromestr.cpp) · [Open →](./recursion.cpp/saydigits.cpp) · [Open →](./recursion.cpp/digitsrec.cpp) |
| [mergesort.cpp](./recursion.cpp/mergesort.cpp), [quicksort.cpp](./recursion.cpp/quicksort.cpp), [bubblesort.cpp](./recursion.cpp/bubblesort.cpp), [inplacesort.cpp](./recursion.cpp/inplacesort.cpp), [gapmethod.cpp](./recursion.cpp/gapmethod.cpp) | Recursive sorting | [Open →](./recursion.cpp/mergesort.cpp) · [Open →](./recursion.cpp/quicksort.cpp) · [Open →](./recursion.cpp/bubblesort.cpp) · [Open →](./recursion.cpp/inplacesort.cpp) · [Open →](./recursion.cpp/gapmethod.cpp) |
| [subsequences.cpp](./recursion.cpp/subsequences.cpp), [setsubsets.cpp](./recursion.cpp/setsubsets.cpp), [permutationofstr.cpp](./recursion.cpp/permutationofstr.cpp) | Subsets & permutations | [Open →](./recursion.cpp/subsequences.cpp) · [Open →](./recursion.cpp/setsubsets.cpp) · [Open →](./recursion.cpp/permutationofstr.cpp) |
| [generateparenthesis.cpp](./recursion.cpp/generateparenthesis.cpp) | Generate valid parentheses | [Open →](./recursion.cpp/generateparenthesis.cpp) |
| [coinchangeprblm.cpp](./recursion.cpp/coinchangeprblm.cpp), [houserobber.cpp](./recursion.cpp/houserobber.cpp), [maximumsum.cpp](./recursion.cpp/maximumsum.cpp) | DP-style recursion | [Open →](./recursion.cpp/coinchangeprblm.cpp) · [Open →](./recursion.cpp/houserobber.cpp) · [Open →](./recursion.cpp/maximumsum.cpp) |
| [ratinmazeprblm.cpp](./recursion.cpp/ratinmazeprblm.cpp), [phnkeypadprblm.cpp](./recursion.cpp/phnkeypadprblm.cpp), [cutinsegment.cpp](./recursion.cpp/cutinsegment.cpp) | Backtracking | [Open →](./recursion.cpp/ratinmazeprblm.cpp) · [Open →](./recursion.cpp/phnkeypadprblm.cpp) · [Open →](./recursion.cpp/cutinsegment.cpp) |
| [countinversion.cpp](./recursion.cpp/countinversion.cpp), [mergearray.cpp](./recursion.cpp/mergearray.cpp) | Merge & inversion count | [Open →](./recursion.cpp/countinversion.cpp) · [Open →](./recursion.cpp/mergearray.cpp) |
| [headandtail.cpp](./recursion.cpp/headandtail.cpp), [printsum.cpp](./recursion.cpp/printsum.cpp), [stringelement.cpp](./recursion.cpp/stringelement.cpp) | Basics | [Open →](./recursion.cpp/headandtail.cpp) · [Open →](./recursion.cpp/printsum.cpp) · [Open →](./recursion.cpp/stringelement.cpp) |
| [practicerecursion.cpp](./recursion.cpp/practicerecursion.cpp), [pracrec2.cpp](./recursion.cpp/pracrec2.cpp), [practicesorting.cpp](./recursion.cpp/practicesorting.cpp) | Practice | [Open →](./recursion.cpp/practicerecursion.cpp) · [Open →](./recursion.cpp/pracrec2.cpp) · [Open →](./recursion.cpp/practicesorting.cpp) |

---

### `segment_tree/`

Segment trees, Fenwick trees, sqrt decomposition, and related range query techniques.

> See also: [segment_tree/important.txt](./segment_tree/important.txt) — a detailed **Segment Tree vs Fenwick Tree decision guide** (Hindi + English).

| File | Topic | Code |
|------|-------|------|
| [min_max_segment_tree.cpp](./segment_tree/min_max_segment_tree.cpp) | Min/max segment tree | [Open →](./segment_tree/min_max_segment_tree.cpp) |
| [lazy_propogation.cpp](./segment_tree/lazy_propogation.cpp) | Lazy propagation (range update) | [Open →](./segment_tree/lazy_propogation.cpp) |
| [dynamic_segment_tree.cpp](./segment_tree/dynamic_segment_tree.cpp) | Dynamic segment tree | [Open →](./segment_tree/dynamic_segment_tree.cpp) |
| [2D_segment_tree.cpp](./segment_tree/2D_segment_tree.cpp), [2D_Segment_tree_important.cpp](./segment_tree/2D_Segment_tree_important.cpp) | 2D segment tree | [Open →](./segment_tree/2D_segment_tree.cpp) · [Open →](./segment_tree/2D_Segment_tree_important.cpp) |
| [variations_in_seg_tree.cpp](./segment_tree/variations_in_seg_tree.cpp), [gcd_problem_segment_tree.cpp](./segment_tree/gcd_problem_segment_tree.cpp) | Seg tree variations & GCD | [Open →](./segment_tree/variations_in_seg_tree.cpp) · [Open →](./segment_tree/gcd_problem_segment_tree.cpp) |
| [fenwick_tree_variations_types.cpp](./segment_tree/fenwick_tree_variations_types.cpp), [fenwick_tree_xor.cpp](./segment_tree/fenwick_tree_xor.cpp), [xor_fenwick_tree.cpp](./segment_tree/xor_fenwick_tree.cpp) | Fenwick tree variants | [Open →](./segment_tree/fenwick_tree_variations_types.cpp) · [Open →](./segment_tree/fenwick_tree_xor.cpp) · [Open →](./segment_tree/xor_fenwick_tree.cpp) |
| [2d_fenwick_tree.cpp](./segment_tree/2d_fenwick_tree.cpp) | 2D Fenwick tree | [Open →](./segment_tree/2d_fenwick_tree.cpp) |
| [count_inversion_fenwick_tree.cpp](./segment_tree/count_inversion_fenwick_tree.cpp) | Inversion count via Fenwick | [Open →](./segment_tree/count_inversion_fenwick_tree.cpp) |
| [Count_of_number_in_array_less_than_x_using_fenwick_tree.cpp](./segment_tree/Count_of_number_in_array_less_than_x_using_fenwick_tree.cpp) | Count smaller elements | [Open →](./segment_tree/Count_of_number_in_array_less_than_x_using_fenwick_tree.cpp) |
| [coordinate_compression.cpp](./segment_tree/coordinate_compression.cpp) | Coordinate compression | [Open →](./segment_tree/coordinate_compression.cpp) |
| [sqrt_decomposition.cpp](./segment_tree/sqrt_decomposition.cpp) | Square root decomposition | [Open →](./segment_tree/sqrt_decomposition.cpp) |
| [euler_tour_+_segment_tree.cpp](./segment_tree/euler_tour_+_segment_tree.cpp) | Euler tour + segment tree on trees | [Open →](./segment_tree/euler_tour_+_segment_tree.cpp) |
| [subtree_query_problems.cpp](./segment_tree/subtree_query_problems.cpp) | Subtree queries | [Open →](./segment_tree/subtree_query_problems.cpp) |
| [k_smallest_number_in_range.cpp](./segment_tree/k_smallest_number_in_range.cpp) | K-th smallest in range | [Open →](./segment_tree/k_smallest_number_in_range.cpp) |
| [all_trees.cpp](./segment_tree/all_trees.cpp) | Tree-related segment tree problems | [Open →](./segment_tree/all_trees.cpp) |
| [Leetcode_315_fenwick_tree.cpp](./segment_tree/Leetcode_315_fenwick_tree.cpp) | LeetCode 315 (count of smaller numbers) | [Open →](./segment_tree/Leetcode_315_fenwick_tree.cpp) |
| [Leetcode_3636_Mos_algo.cpp](./segment_tree/Leetcode_3636_Mos_algo.cpp) | LeetCode 3636 (Mo's algorithm) | [Open →](./segment_tree/Leetcode_3636_Mos_algo.cpp) |

---

### `stacks.cpp/`

Stack implementations and monotonic stack problems.

| File | Topic | Code |
|------|-------|------|
| [stackbasics.cpp](./stacks.cpp/stackbasics.cpp), [stackarray.cpp](./stacks.cpp/stackarray.cpp), [practicestacks.cpp](./stacks.cpp/practicestacks.cpp), [practicestacks2.cpp](./stacks.cpp/practicestacks2.cpp) | Stack basics | [Open →](./stacks.cpp/stackbasics.cpp) · [Open →](./stacks.cpp/stackarray.cpp) · [Open →](./stacks.cpp/practicestacks.cpp) · [Open →](./stacks.cpp/practicestacks2.cpp) |
| [validbrackets.cpp](./stacks.cpp/validbrackets.cpp), [checkredbracket.cpp](./stacks.cpp/checkredbracket.cpp), [bracketreversal.cpp](./stacks.cpp/bracketreversal.cpp) | Bracket problems | [Open →](./stacks.cpp/validbrackets.cpp) · [Open →](./stacks.cpp/checkredbracket.cpp) · [Open →](./stacks.cpp/bracketreversal.cpp) |
| [minstack.cpp](./stacks.cpp/minstack.cpp) | Min stack | [Open →](./stacks.cpp/minstack.cpp) |
| [nextsmaller.cpp](./stacks.cpp/nextsmaller.cpp), [prevsmallelement.cpp](./stacks.cpp/prevsmallelement.cpp) | Next/previous smaller element | [Open →](./stacks.cpp/nextsmaller.cpp) · [Open →](./stacks.cpp/prevsmallelement.cpp) |
| [histogramarea.cpp](./stacks.cpp/histogramarea.cpp) | Largest rectangle in histogram | [Open →](./stacks.cpp/histogramarea.cpp) |
| [insertatbottom.cpp](./stacks.cpp/insertatbottom.cpp), [reversestack.cpp](./stacks.cpp/reversestack.cpp), [removedup.cpp](./stacks.cpp/removedup.cpp) | Stack operations | [Open →](./stacks.cpp/insertatbottom.cpp) · [Open →](./stacks.cpp/reversestack.cpp) · [Open →](./stacks.cpp/removedup.cpp) |
| [implement2stacks.cpp](./stacks.cpp/implement2stacks.cpp), [twostackarray.cpp](./stacks.cpp/twostackarray.cpp), [nstackarray.cpp](./stacks.cpp/nstackarray.cpp) | N stacks in one array | [Open →](./stacks.cpp/implement2stacks.cpp) · [Open →](./stacks.cpp/twostackarray.cpp) · [Open →](./stacks.cpp/nstackarray.cpp) |
| [celebrityprblm.cpp](./stacks.cpp/celebrityprblm.cpp), [onlinestockprblm.cpp](./stacks.cpp/onlinestockprblm.cpp), [asteroidcollision.cpp](./stacks.cpp/asteroidcollision.cpp) | Classic stack problems | [Open →](./stacks.cpp/celebrityprblm.cpp) · [Open →](./stacks.cpp/onlinestockprblm.cpp) · [Open →](./stacks.cpp/asteroidcollision.cpp) |
| [leetcode1003.cpp](./stacks.cpp/leetcode1003.cpp) | LeetCode 1003 (valid parentheses after delete) | [Open →](./stacks.cpp/leetcode1003.cpp) |

---

### `strings.cpp/`

| File | Topic | Code |
|------|-------|------|
| [basicstring.cpp](./strings.cpp/basicstring.cpp), [inbuiltstr.cpp](./strings.cpp/inbuiltstr.cpp) | String basics & STL | [Open →](./strings.cpp/basicstring.cpp) · [Open →](./strings.cpp/inbuiltstr.cpp) |
| [pallindrome.cpp](./strings.cpp/pallindrome.cpp) | Palindrome | [Open →](./strings.cpp/pallindrome.cpp) |
| [removeduplicate.cpp](./strings.cpp/removeduplicate.cpp), [removekdup.cpp](./strings.cpp/removekdup.cpp), [removeoccrnce.cpp](./strings.cpp/removeoccrnce.cpp) | Remove duplicates/occurrences | [Open →](./strings.cpp/removeduplicate.cpp) · [Open →](./strings.cpp/removekdup.cpp) · [Open →](./strings.cpp/removeoccrnce.cpp) |
| [practicestring.cpp](./strings.cpp/practicestring.cpp), [practicestrings.cpp](./strings.cpp/practicestrings.cpp) | Practice | [Open →](./strings.cpp/practicestring.cpp) · [Open →](./strings.cpp/practicestrings.cpp) |

---

### `trees.cpp/`

Binary tree creation, traversals, views, and advanced tree techniques.

| File | Topic | Code |
|------|-------|------|
| [basictrees.cpp](./trees.cpp/basictrees.cpp), [make_binary_tree.cpp](./trees.cpp/make_binary_tree.cpp), [practiceBT.cpp](./trees.cpp/practiceBT.cpp) | Tree basics & creation | [Open →](./trees.cpp/basictrees.cpp) · [Open →](./trees.cpp/make_binary_tree.cpp) · [Open →](./trees.cpp/practiceBT.cpp) |
| [inpretreecreate.cpp](./trees.cpp/inpretreecreate.cpp), [inposttreecreate.cpp](./trees.cpp/inposttreecreate.cpp) | Build tree from traversals | [Open →](./trees.cpp/inpretreecreate.cpp) · [Open →](./trees.cpp/inposttreecreate.cpp) |
| [heightBT.cpp](./trees.cpp/heightBT.cpp), [diameterBT.cpp](./trees.cpp/diameterBT.cpp), [balancedBT.cpp](./trees.cpp/balancedBT.cpp) | Height, diameter, balance check | [Open →](./trees.cpp/heightBT.cpp) · [Open →](./trees.cpp/diameterBT.cpp) · [Open →](./trees.cpp/balancedBT.cpp) |
| [LCA.cpp](./trees.cpp/LCA.cpp) | Lowest Common Ancestor | [Open →](./trees.cpp/LCA.cpp) |
| [leftview.cpp](./trees.cpp/leftview.cpp), [rightview.cpp](./trees.cpp/rightview.cpp), [topview.cpp](./trees.cpp/topview.cpp) | Tree views | [Open →](./trees.cpp/leftview.cpp) · [Open →](./trees.cpp/rightview.cpp) · [Open →](./trees.cpp/topview.cpp) |
| [boundarytraversal.cpp](./trees.cpp/boundarytraversal.cpp), [zigzagtraversal.cpp](./trees.cpp/zigzagtraversal.cpp), [diagonaltraversal.cpp](./trees.cpp/diagonaltraversal.cpp) | Traversals | [Open →](./trees.cpp/boundarytraversal.cpp) · [Open →](./trees.cpp/zigzagtraversal.cpp) · [Open →](./trees.cpp/diagonaltraversal.cpp) |
| [pathsum.cpp](./trees.cpp/pathsum.cpp), [tree_leaf.cpp](./trees.cpp/tree_leaf.cpp) | Path sum & leaf nodes | [Open →](./trees.cpp/pathsum.cpp) · [Open →](./trees.cpp/tree_leaf.cpp) |
| [making_bst.cpp](./trees.cpp/making_bst.cpp) | BST construction | [Open →](./trees.cpp/making_bst.cpp) |
| [morris_binary_tree.cpp](./trees.cpp/morris_binary_tree.cpp), [morris_bst.cpp](./trees.cpp/morris_bst.cpp) | Morris traversal (O(1) space) | [Open →](./trees.cpp/morris_binary_tree.cpp) · [Open →](./trees.cpp/morris_bst.cpp) |
| [revised.cpp](./trees.cpp/revised.cpp) | Revised tree problems | [Open →](./trees.cpp/revised.cpp) |

---

### `vector.cpp/`

| File | Topic | Code |
|------|-------|------|
| [basicvector.cpp](./vector.cpp/basicvector.cpp) | STL vector basics | [Open →](./vector.cpp/basicvector.cpp) |
| [pairsum.cpp](./vector.cpp/pairsum.cpp), [uniqueelement.cpp](./vector.cpp/uniqueelement.cpp) | Pair sum & unique elements | [Open →](./vector.cpp/pairsum.cpp) · [Open →](./vector.cpp/uniqueelement.cpp) |
| [jaggedarray.cpp](./vector.cpp/jaggedarray.cpp) | Jagged array via vector | [Open →](./vector.cpp/jaggedarray.cpp) |
| [practice1.cpp](./vector.cpp/practice1.cpp) | Practice | [Open →](./vector.cpp/practice1.cpp) |

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
