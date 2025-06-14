#include <stdexcept>
#include <vector>

class Cell {
public:
    Cell(size_t row, size_t column) : row(row), column(column) {}
    virtual ~Cell() = default;

    size_t get_neighbor_count(const std::vector<std::vector<size_t>>& grid) const
    {
        size_t rows    = grid.size();
        size_t columns = grid[0].size();

        size_t above = 0;
        size_t below = 0;
        for (int i = -1; i < 2; ++i) {
            size_t col = (column + i + columns) % columns;
            above += grid[(row - 1 + rows) % rows][col];
            below += grid[(row + 1 + rows) % rows][col];
        }
        size_t left  = grid[row][(column - 1 + columns) % columns];
        size_t right = grid[row][(column + 1 + columns) % columns];

        return above + below + left + right;
    }

    virtual bool will_stay_alive(const std::vector<std::vector<size_t>>& grid) const = 0;

protected:
    size_t row;
    size_t column;
};

class Critter final : public Cell {
public:
    using Cell::Cell;

    bool will_stay_alive(const std::vector<std::vector<size_t>>& grid) const final
    {
        auto neighbors = get_neighbor_count(grid);
        return 1 < neighbors && neighbors < 4;
    }
};

class Space final : public Cell {
public:
    using Cell::Cell;

    bool will_stay_alive(const std::vector<std::vector<size_t>>& grid) const final
    {
        return false;
    }

    bool will_be_born(const std::vector<std::vector<size_t>>& grid) const
    {
        return get_neighbor_count(grid) == 3;
    }
};

class Important final : public Cell {
public:
    using Cell::Cell;

    // Important cells never die; always return true
    bool will_stay_alive(const std::vector<std::vector<size_t>>& grid) const final
    {
        return true;
    }
};

class Reproductive final : public Cell {
public:
    using Cell::Cell;

    // Reproductive cells stay alive with 2 or 3 neighbors (like Critter)
    bool will_stay_alive(const std::vector<std::vector<size_t>>& grid) const final
    {
        auto neighbors = get_neighbor_count(grid);
        return 1 < neighbors && neighbors < 4;
    }

    // Reproductive cells are born with 2 or 3 neighbors (instead of just 3)
    bool will_be_born(const std::vector<std::vector<size_t>>& grid) const
    {
        auto neighbors = get_neighbor_count(grid);
        return neighbors == 2 || neighbors == 3;
    }
};

class Lazy final : public Cell {
public:
    using Cell::Cell;

    // Lazy cells stay alive only if they have exactly three neighbors
    bool will_stay_alive(const std::vector<std::vector<size_t>>& grid) const final
    {
        return get_neighbor_count(grid) == 3;
    }
};

class Game {
public:
    explicit Game(std::vector<std::vector<size_t>> grid) : grid(std::move(grid)) {}

    void iterate()
    {
        std::vector<std::vector<size_t>> new_grid;

        for (size_t row_num = 0; row_num < grid.size(); ++row_num) {
            std::vector<size_t> new_row;

            for (size_t col_num = 0; col_num < grid[row_num].size(); ++col_num) {
                size_t cell = grid[row_num][col_num];
                if (cell) {
                    Critter cell_obj(row_num, col_num);
                    new_row.push_back(cell_obj.will_stay_alive(grid));
                }
                else {
                    Space cell_obj(row_num, col_num);
                    new_row.push_back(cell_obj.will_be_born(grid));
                }
            }
            new_grid.push_back(new_row);
        }
        grid = new_grid;
    }

    std::vector<std::vector<size_t>> grid;
};
