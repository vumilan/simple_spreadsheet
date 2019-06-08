//
// Created by Milan on 12.05.2019.
//

#ifndef SIMPLE_SPREADSHEET_TEXTCELL_H
#define SIMPLE_SPREADSHEET_TEXTCELL_H

#include "string"
#include "cell.h"
#include <memory>
#include <string>
#include <iostream>


class TextCell : public Cell {
public:
    TextCell(std::string formula, std::string value);

    std::shared_ptr<Cell> clone() const override;

    std::ostream &print(std::ostream &os) const override;

    const std::string &value() const override;

private:
    std::string stringValue;
};

#endif //SIMPLE_SPREADSHEET_TEXTCELL_H
