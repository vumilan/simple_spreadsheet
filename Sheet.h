//
// Created by Milan on 12.05.2019.
//

#ifndef SIMPLE_SPREADSHEET_SHEET_H
#define SIMPLE_SPREADSHEET_SHEET_H

#include "Cell.h"
#include "memory"
#include <iostream>
#include <string>
#include <map>

class Sheet {
public:
    Sheet() = default;

    ~Sheet() = default;

    template<typename T>
    Sheet &put(const Cell &cell) {
        cells.emplace(std::make_pair(1, 1), cell.clone());
        return *this;
    }

    void printSheet(int row, int column) {
        std::cout << "prints spreadsheet" << std::endl;
    }

    // loads/saves a spreadsheet from/to a file, returns false if there is any kind of error
    bool loadSheet(const char *fileName) {
        return true;
    }

    bool saveSheet(const char *fileName) {
        return true;
    }

protected:
    // a map of cells, each cell has a pair of 2 numbers: row and column
    // each cell has a unique pair of row and column
    // using pointers for cell child access
    std::map<std::pair<unsigned, unsigned>, std::shared_ptr<Cell>> cells;
};


#endif //SIMPLE_SPREADSHEET_SHEET_H
