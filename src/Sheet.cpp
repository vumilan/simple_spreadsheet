//
// Created by Milan on 12.05.2019.
//

#include "Sheet.h"

/**
 * puts a new cell into the sheet
 * @param x
 * @param y
 * \param cell
 * \return returns self for method chaining
 */
Sheet &Sheet::put(size_t x, size_t y, const Cell &cell) {
    auto ptrToCell = cell.clone();
    std::pair<size_t, size_t> newCellCoordinates = std::make_pair(x, y);
    cellsByRow.emplace(newCellCoordinates, ptrToCell);
    cellsByColumn.emplace(newCellCoordinates, ptrToCell);
    return *this;
}

/**
 * prints a window set by parameters into console
 * @param x is a row index
 * @param y is a column index
 * @param width of window to be printed
 * \param height of window to be printed
 */
void Sheet::printSheet(size_t x, size_t y, size_t width, size_t height) {
    std::cout << std::endl;
    std::cout << "Printing cells sorted by row:" << std::endl;
    for (auto &cell : cellsByRow) {
        std::cout << "[" << cell.first.first << ":" << cell.first.second << "] " << *cell.second << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Printing cells sorted by column:" << std::endl;
    for (auto &cell : cellsByColumn) {
        std::cout << "[" << cell.first.first << ":" << cell.first.second << "] " << *cell.second << std::endl;
    }
}

/// comparison function for map of cells, sorting by row index
bool Sheet::cellsRowCompare::operator()(const std::pair<size_t, size_t> a, const std::pair<size_t, size_t> b) const {
    return a.first < b.first;
}

/// comparison function for map of cells, sorting by column index
bool Sheet::cellsColumnCompare::operator()(std::pair<size_t, size_t> a, std::pair<size_t, size_t> b) const {
    return a.second < b.second;
}