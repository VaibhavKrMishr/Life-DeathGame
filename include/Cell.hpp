#pragma once

#include <cstdint>
#include <functional>

struct CellPosition {
    int32_t x;
    int32_t y;

    bool operator==(const CellPosition& other) const {
        return x == other.x && y == other.y;
    }
};

namespace std {
    template <>
    struct hash<CellPosition> {
        std::size_t operator()(const CellPosition& pos) const {
            // A simple hash combination for two integers
            std::size_t h1 = std::hash<int32_t>{}(pos.x);
            std::size_t h2 = std::hash<int32_t>{}(pos.y);
            return h1 ^ (h2 << 1); 
        }
    };
}
