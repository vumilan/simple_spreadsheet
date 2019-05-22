//
// Created by Milan on 12.05.2019.
//

#ifndef SIMPLE_SPREADSHEET_FUNCTIONCELL_H
#define SIMPLE_SPREADSHEET_FUNCTIONCELL_H


#include "Cell.h"
#include <memory>
#include <string>
#include <iomanip>
#include <map>
#include <string>
#include <vector>

class FunctionCell : public Cell {
public:
    FunctionCell(const std::string &cellValue, const std::string &function, size_t number);

    std::shared_ptr<Cell> clone() const override;

    std::string convertToSF() const override;

    std::ostream &print(std::ostream &os) const override;

private:
    std::map<std::string, size_t> functionStrings = { {"sin", 0}, {"cos", 1}, {"concat", 2}, {"abs", 3} };
    size_t number;
    std::vector<std::string> texts;
    size_t function;
};


#endif //SIMPLE_SPREADSHEET_FUNCTIONCELL_H
