//
// Created by Milan on 12.05.2019.
//

#ifndef SIMPLE_SPREADSHEET_SHEET_H
#define SIMPLE_SPREADSHEET_SHEET_H

#include "cell.h"
#include "textCell.h"
#include "memory"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "exp.h"
#include "expTerm.h"
#include "expNode.h"
#include "formulaCell.h"
#include "expFunction.h"
#include <fstream>
#include <algorithm>

class Sheet {
public:
    Sheet();

    ~Sheet() = default;

    Sheet &operator=(const Sheet &sheet);

    std::shared_ptr<Cell> addCell(std::pair<size_t, size_t> coordinates, std::shared_ptr<Cell> &ptrToCell);

    void put(size_t x, size_t y, const std::string &value);

    void updateCellRelations(std::pair<size_t, size_t> coordinates, std::shared_ptr<Cell> &ptrToCell);

    void updateDescendants(std::shared_ptr<Cell> &ptrToCell);

    std::shared_ptr<Exp> parseExpr(std::shared_ptr<Cell> &parentCell, const std::string &str);

    std::shared_ptr<Exp> makeExpFunction(int functionType, std::shared_ptr<Cell> &newCellPtr, const std::string &str);

    std::shared_ptr<Exp> makeCellReference(std::shared_ptr<Cell> &newCellPtr, const std::string &str);

    static std::string removeWhiteSpaces(const std::string &value);

    static bool isACellCoordinate(const std::string &str);

    int findFunction(const std::string &str);

    static std::pair<size_t, size_t> convertToCellCoordinate(const std::string &str);

    void save(const std::string &fileName);

    const std::map<std::pair<size_t, size_t>, std::shared_ptr<Cell>> &getCells() const;

    size_t getMaxRow() const;

    size_t getMaxColumn() const;

private:
    size_t maxRow;
    size_t maxColumn;
    std::map<std::pair<size_t, size_t>, std::shared_ptr<Cell>> cells;
    std::map<std::string, int> definedFunctions = {{"SIN",    1},
                                                   {"COS",    2},
                                                   {"ABS",    3},
                                                   {"CONCAT", 4}};
};


#endif //SIMPLE_SPREADSHEET_SHEET_H
