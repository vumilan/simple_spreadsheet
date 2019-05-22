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
#include <map>
#include "Exp.h"
#include "ExpTerm.h"
#include "ExpNode.h"

class Sheet {
public:
    Sheet(const std::string &name);

    ~Sheet() = default;

    void addCell(std::pair<size_t, size_t> coordinates, const Cell &cell);

    void put(size_t x, size_t y, const std::string &value);

    //
    std::shared_ptr<Exp> parseExpr(const std::string &str);

//    Cell &cell(size_t x, size_t y);

    void printSheet(size_t x, size_t y, size_t width, size_t height);

    // loads/saves a spreadsheet from/to a file, returns false if there is any kind of error
    bool loadSheet(const char *fileName) {
        return true;
    }

    bool saveSheet(const char *fileName) {
        return true;
    }

private:
    std::string name;

    size_t maxRow;

    size_t maxColumn;

    std::map<std::pair<size_t, size_t>, std::shared_ptr<Cell>> cells;
};


#endif //SIMPLE_SPREADSHEET_SHEET_H
