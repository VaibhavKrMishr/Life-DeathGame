#pragma once

#include "Grid.hpp"
#include <vector>
#include <string>

class Pattern {
public:
    enum class Type {
        // Still lifes
        Block, Beehive, Loaf, Boat, Tub,
        // Oscillators
        Blinker, Toad, Beacon, Pulsar, Pentadecathlon,
        // Spaceships
        Glider, LightweightSpaceship,
        // Guns
        GosperGliderGun
    };

    static std::vector<CellPosition> get(Type type);
    static std::string getName(Type type);
    
    // Helper to place a pattern on a grid at a specific starting position
    static void place(Grid& grid, int32_t startX, int32_t startY, const std::vector<CellPosition>& pattern);
};
