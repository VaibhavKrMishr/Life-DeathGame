#pragma once

#include "Cell.hpp"
#include <vector>
#include <unordered_set>
#include <cstdint>

class Grid {
public:
    virtual ~Grid() = default;

    // Core operations
    virtual bool getCell(int32_t x, int32_t y) const = 0;
    virtual void setCell(int32_t x, int32_t y, bool alive) = 0;
    virtual void toggleCell(int32_t x, int32_t y) = 0;
    virtual void clear() = 0;

    // Simulation helpers
    virtual int countAliveNeighbors(int32_t x, int32_t y) const = 0;

    // Data retrieval for rendering/serialization
    virtual std::vector<CellPosition> getAliveCells() const = 0;
    virtual std::size_t getAliveCount() const = 0;
    
    // Check if the grid has fixed boundaries
    virtual bool isInfinite() const = 0;
};

class DenseGrid : public Grid {
public:
    DenseGrid(int32_t width, int32_t height);

    bool getCell(int32_t x, int32_t y) const override;
    void setCell(int32_t x, int32_t y, bool alive) override;
    void toggleCell(int32_t x, int32_t y) override;
    void clear() override;

    int countAliveNeighbors(int32_t x, int32_t y) const override;
    
    std::vector<CellPosition> getAliveCells() const override;
    std::size_t getAliveCount() const override;
    bool isInfinite() const override { return false; }

    int32_t getWidth() const { return m_width; }
    int32_t getHeight() const { return m_height; }

private:
    int32_t m_width;
    int32_t m_height;
    std::vector<std::vector<bool>> m_grid;
    std::size_t m_aliveCount = 0;
};

class SparseGrid : public Grid {
public:
    SparseGrid() = default;

    bool getCell(int32_t x, int32_t y) const override;
    void setCell(int32_t x, int32_t y, bool alive) override;
    void toggleCell(int32_t x, int32_t y) override;
    void clear() override;

    int countAliveNeighbors(int32_t x, int32_t y) const override;

    std::vector<CellPosition> getAliveCells() const override;
    std::size_t getAliveCount() const override;
    bool isInfinite() const override { return true; }

private:
    std::unordered_set<CellPosition> m_cells;
};
