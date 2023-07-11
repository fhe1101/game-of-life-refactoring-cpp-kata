#include <vector>

#include <gmock/gmock.h>

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

// Test two_or_three_neighbors_live_on
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

// Test over_population
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
