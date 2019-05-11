//
// Created by Milan on 12.05.2019.
//

#ifndef SIMPLE_SPREADSHEET_FUNCTIONCELL_H
#define SIMPLE_SPREADSHEET_FUNCTIONCELL_H


#include "Cell.h"
#include <memory>
#include <string>

class FunctionCell : public Cell {
public:
    FunctionCell(const std::string &function, double number) : value(number) {}

    std::shared_ptr<Cell> clone() const override;

//    void convertToSF() const override;
//
//    std::ostream &print(std::ostream &os) const override;

protected:
    double value;
};


#endif //SIMPLE_SPREADSHEET_FUNCTIONCELL_H
