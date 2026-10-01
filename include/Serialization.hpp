#pragma once

#include "Grid.hpp"
#include <string>

class Serialization {
public:
    static bool save(const Grid& grid, const std::string& filename);
    static bool load(Grid& grid, const std::string& filename);
};
