#include "Simulation.hpp"
#include <unordered_set>

Simulation::Simulation(int32_t width, int32_t height)
    : m_width(width), m_height(height), m_generation(0), m_sparseMode(false) {
    m_currentGrid = std::make_unique<DenseGrid>(width, height);
    m_nextGrid = std::make_unique<DenseGrid>(width, height);
}

void Simulation::update() {
    if (m_sparseMode) {
        stepSparse();
    } else {
        stepDense();
    }
    
    // Swap grids
    m_currentGrid.swap(m_nextGrid);
    m_generation++;
}

void Simulation::reset() {
    m_currentGrid->clear();
    m_nextGrid->clear();
    m_generation = 0;
}

Grid& Simulation::getGrid() {
    return *m_currentGrid;
}

const Grid& Simulation::getGrid() const {
    return *m_currentGrid;
}

void Simulation::setSparseMode(bool sparse) {
    if (m_sparseMode == sparse) return;

    m_sparseMode = sparse;
    auto aliveCells = m_currentGrid->getAliveCells();
    
    if (sparse) {
        m_currentGrid = std::make_unique<SparseGrid>();
        m_nextGrid = std::make_unique<SparseGrid>();
    } else {
        m_currentGrid = std::make_unique<DenseGrid>(m_width, m_height);
        m_nextGrid = std::make_unique<DenseGrid>(m_width, m_height);
    }
    
    // Restore alive cells
    for (const auto& cell : aliveCells) {
        m_currentGrid->setCell(cell.x, cell.y, true);
    }
}

bool Simulation::isSparseMode() const {
    return m_sparseMode;
}

std::size_t Simulation::getGeneration() const {
    return m_generation;
}

void Simulation::setGeneration(std::size_t gen) {
    m_generation = gen;
}

void Simulation::stepDense() {
    m_nextGrid->clear();
    
    for (int32_t x = 0; x < m_width; ++x) {
        for (int32_t y = 0; y < m_height; ++y) {
            int neighbors = m_currentGrid->countAliveNeighbors(x, y);
            bool isAlive = m_currentGrid->getCell(x, y);
            
            if (isAlive && (neighbors == 2 || neighbors == 3)) {
                m_nextGrid->setCell(x, y, true);
            } else if (!isAlive && neighbors == 3) {
                m_nextGrid->setCell(x, y, true);
            }
        }
    }
}

void Simulation::stepSparse() {
    m_nextGrid->clear();
    
    // In sparse mode, we only need to check currently alive cells and their immediate neighbors.
    std::unordered_set<CellPosition> cellsToCheck;
    auto aliveCells = m_currentGrid->getAliveCells();
    
    for (const auto& cell : aliveCells) {
        cellsToCheck.insert(cell);
        for (int32_t dx = -1; dx <= 1; ++dx) {
            for (int32_t dy = -1; dy <= 1; ++dy) {
                cellsToCheck.insert({cell.x + dx, cell.y + dy});
            }
        }
    }
    
    for (const auto& cell : cellsToCheck) {
        int neighbors = m_currentGrid->countAliveNeighbors(cell.x, cell.y);
        bool isAlive = m_currentGrid->getCell(cell.x, cell.y);
        
        if (isAlive && (neighbors == 2 || neighbors == 3)) {
            m_nextGrid->setCell(cell.x, cell.y, true);
        } else if (!isAlive && neighbors == 3) {
            m_nextGrid->setCell(cell.x, cell.y, true);
        }
    }
}
