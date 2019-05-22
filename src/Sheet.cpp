//
// Created by Milan on 12.05.2019.
//

#include "Sheet.h"
#include "NumberCell.h"

/// constructor that initializes Sheet class with a name, maxRow and maxColumn set to default 1
Sheet::Sheet(const std::string &name) : name(name), maxRow(1), maxColumn(1) {}

void Sheet::addCell(std::pair<size_t, size_t> coordinates, const Cell &cell) {
    auto ptrToCell = cell.clone();
    auto cellsIter = cells.find(coordinates);
    // if cell at coordinates is empty
    if (cellsIter == cells.end()) {
        cells.emplace(coordinates, ptrToCell);
    } else {
        cellsIter->second = ptrToCell;
    }
}

/**
 * Recursive descent parser algorithm
 * https://en.wikipedia.org/wiki/Recursive_descent_parser
 * @param str
 * @return shared_ptr<Exp>
 */

std::shared_ptr<Exp> Sheet::parseExpr(const std::string &str) {
    int level = 0;//inside parentheses check
    //case + or -
    //most right '+' or '-' (but not inside '()') search and split
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
        if ((c == '+' || c == '-') && i != 0) {//if i==0 then s[0] is sign
            std::string left(str.substr(0, i));
            std::string right(str.substr(i + 1));
            return ExpNode(c, parseExpr(left), parseExpr(right)).clone();
        }
    }
    //case * or /
    //most right '*' or '/' (but not inside '()') search and split
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
            return ExpNode(c, parseExpr(left), parseExpr(right)).clone();
        }
    }
    if (str[0] == '(') {
        //case ()
        //pull out inside and to strToExp
        for (int i = 0; i < str.size(); ++i) {
            if (str[i] == '(') {
                ++level;
                continue;
            }
            if (str[i] == ')') {
                --level;
                if (level == 0) {
                    std::string exp(str.substr(1, i - 1));
                    return parseExpr(exp);
                }
                continue;
            }
        }
    } else
        //case value
        return ExpTerm(str).clone();
    std::cerr << "Error:never execute point" << std::endl;
    return nullptr;//never
}

void Sheet::put(size_t x, size_t y, const std::string &value) {
    std::pair<size_t, size_t> coordinates = std::make_pair(x, y);
    // remove whitespaces from string value
    std::string str = value;
    str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
    if (str[0] == '=') {
        parseExpr(str.substr(1))->print();
    } else {
        // check if string value is convertible to number
        char *pEnd = nullptr;
        double number = std::strtod(str.c_str(), &pEnd);
        if (*pEnd) { // can't convert to number
            // TODO check if string is of date format
            addCell(coordinates, TextCell(value, value));
            return;
        } else {
            addCell(coordinates, NumberCell(value, number));
            return;
        }

    }
}

//Cell &Sheet::cell(size_t x, size_t y) {
//    auto foundCellIter = cellsByRow.find(std::make_pair(x, y));
//    if (foundCellIter == cellsByRow.end()) {
//        TextCell tmp = TextCell("", "");
//        return this->put(x, y, tmp);
//    }
//    else {
//        return *(foundCellIter->second);
//    }
//}

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