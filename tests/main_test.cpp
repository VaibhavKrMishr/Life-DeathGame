#include <gtest/gtest.h>
#include "../include/Grid.hpp"
#include "../include/Simulation.hpp"

TEST(DenseGridTest, CellOperations) {
    DenseGrid grid(10, 10);
    EXPECT_FALSE(grid.getCell(5, 5));
    
    grid.setCell(5, 5, true);
    EXPECT_TRUE(grid.getCell(5, 5));
    
    grid.toggleCell(5, 5);
    EXPECT_FALSE(grid.getCell(5, 5));
    
    grid.setCell(5, 5, true);
    grid.clear();
    EXPECT_FALSE(grid.getCell(5, 5));
    EXPECT_EQ(grid.getAliveCount(), 0);
}

TEST(SparseGridTest, CellOperations) {
    SparseGrid grid;
    EXPECT_FALSE(grid.getCell(100, 100));
    
    grid.setCell(100, 100, true);
    EXPECT_TRUE(grid.getCell(100, 100));
    
    grid.toggleCell(100, 100);
    EXPECT_FALSE(grid.getCell(100, 100));
    
    grid.setCell(100, 100, true);
    grid.clear();
    EXPECT_FALSE(grid.getCell(100, 100));
    EXPECT_EQ(grid.getAliveCount(), 0);
}

TEST(GridTest, NeighborCounting) {
    DenseGrid grid(10, 10);
    grid.setCell(5, 5, true);
    grid.setCell(5, 6, true);
    grid.setCell(6, 5, true);
    
    EXPECT_EQ(grid.countAliveNeighbors(5, 5), 2);
    EXPECT_EQ(grid.countAliveNeighbors(6, 6), 3);
}

TEST(SimulationTest, CoreRules) {
    Simulation sim(10, 10);
    sim.setSparseMode(false);
    auto& grid = sim.getGrid();
    
    // Blinker
    grid.setCell(5, 4, true);
    grid.setCell(5, 5, true);
    grid.setCell(5, 6, true);
    
    sim.update();
    
    EXPECT_FALSE(sim.getGrid().getCell(5, 4));
    EXPECT_TRUE(sim.getGrid().getCell(4, 5));
    EXPECT_TRUE(sim.getGrid().getCell(5, 5));
    EXPECT_TRUE(sim.getGrid().getCell(6, 5));
    EXPECT_FALSE(sim.getGrid().getCell(5, 6));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
