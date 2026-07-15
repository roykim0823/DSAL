# Algorithm Reference (C++)

Modernized, compilable C++ implementations of the algorithms in
**Robert Sedgewick, *Algorithms in C++, 3rd Edition* (Parts 1–4 and Part 5)**.

The two files `algorithm1-4_code.txt` and `algorithm5_code.txt` are the original
1999/2002 code excerpts from the book (kept verbatim as the source reference).
Each numbered chapter below takes the key algorithms from those excerpts and
rewrites them as **self-contained, standard C++14** that actually builds and runs
— replacing pre-standard constructs (`<iostream.h>`, raw `new[]`, global
`maxN` buffers, implicit `int` return, etc.) with `std::vector`, RAII, templates,
and namespaces, while keeping the algorithmic structure faithful to the text.

> These are teaching demonstrations. Correctness of the algorithm is the goal;
> a few demos intentionally leak nodes rather than clutter the code with cleanup.
> For polished, tested library-style versions of the early topics, see the
> repository's top-level `fundamentals/` and `sorting/` directories.

## Organization

```
algorithm_ref_cpp/
├── CMakeLists.txt            # builds every chapter
├── README.md
├── algorithm1-4_code.txt     # original reference excerpts (Parts 1–4)
├── algorithm5_code.txt       # original reference excerpts (Part 5)
└── chNN_<topic>/             # one directory per chapter
    ├── CMakeLists.txt        # also builds standalone
    ├── include/*.h           # the algorithms/data structures (namespace chNN)
    └── src/main.cc           # a no-argument demo driver
```

Every chapter follows the same convention:

- Reusable code lives in `include/*.h`, wrapped in a `chNN` namespace with an
  `ALG_REF_CHNN_<NAME>_H_` include guard.
- `src/main.cc` has a `main()` that runs a **built-in demo with no command-line
  arguments** and prints clearly labeled output. (Chapter 1 also accepts an
  optional input file.)
- Each chapter builds one executable named `<chapter_dir>_main`.

## Chapters

### Parts 1–4 — Fundamentals, Data Structures, Sorting, Searching
| Dir | Chapter | Contents |
|-----|---------|----------|
| `ch01_introduction`          | 1. Introduction                     | Union-find: quick-find, quick-union, weighted, + path compression |
| `ch02_analysis`              | 2. Principles of Algorithm Analysis | Sequential vs. binary search, with comparison counts |
| `ch03_elementary_ds`         | 3. Elementary Data Structures       | Sieve of Eratosthenes, Josephus (circular list), list reversal |
| `ch04_abstract_data_types`   | 4. Abstract Data Types              | Generic Stack/Queue, postfix eval, Complex roots of unity, Poly |
| `ch05_recursion_trees`       | 5. Recursion and Trees              | factorial/gcd, Towers of Hanoi, Fibonacci (naive vs. memo), tree traversals |
| `ch06_elementary_sorting`    | 6. Elementary Sorting Methods       | selection, insertion, bubble, shellsort, distribution counting |
| `ch07_quicksort`             | 7. Quicksort                        | partition, median-of-three hybrid, 3-way partition, quickselect |
| `ch08_mergesort`             | 8. Mergesort                        | top-down, bottom-up, and linked-list mergesort |
| `ch09_priority_queues_heapsort` | 9. Priority Queues and Heapsort  | heap fixUp/fixDown, max-PQ, heapsort, PQsort |
| `ch10_radix_sorting`         | 10. Radix Sorting                   | LSD radix, MSD radix, binary quicksort (radix exchange) |
| `ch11_special_purpose_sorts` | 11. Special-Purpose Sorts           | Batcher's odd-even mergesort (sorting network), shuffle/unshuffle |
| `ch12_symbol_tables_bst`     | 12. Symbol Tables and BSTs          | BST with search/insert/select/rank/remove, ordered-array ST |
| `ch13_balanced_trees`        | 13. Balanced Trees                  | red-black BST, skip list |
| `ch14_hashing`               | 14. Hashing                         | Horner/modular hashing, separate chaining, linear probing (+resize) |
| `ch15_radix_search`          | 15. Radix Search                    | digital search tree, ternary search trie |
| `ch16_external_searching`    | 16. External Searching              | B-tree symbol table (multiway search + split) |

### Part 5 — Graph Algorithms
| Dir | Chapter | Contents |
|-----|---------|----------|
| `ch17_graph_properties`      | 17. Graph Properties and Types      | dense (matrix) & sparse (list) graphs, adjIterator, degrees, edges |
| `ch18_graph_search`          | 18. Graph Search                    | DFS, connected components, bipartite check, BFS |
| `ch19_digraphs_dags`         | 19. Digraphs and DAGs               | topological sort, transitive closure, strong components |
| `ch20_mst`                   | 20. Minimum Spanning Trees          | Prim and Kruskal |
| `ch21_shortest_paths`        | 21. Shortest Paths                  | Dijkstra (SSSP), Floyd–Warshall (all-pairs) |
| `ch22_network_flow`          | 22. Network Flow                    | max-flow (augmenting paths), bipartite matching |

## Building and running

Requirements: a C++14 compiler and CMake ≥ 3.10.

### Build everything

```sh
cd algorithm_ref_cpp
cmake -S . -B build
cmake --build build -j
```

Executables land under `build/<chapter_dir>/<chapter_dir>_main`. Run any of them
(no arguments needed):

```sh
./build/ch01_introduction/ch01_introduction_main
./build/ch20_mst/ch20_mst_main
```

### Build / run a single chapter

Each chapter is also a standalone CMake project:

```sh
cd ch07_quicksort
cmake -S . -B build
cmake --build build
./build/ch07_quicksort_main
```

### Compile one chapter by hand (no CMake)

```sh
cd ch06_elementary_sorting
c++ -std=c++14 -Wall -Iinclude src/main.cc -o demo && ./demo
```

Build directories (`build/`) are git-ignored.
