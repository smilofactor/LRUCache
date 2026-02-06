# High-Performance LRU Cache Engine

A C++ implementation of a Least Recently Used (LRU) cache designed for low-latency systems.

## Technical Specifications
- **Time Complexity**: O(1) for both `get` and `put` operations.
- **Space Complexity**: O(n), where n is the capacity of the cache.
- **Data Structures**: 
    - `std::unordered_map` for constant-time lookups.
    - `std::list` (doubly-linked) for O(1) reordering and eviction.
- **Memory Optimization**: Uses `std::list::splice` to move elements within the list without reallocating nodes or copying data, maintaining zero-overhead frequency tracking.

## Design Decisions
1. **Splice vs. Erase/Push**: Many implementations erase and re-insert nodes on a "hit." This implementation uses `splice`, which only redirects pointers, keeping the memory manifold stable and avoiding allocator churn.
2. **Iterator Stability**: Iterators in `std::list` remain valid even after other elements are inserted or deleted, making it a robust choice for the value type in the hash map.
3. **Thread Safety**: Included basic `std::mutex` locking to demonstrate awareness of concurrency requirements in trading infrastructure.

## Building and Testing
```bash
g++ -O3 -std=c++17 lru_cache.cpp -o lru_cache
./lru_cache
