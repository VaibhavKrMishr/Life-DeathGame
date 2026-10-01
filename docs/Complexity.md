# Time and Space Complexity Analysis

## Dense Grid (`std::vector<std::vector<bool>>`)

The Dense Grid allocates memory for the entire configured boundary area regardless of how many cells are actually alive.

### Space Complexity
- **O(W * H)** where `W` is width and `H` is height.
- Specifically, `std::vector<bool>` optimizes storage to 1 bit per cell. Thus, a 1000x1000 grid uses roughly 1,000,000 bits (~122 KB) per buffer. Since we use double-buffering, it uses ~244 KB total.
- Highly cache-friendly due to contiguous memory allocation.

### Time Complexity
- **Grid Update (Simulation Step)**: **O(W * H)**. The algorithm must iterate over every cell in the bounds to count neighbors, even if large portions of the grid are dead. 
- **Cell Lookup / Set**: **O(1)** via direct 2D array indexing.
- **Clear**: **O(W * H)**.

## Sparse Grid (`std::unordered_set<CellPosition>`)

The Sparse Grid only allocates memory for cells that are alive. It operates on an theoretically infinite grid size.

### Space Complexity
- **O(A)** where `A` is the number of alive cells.
- Each `CellPosition` struct is 8 bytes (two 32-bit integers), plus the hash table overhead from `std::unordered_set` (bucket pointers, linked list nodes). 
- If the grid is densely populated, this will consume significantly more memory than `DenseGrid`. If it is extremely sparse in an infinite domain, it is vastly more efficient.

### Time Complexity
- **Grid Update (Simulation Step)**: **O(A)**. 
  - The algorithm first identifies the "cells to check" by collecting all alive cells and their 8 neighbors. 
  - Max cells to check = 9 * A.
  - For each cell, we count neighbors, doing 8 hash map lookups.
  - Overall time scales strictly with the number of alive cells, bypassing empty space.
- **Cell Lookup / Set**: **O(1)** on average (amortized).
- **Clear**: **O(A)** to destruct the nodes.

## Conclusion & Optimizations
- Use **DenseGrid** when simulating a bounded area with a high population density (e.g. noise generation or heavily active patterns). Memory locality is excellent and cache misses are rare.
- Use **SparseGrid** when simulating small structures wandering across infinite space (e.g. spaceships) or large, mostly empty configurations.

In this implementation, `sf::VertexArray` operates in **O(A)** rendering time, pushing the performance bottleneck entirely into the simulation update logic, enabling high FPS.
