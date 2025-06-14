#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "game.h"

TEST(GameTest, UnderPopulation)
{
    std::vector<std::vector<size_t>> initial_grid = {
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 0},
    };
    Game game(initial_grid);
    game.iterate();

    std::vector<std::vector<size_t>> expected_grid = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
    };
    EXPECT_EQ(game.grid, expected_grid);
}

TEST(GameTest, TwoOrThreeNeighborsLiveOn)
{
    std::vector<std::vector<size_t>> initial_grid = {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0},
    };
    Game game(initial_grid);
    game.iterate();

    std::vector<std::vector<size_t>> expected_grid = {
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
    };
    EXPECT_EQ(game.grid, expected_grid);
}

TEST(GameTest, OverPopulation)
{
    std::vector<std::vector<size_t>> initial_grid = {
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0},
    };
    Game game(initial_grid);
    game.iterate();

    std::vector<std::vector<size_t>> expected_grid = {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 1, 0, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0},
    };
    EXPECT_EQ(game.grid, expected_grid);
}

TEST(GameTest, OverPopulationAcrossBoundaries)
{
    std::vector<std::vector<size_t>> initial_grid = {
        {1, 0, 0, 1, 1},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1},
    };
    Game game(initial_grid);
    game.iterate();

    std::vector<std::vector<size_t>> expected_grid = {
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 1},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {1, 0, 0, 1, 1},
    };
    EXPECT_EQ(game.grid, expected_grid);
}

TEST(GameTest, Reproduction)
{
    std::vector<std::vector<size_t>> initial_grid = {
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0},
    };
    Game game(initial_grid);
    game.iterate();

    std::vector<std::vector<size_t>> expected_grid = {
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0},
    };
    EXPECT_EQ(game.grid, expected_grid);
}

TEST(ImportantCellTest, AlwaysStaysAlive) {
    std::vector<std::vector<size_t>> grid = {
        {0, 1, 0},
        {1, 1, 1},
        {0, 1, 0}
    };
    Important cell(1, 1);
    EXPECT_TRUE(cell.will_stay_alive(grid));
    grid = {{0,0,0},{0,1,0},{0,0,0}};
    EXPECT_TRUE(cell.will_stay_alive(grid));
}

TEST(ReproductiveCellTest, StaysAliveWithTwoOrThreeNeighbors) {
    std::vector<std::vector<size_t>> grid2 = {
        {0, 1, 0},
        {1, 1, 0},
        {0, 0, 0}
    };
    Reproductive cell2(1, 1);
    EXPECT_TRUE(cell2.will_stay_alive(grid2)); // 2 neighbors

    std::vector<std::vector<size_t>> grid3 = {
        {1, 1, 1},
        {0, 1, 0},
        {0, 0, 0}
    };
    Reproductive cell3(1, 1);
    EXPECT_TRUE(cell3.will_stay_alive(grid3)); // 3 neighbors

    std::vector<std::vector<size_t>> grid1 = {
        {0, 0, 0},
        {1, 1, 0},
        {0, 0, 0}
    };
    Reproductive cell1(1, 1);
    EXPECT_FALSE(cell1.will_stay_alive(grid1)); // 1 neighbor
}

TEST(ReproductiveCellTest, BornWithTwoOrThreeNeighbors) {
    std::vector<std::vector<size_t>> grid2 = {
        {0, 1, 0},
        {1, 0, 0},
        {0, 0, 0}
    };
    Reproductive cell2(1, 1);
    EXPECT_TRUE(cell2.will_be_born(grid2)); // 2 neighbors

    std::vector<std::vector<size_t>> grid3 = {
        {1, 1, 1},
        {0, 0, 0},
        {0, 0, 0}
    };
    Reproductive cell3(1, 1);
    EXPECT_TRUE(cell3.will_be_born(grid3)); // 3 neighbors

    std::vector<std::vector<size_t>> grid1 = {
        {0, 0, 0},
        {1, 0, 0},
        {0, 0, 0}
    };
    Reproductive cell1(1, 1);
    EXPECT_FALSE(cell1.will_be_born(grid1)); // 1 neighbor
}

TEST(LazyCellTest, StaysAliveWithExactlyThreeNeighbors) {
    std::vector<std::vector<size_t>> grid3 = {
        {1, 1, 1},
        {0, 1, 0},
        {0, 0, 0}
    };
    Lazy cell3(1, 1);
    EXPECT_TRUE(cell3.will_stay_alive(grid3)); // 3 neighbors

    std::vector<std::vector<size_t>> grid2 = {
        {0, 1, 0},
        {1, 1, 0},
        {0, 0, 0}
    };
    Lazy cell2(1, 1);
    EXPECT_FALSE(cell2.will_stay_alive(grid2)); // 2 neighbors

    std::vector<std::vector<size_t>> grid4 = {
        {1, 1, 1},
        {1, 1, 0},
        {0, 0, 0}
    };
    Lazy cell4(1, 1);
    EXPECT_FALSE(cell4.will_stay_alive(grid4)); // 4 neighbors
}
