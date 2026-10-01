#include "Grid.hpp"

// ==============================================================================
// DenseGrid Implementation
// ==============================================================================

DenseGrid::DenseGrid(int32_t width, int32_t height)
    : m_width(width), m_height(height) {
    if (m_width > 0 && m_height > 0) {
        m_grid.resize(m_width, std::vector<bool>(m_height, false));
    }
}

bool DenseGrid::getCell(int32_t x, int32_t y) const {
    if (x >= 0 && x < m_width && y >= 0 && y < m_height) {
        return m_grid[x][y];
    }
    return false;
}

void DenseGrid::setCell(int32_t x, int32_t y, bool alive) {
    if (x >= 0 && x < m_width && y >= 0 && y < m_height) {
        if (m_grid[x][y] != alive) {
            m_grid[x][y] = alive;
            if (alive) {
                m_aliveCount++;
            } else {
                m_aliveCount--;
            }
        }
    }
}

void DenseGrid::toggleCell(int32_t x, int32_t y) {
    if (x >= 0 && x < m_width && y >= 0 && y < m_height) {
        m_grid[x][y] = !m_grid[x][y];
        if (m_grid[x][y]) {
            m_aliveCount++;
        } else {
            m_aliveCount--;
        }
    }
}

void DenseGrid::clear() {
    for (int x = 0; x < m_width; ++x) {
        std::fill(m_grid[x].begin(), m_grid[x].end(), false);
    }
    m_aliveCount = 0;
}

int DenseGrid::countAliveNeighbors(int32_t x, int32_t y) const {
    int count = 0;
    for (int32_t dx = -1; dx <= 1; ++dx) {
        for (int32_t dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;
            
            // For now, no wrapping (finite grid)
            int32_t nx = x + dx;
            int32_t ny = y + dy;
            if (nx >= 0 && nx < m_width && ny >= 0 && ny < m_height) {
                if (m_grid[nx][ny]) {
                    count++;
                }
            }
        }
    }
    return count;
}

std::vector<CellPosition> DenseGrid::getAliveCells() const {
    std::vector<CellPosition> aliveCells;
    aliveCells.reserve(m_aliveCount);
    for (int32_t x = 0; x < m_width; ++x) {
        for (int32_t y = 0; y < m_height; ++y) {
            if (m_grid[x][y]) {
                aliveCells.push_back({x, y});
            }
        }
    }
    return aliveCells;
}

std::size_t DenseGrid::getAliveCount() const {
    return m_aliveCount;
}

// ==============================================================================
// SparseGrid Implementation
// ==============================================================================

bool SparseGrid::getCell(int32_t x, int32_t y) const {
    return m_cells.find({x, y}) != m_cells.end();
}

void SparseGrid::setCell(int32_t x, int32_t y, bool alive) {
    if (alive) {
        m_cells.insert({x, y});
    } else {
        m_cells.erase({x, y});
    }
}

void SparseGrid::toggleCell(int32_t x, int32_t y) {
    auto it = m_cells.find({x, y});
    if (it != m_cells.end()) {
        m_cells.erase(it);
    } else {
        m_cells.insert({x, y});
    }
}

void SparseGrid::clear() {
    m_cells.clear();
}

int SparseGrid::countAliveNeighbors(int32_t x, int32_t y) const {
    int count = 0;
    for (int32_t dx = -1; dx <= 1; ++dx) {
        for (int32_t dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;
            
            if (m_cells.find({x + dx, y + dy}) != m_cells.end()) {
                count++;
            }
        }
    }
    return count;
}

std::vector<CellPosition> SparseGrid::getAliveCells() const {
    std::vector<CellPosition> aliveCells;
    aliveCells.reserve(m_cells.size());
    for (const auto& cell : m_cells) {
        aliveCells.push_back(cell);
    }
    return aliveCells;
}

std::size_t SparseGrid::getAliveCount() const {
    return m_cells.size();
}
