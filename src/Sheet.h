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

    Sheet &put(size_t x, size_t y, const Cell &cell);

    void printSheet(size_t x, size_t y, size_t width, size_t height);

    // loads/saves a spreadsheet from/to a file, returns false if there is any kind of error
    bool loadSheet(const char *fileName) {
        return true;
    }

    bool saveSheet(const char *fileName) {
        return true;
    }

private:
    struct cellsRowCompare {
        bool operator()(std::pair<size_t, size_t> a, std::pair<size_t, size_t> b) const;
    };

    struct cellsColumnCompare {
        bool operator()(std::pair<size_t, size_t> a, std::pair<size_t, size_t> b) const;
    };

    /// using two maps, each sorted by either row or column for better runtime
    std::map<std::pair<size_t, size_t>, std::shared_ptr<Cell>, cellsRowCompare> cellsByRow;
    std::map<std::pair<size_t, size_t>, std::shared_ptr<Cell>, cellsColumnCompare> cellsByColumn;
};


#endif //SIMPLE_SPREADSHEET_SHEET_H
