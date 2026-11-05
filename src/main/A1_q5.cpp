#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <limits>
#include <memory>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

// Assessment 01 Q5; see 题面.pdf.
namespace aim::q5 {


// BEGIN IMPLEMENTATION
std::vector<std::vector<int>> risk(const std::vector<std::string>& grid) {
    if (grid.empty()) {
        return {};
    }

    const int rows = static_cast<int>(grid.size());
    const int columns = static_cast<int>(grid.front().size());
    if (columns == 0) {
        throw std::invalid_argument("grid has zero columns");
    }
    for (const std::string& row : grid) {
        if (static_cast<int>(row.size()) != columns) {
            throw std::invalid_argument("grid rows have different lengths");
        }
        for (char cell : row) {
            if (cell != '.' && cell != '#') {
                throw std::invalid_argument("grid contains an invalid character");
            }
        }
    }

    std::vector<std::vector<int>> result(
        static_cast<std::size_t>(rows),
        std::vector<int>(static_cast<std::size_t>(columns), 0));
    const int rowOffset[4] = {-1, 1, 0, 0};
    const int columnOffset[4] = {0, 0, -1, 1};
    for (int row = 0; row < rows; ++row) {
        for (int column = 0; column < columns; ++column) {
            if (grid[static_cast<std::size_t>(row)][static_cast<std::size_t>(column)] == '#') {
                result[static_cast<std::size_t>(row)][static_cast<std::size_t>(column)] = -1;
                continue;
            }
            int adjacentObstacles = 0;
            for (int direction = 0; direction < 4; ++direction) {
                const int nextRow = row + rowOffset[direction];
                const int nextColumn = column + columnOffset[direction];
                if (nextRow >= 0 && nextRow < rows && nextColumn >= 0 &&
                    nextColumn < columns &&
                    grid[static_cast<std::size_t>(nextRow)][static_cast<std::size_t>(nextColumn)] ==
                        '#') {
                    ++adjacentObstacles;
                }
            }
            result[static_cast<std::size_t>(row)][static_cast<std::size_t>(column)] =
                adjacentObstacles;
        }
    }

    return result;
}
// END IMPLEMENTATION
}

#define CHECK(...) do { if (!(__VA_ARGS__)) throw std::runtime_error("check failed"); } while(false)
#define EXPECT_INVALID(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::invalid_argument&) { caught=true; } CHECK(caught); } while(false)
#define EXPECT_RANGE(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::out_of_range&) { caught=true; } CHECK(caught); } while(false)

using namespace aim::q5;
int main() {
    try {
        { CHECK((risk({".#",".."})==std::vector<std::vector<int>>{{1,-1},{0,1}})); }
        { CHECK(risk({}).empty()); }
        std::cout << "PUBLIC 2/2\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
