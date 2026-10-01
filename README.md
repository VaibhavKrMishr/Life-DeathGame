# Conway's Game of Life

A production-quality implementation of Conway's Game of Life in modern C++20 using SFML for hardware-accelerated rendering. 

## Features
- **Two Grid Architectures**: 
  - `DenseGrid`: Backed by `std::vector<std::vector<bool>>` for extremely fast small-to-medium worlds.
  - `SparseGrid`: Backed by `std::unordered_set<CellPosition>` for infinite scrolling worlds where only alive cells consume memory.
- **Hardware-Accelerated Rendering**: Uses SFML `sf::VertexArray` to batch-render thousands of cells efficiently in a single draw call.
- **Interactive Camera**: Smooth zooming via scroll-wheel and click-and-drag panning.
- **Pattern Library**: Built-in support for Gliders, Gosper Glider Guns, Pulsars, and more.
- **Serialization**: JSON based save/load using `nlohmann/json`.
- **UI Overlay**: On-screen real-time statistics (FPS, Generation, Alive Cell count).

## Dependencies
- C++20 Compiler (GCC 10+, Clang 10+, or MSVC)
- CMake 3.20+
- SFML 2.6 (Fetched automatically via FetchContent)
- GoogleTest (Fetched automatically via FetchContent)
- nlohmann_json (Fetched automatically via FetchContent)

## Building the Project

```bash
# Clone the repository
git clone <repository_url>
cd LifeAndDeathGame

# Configure and build
cmake -S . -B build -DCMAKE_POLICY_VERSION_MINIMUM=3.5
cmake --build build -j 4
```

## Running

```bash
./build/GameOfLife
```

## Controls
- **Space**: Play / Pause simulation.
- **Right Arrow**: Step forward one generation.
- **Mouse Left Drag**: Draw alive cells.
- **Mouse Right Drag**: Erase alive cells.
- **Mouse Middle Drag**: Pan the camera.
- **Mouse Scroll**: Zoom in / out.
- **1-4 Keys**: Place predefined patterns at the center of the screen.
- **C**: Clear grid.
- **R**: Randomize grid.
- **G**: Toggle grid lines.
- **S**: Save grid state to `save.json`.
- **L**: Load grid state from `save.json`.

## Architecture Highlights
- **SOLID Principles**: Input handling, rendering, data storage, and simulation logic are fully decoupled.
- **Double Buffering**: Grid updates process the `m_currentGrid` and write to `m_nextGrid`, minimizing memory allocation overhead during runtime.

## Testing
Run the comprehensive GoogleTest suite:
```bash
cd build
ctest --output-on-failure
```
# Life-DeathGame
