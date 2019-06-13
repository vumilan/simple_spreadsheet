//
// Created by Milan on 12.05.2019.
//

#include "sheet.h"

/// constructor that initializes Sheet class with maxRow and maxColumn set to default 1
Sheet::Sheet() : maxRow(1), maxColumn(1) {}

/// copy operator
Sheet &Sheet::operator=(const Sheet &sheet) = default;

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
        // update expression tree for each descendant cell if there is no error in cell
        updateDescendants(ptrToCell);
    }
    return ptrToCell;
}

/**
 * Refresh the expression tree of every descendant cell that referenced from the old cell
 * with the value of the new cell
 * @param ptrToCell
 */
void Sheet::updateDescendants(std::shared_ptr<Cell> &ptrToCell) {
    std::set<std::shared_ptr<Cell>> descendants = ptrToCell->getDescendantCells();
    for (auto descendant : descendants) {
        std::shared_ptr<Exp> newExpTree;
        newExpTree = parseExpr(descendant, removeWhiteSpaces(descendant->formula()).substr(1));
        descendant->setExpTree(newExpTree);
        // call recursively for each descendant
        updateDescendants(descendant);
    }
}

/**
 * Update cell relations when adding new cell
 * @param coordinates
 * @param ptrToCell
 */
void Sheet::updateCellRelations(std::pair<size_t, size_t> coordinates, std::shared_ptr<Cell> &ptrToCell) {
    auto cellsIter = cells.find(coordinates);
    if (cellsIter != cells.end()) {
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
    for (int i = static_cast<int>(str.size() - 1); i >= 0; --i) {
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
    for (int i = static_cast<int>(str.size() - 1); i >= 0; --i) {
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
        for (int i = 0; i < static_cast<int>(str.size()); ++i) {
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
        int functionType = findFunction(str);
        if (functionType != -1)
            return makeExpFunction(functionType, newCellPtr, str);
        else if (isACellCoordinate(str)) {
            return makeCellReference(newCellPtr, str);
        } else {
            return ExpTerm(str).clone();
        }
    }
    // if formula is invalid
    return nullptr;
}

/**
 * Helper function of parseExpr to control creation of function expression
 * @param functionType
 * @param newCellPtr
 * @param str
 * @return shared_ptr<Exp>
 */
std::shared_ptr<Exp>
Sheet::makeExpFunction(int functionType, std::shared_ptr<Cell> &newCellPtr, const std::string &str) {
    // extract string inside of function
    std::string insideFunction = str.substr(str.find('(') + 1, str.size() - str.find('(') - 2);
    // concat function
    if (functionType == 4) {
        std::vector<std::shared_ptr<Exp>> expTrees;
        size_t pos = 0;
        std::string token;
        // split the inside of concat function into tokens and create expression trees from each token
        while ((pos = insideFunction.find(',')) != std::string::npos) {
            // check if another CONCAT function is in token
            if (insideFunction.size() > 6 && insideFunction.substr(0, 7) == "CONCAT(" &&
                insideFunction.find(')') != std::string::npos)
                pos = insideFunction.find(')') + 1;
            token = insideFunction.substr(0, pos);
            expTrees.push_back(parseExpr(newCellPtr, token));
            insideFunction.erase(0, pos + 1);
        }
        expTrees.push_back(parseExpr(newCellPtr, insideFunction));
        return ExpFunction(functionType, expTrees).clone();
    }
    // if function is not concat
    auto newExpTree = parseExpr(newCellPtr, insideFunction);
    return ExpFunction(functionType, newExpTree).clone();
}

/**
 * Helper function of parseExpr to control creation of a cell reference expression
 * @param newCellPtr
 * @param str
 * @return shared_ptr<Exp>
 */
std::shared_ptr<Exp> Sheet::makeCellReference(std::shared_ptr<Cell> &newCellPtr, const std::string &str) {
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
}

/**
 * Remove whitespaces from a string
 * @param value
 * @return string
 */
std::string Sheet::removeWhiteSpaces(const std::string &value) {
    std::string str = value;
    std::string::iterator end_pos = std::remove(str.begin(), str.end(), ' ');
    str.erase(end_pos, str.end());
    return str;
}

/**
 * Determine what type of cell to put into map of cells
 * Also updates maxRow and maxColumn depending on the coordinates
 * @param x
 * @param y
 * @param value
 */
void Sheet::put(size_t x, size_t y, const std::string &value) {
    std::pair<size_t, size_t> coordinates = std::make_pair(x, y);
    std::shared_ptr<Cell> newCellPtr = nullptr;
    if (value[0] == '=' && value.size() > 1) {
        newCellPtr = FormulaCell(value).clone();
        updateCellRelations(coordinates, newCellPtr);
        std::shared_ptr<Exp> expTree = parseExpr(newCellPtr, removeWhiteSpaces(value).substr(1));
        newCellPtr->setExpTree(expTree);
    } else {
        newCellPtr = TextCell(value, value).clone();
    }
    addCell(coordinates, newCellPtr);
    // update max row and max column
    if (maxColumn < x)
        maxColumn = x;
    if (maxRow < y)
        maxRow = y;
}

/**
 * Check if input string is a cell coordinate (AAA222 is a coordinate, A2B is not)
 * @param str
 * @return bool
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
 * Convert string to cell coordinate
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

/**
 * Check if input string is a function with the right amount of parentheses
 * @param str
 * @return bool
 */
int Sheet::findFunction(const std::string &str) {
    if (str.size() > 3 && str[str.size() - 1] == ')') {
        std::string header = str.substr(0, str.find('('));
        auto findIter = definedFunctions.find(header);
        if (findIter == definedFunctions.end())
            return -1;
        return findIter->second;
    }
    return -1;
}

/**
 * Saves this sheet into a .csv file with given name
 * @param fileName
 */
void Sheet::save(const std::string &fileName) {
    std::ofstream newFile;
    newFile.open("examples/" + fileName);
    for (size_t y = 1; y <= maxRow; ++y) {
        for (size_t x = 1; x <= maxColumn; ++x) {
            auto cellsIter = cells.find(std::make_pair(x, y));
            if (cellsIter != cells.end())
                newFile << cellsIter->second->formula() << ';';
            else
                newFile << ';';
        }
        newFile << '\n';
    }
    std::cout << "File: " + fileName + " was saved into /examples." << std::endl;
    newFile.close();
}

/**
 * Getter of map of cells
 * @return map<std::pair<size_t, size_t>
 */
const std::map<std::pair<size_t, size_t>, std::shared_ptr<Cell>> &Sheet::getCells() const {
    return cells;
}

/**
 * Getter of maxRow
 * @return size_t
 */
size_t Sheet::getMaxRow() const {
    return maxRow;
}

/**
 * Getter of maxColumn
 * @return size_t
 */
size_t Sheet::getMaxColumn() const {
    return maxColumn;
}
