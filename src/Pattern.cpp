#include "Pattern.hpp"

std::string Pattern::getName(Type type) {
    switch (type) {
        case Type::Block: return "Block";
        case Type::Beehive: return "Beehive";
        case Type::Loaf: return "Loaf";
        case Type::Boat: return "Boat";
        case Type::Tub: return "Tub";
        case Type::Blinker: return "Blinker";
        case Type::Toad: return "Toad";
        case Type::Beacon: return "Beacon";
        case Type::Pulsar: return "Pulsar";
        case Type::Pentadecathlon: return "Pentadecathlon";
        case Type::Glider: return "Glider";
        case Type::LightweightSpaceship: return "Lightweight Spaceship";
        case Type::GosperGliderGun: return "Gosper Glider Gun";
        default: return "Unknown";
    }
}

void Pattern::place(Grid& grid, int32_t startX, int32_t startY, const std::vector<CellPosition>& pattern) {
    for (const auto& cell : pattern) {
        grid.setCell(startX + cell.x, startY + cell.y, true);
    }
}

std::vector<CellPosition> Pattern::get(Type type) {
    switch (type) {
        case Type::Block:
            return {{0,0}, {1,0}, {0,1}, {1,1}};
        case Type::Beehive:
            return {{1,0}, {2,0}, {0,1}, {3,1}, {1,2}, {2,2}};
        case Type::Loaf:
            return {{1,0}, {2,0}, {0,1}, {3,1}, {1,2}, {3,2}, {2,3}};
        case Type::Boat:
            return {{0,0}, {1,0}, {0,1}, {2,1}, {1,2}};
        case Type::Tub:
            return {{1,0}, {0,1}, {2,1}, {1,2}};
        case Type::Blinker:
            return {{0,0}, {1,0}, {2,0}};
        case Type::Toad:
            return {{1,0}, {2,0}, {3,0}, {0,1}, {1,1}, {2,1}};
        case Type::Beacon:
            return {{0,0}, {1,0}, {0,1}, {3,2}, {2,3}, {3,3}};
        case Type::Glider:
            return {{1,0}, {2,1}, {0,2}, {1,2}, {2,2}};
        case Type::LightweightSpaceship:
            return {{1,0}, {4,0}, {0,1}, {0,2}, {4,2}, {0,3}, {1,3}, {2,3}, {3,3}};
        case Type::Pulsar:
            return {
                {2,0}, {3,0}, {4,0}, {8,0}, {9,0}, {10,0},
                {0,2}, {5,2}, {7,2}, {12,2},
                {0,3}, {5,3}, {7,3}, {12,3},
                {0,4}, {5,4}, {7,4}, {12,4},
                {2,5}, {3,5}, {4,5}, {8,5}, {9,5}, {10,5},
                {2,7}, {3,7}, {4,7}, {8,7}, {9,7}, {10,7},
                {0,8}, {5,8}, {7,8}, {12,8},
                {0,9}, {5,9}, {7,9}, {12,9},
                {0,10}, {5,10}, {7,10}, {12,10},
                {2,12}, {3,12}, {4,12}, {8,12}, {9,12}, {10,12}
            };
        case Type::Pentadecathlon:
            return {
                {1,0}, {1,1}, {0,2}, {2,2}, {1,3}, {1,4}, {1,5}, {1,6},
                {0,7}, {2,7}, {1,8}, {1,9}
            };
        case Type::GosperGliderGun:
            return {
                {0,4}, {1,4}, {0,5}, {1,5},
                {10,4}, {10,5}, {10,6}, {11,3}, {11,7}, {12,2}, {13,2}, {12,8}, {13,8},
                {14,5}, {15,3}, {15,7}, {16,4}, {16,5}, {16,6}, {17,5},
                {20,2}, {21,2}, {20,3}, {21,3}, {20,4}, {21,4}, {22,1}, {22,5},
                {24,0}, {24,1}, {24,5}, {24,6},
                {34,2}, {35,2}, {34,3}, {35,3}
            };
        default:
            return {};
    }
}
