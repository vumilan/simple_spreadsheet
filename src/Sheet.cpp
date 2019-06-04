//
// Created by Milan on 12.05.2019.
//

#include "Sheet.h"

/// constructor that initializes Sheet class with a name, maxRow and maxColumn set to default 1
Sheet::Sheet(std::string name) : name(std::move(name)), maxRow(1), maxColumn(1) {}

/**
 * Add cell into a sheet, if cell already exists, update all parents referencing from this cell
 * @param coordinates
 * @param ptrToCell
 * @return shared_ptr<Cell>
 */
std::shared_ptr<Cell> Sheet::addCell(std::pair<size_t, size_t> coordinates, std::shared_ptr<Cell> &ptrToCell) {
    auto cellsIter = cells.find(coordinates);
    // if cell at coordinates is empty
    if (cellsIter == cells.end()) {
        cells.emplace(coordinates, ptrToCell);
    } else {
        updateCellRelations(coordinates, ptrToCell);
        // replace new pointer with old one
        cellsIter->second = ptrToCell;
        // if there is some error with the added cell, compute no further

        if (ptrToCell->hasError()) {
            return ptrToCell;
        }
        // update expression tree for each descendant cell
        for (auto descendant : ptrToCell->getDescendantCells()) {
            std::shared_ptr<Exp> newExpTree;
            newExpTree = parseExpr(descendant, removeWhiteSpaces(descendant->formula()).substr(1));
            descendant->setExpTree(newExpTree);
        }
    }
    return ptrToCell;
}

void Sheet::updateCellRelations(std::pair<size_t, size_t> coordinates, std::shared_ptr<Cell> &ptrToCell) {
    auto cellsIter = cells.find(coordinates);
    if (cellsIter->second) {
        cellsIter->second->replaceFromRelations(cellsIter->second, ptrToCell);
        ptrToCell->setDescendantCells(cellsIter->second->getDescendantCells());
        ptrToCell->setAncestorCells(cellsIter->second->getAncestorCells());
    }
}

/**
 * Recursive descent parser algorithm for infix expressions
 * https://en.wikipedia.org/wiki/Recursive_descent_parser
 * converts expression in string into an expression tree
 * @param str
 * @return shared_ptr<Exp>
 */

std::shared_ptr<Exp> Sheet::parseExpr(std::shared_ptr<Cell> &newCellPtr, const std::string &str) {
    int level = 0;  // inside parentheses check
    // case + or -
    // most right '+' or '-' (but not inside '()') search and split
    for (int i = str.size() - 1; i >= 0; --i) {
        char c = str[i];
        if (c == ')') {
            ++level;
            continue;
        }
        if (c == '(') {
            --level;
            continue;
        }
        if (level > 0) continue;
        if ((c == '+' || c == '-') && i != 0) { // if i==0 then s[0] is sign
            std::string left(str.substr(0, i));
            std::string right(str.substr(i + 1));
            return ExpNode(c, parseExpr(newCellPtr, left), parseExpr(newCellPtr, right)).clone();
        }
    }
    // case * or /
    // most right '*' or '/' (but not inside '()') search and split
    for (int i = str.size() - 1; i >= 0; --i) {
        char c = str[i];
        if (c == ')') {
            ++level;
            continue;
        }
        if (c == '(') {
            --level;
            continue;
        }
        if (level > 0) continue;
        if (c == '*' || c == '/') {
            std::string left(str.substr(0, i));
            std::string right(str.substr(i + 1));
            return ExpNode(c, parseExpr(newCellPtr, left), parseExpr(newCellPtr, right)).clone();
        }
    }
    if (str[0] == '(') {
        // case ()
        // pull out inside and to strToExp
        for (int i = 0; i < str.size(); ++i) {
            if (str[i] == '(') {
                ++level;
                continue;
            }
            if (str[i] == ')') {
                --level;
                if (level == 0) {
                    std::string exp(str.substr(1, i - 1));
                    return parseExpr(newCellPtr, exp);
                }
                continue;
            }
        }
    } else {
        // case value or coordinate or function
        if (isACellCoordinate(str)) {
            std::pair<size_t, size_t> coordinates = convertToCellCoordinate(str);
            auto iter = cells.find(coordinates);
            // add empty cell if cell not found or return found cell
            auto emptyCell = TextCell("", "").clone();
            std::shared_ptr<Cell> ancestorCell = iter == cells.end() ? addCell(coordinates, emptyCell) : iter->second;
            // if cycle created
            if (!newCellPtr->updateCellRelations(ancestorCell, newCellPtr)) {
                return ExpTerm(true).clone();
            }
            return ExpTerm(ancestorCell).clone();
        } else if (isAFunction(str)) {

        } else {
            return ExpTerm(str).clone();
        }
    }
    // if formula is invalid
    return nullptr;
}

// remove whitespaces from string value
std::string Sheet::removeWhiteSpaces(const std::string &value) {
    std::string str = value;
    str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
    return str;
}

/**
 * Determine what type of cell to put into map of cells
 * @param x
 * @param y
 * @param value
 */
void Sheet::put(size_t x, size_t y, const std::string &value) {
    std::pair<size_t, size_t> coordinates = std::make_pair(x, y);
    std::shared_ptr<Cell> newCellPtr = nullptr;
    if (value[0] == '=') {
        newCellPtr = FormulaCell(value).clone();
        updateCellRelations(coordinates, newCellPtr);
        std::shared_ptr<Exp> expTree = parseExpr(newCellPtr, removeWhiteSpaces(value).substr(1));
        newCellPtr->setExpTree(expTree);
    } else {
        newCellPtr = TextCell(value, value).clone();
    }
    addCell(coordinates, newCellPtr);
}

/**
 * check if input string is a cell coordinate (AAA222 is a coordinate, A2B is not)
 * @param str
 * @return
 */
bool Sheet::isACellCoordinate(const std::string &str) {
    size_t i;
    for (i = 0; i <= str.size() - 1; ++i) {
        if (str[i] < 65 || str[i] > 90)
            break;
    }
    char *pEnd = nullptr;
    std::strtod(str.substr(i).c_str(), &pEnd);
    return i != 0 && !*pEnd && i < str.size();
}

/**
 * convert string to cell coordinate
 * @param str
 * @return
 */
std::pair<size_t, size_t> Sheet::convertToCellCoordinate(const std::string &str) {
    size_t x = 0, lastCol = 0, currentCol = 0;
    size_t i;
    for (i = 0; i <= str.size() - 1; ++i) {
        if (str[i] < 65 || str[i] > 90)
            break;
        lastCol *= 24;
        currentCol = str[i] - 64;
        x += lastCol;
        lastCol = currentCol;
    }
    x += currentCol;
    return std::make_pair(x, std::stoul(str.substr(i)));
}


bool Sheet::isAFunction(const std::string &str) {
    if (str.substr(0, 3) == "sin") {

    }
    return false;
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
    for (auto &cell : cells) {
        std::cout << "[" << cell.first.first << ":" << cell.first.second << "] " << *cell.second << std::endl;
    }
}

