#pragma once

#include "Grid.hpp"
#include <memory>

class Simulation {
public:
    Simulation(int32_t width, int32_t height);
    
    // Core engine
    void update();
    void reset();
    
    // Grid access
    Grid& getGrid();
    const Grid& getGrid() const;
    
    // Grid type switching
    void setSparseMode(bool sparse);
    bool isSparseMode() const;
    
    // Statistics
    std::size_t getGeneration() const;
    void setGeneration(std::size_t gen);

private:
    void stepDense();
    void stepSparse();

    std::unique_ptr<Grid> m_currentGrid;
    std::unique_ptr<Grid> m_nextGrid;
    
    int32_t m_width;
    int32_t m_height;
    std::size_t m_generation;
    bool m_sparseMode;
};
