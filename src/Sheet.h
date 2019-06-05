//
// Created by Milan on 12.05.2019.
//

#ifndef SIMPLE_SPREADSHEET_SHEET_H
#define SIMPLE_SPREADSHEET_SHEET_H

#include "Cell.h"
#include "TextCell.h"
#include "memory"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Exp.h"
#include "ExpTerm.h"
#include "ExpNode.h"
#include "FormulaCell.h"
#include "ExpFunction.h"
#include <fstream>

class Sheet {
public:
    explicit Sheet(std::string name);

    ~Sheet() = default;

    std::shared_ptr<Cell> addCell(std::pair<size_t, size_t> coordinates, std::shared_ptr<Cell> &ptrToCell);

    void put(size_t x, size_t y, const std::string &value);

    void updateCellRelations(std::pair<size_t, size_t> coordinates, std::shared_ptr<Cell> &ptrToCell);

    void updateDescendants(std::shared_ptr<Cell> &ptrToCell);

    std::shared_ptr<Exp> parseExpr(std::shared_ptr<Cell> &parentCell, const std::string &str);

    static std::string removeWhiteSpaces(const std::string &value);

    static bool isACellCoordinate(const std::string &str);

    int findFunction(const std::string &str);

    static std::pair<size_t, size_t> convertToCellCoordinate(const std::string &str);

    void printSheet(size_t x, size_t y, size_t width, size_t height);

    // loads/saves a spreadsheet from/to a file, returns false if there is any kind of error
    bool loadSheet(const char *fileName) {
        return true;
    }

    bool saveSheet(const char *fileName);

private:
    std::string name;
    size_t maxRow;
    size_t maxColumn;
    std::map<std::pair<size_t, size_t>, std::shared_ptr<Cell>> cells;
    std::map<std::string, int> definedFunctions = {{"SIN", 1}, {"COS", 2}, {"ABS", 3}, {"CONCAT", 4}};
};


#endif //SIMPLE_SPREADSHEET_SHEET_H
