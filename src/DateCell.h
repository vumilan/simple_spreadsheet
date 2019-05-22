//
// Created by Milan on 12.05.2019.
//

#ifndef SIMPLE_SPREADSHEET_DATECELL_H
#define SIMPLE_SPREADSHEET_DATECELL_H

#include "Date.h"
#include "Cell.h"
#include <memory>
#include <string>

class DateCell : public Cell {
public:
    DateCell(const std::string &cellValue, const Date &date);

    std::shared_ptr<Cell> clone() const override;

    std::string convertToSF() const override;

    std::ostream &print(std::ostream &os) const override;

private:
    Date date;
};


#endif //SIMPLE_SPREADSHEET_DATECELL_H
