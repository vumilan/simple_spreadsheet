//
// Created by Milan Vu on 2019-06-01.
//

#ifndef SIMPLE_SPREADSHEET_FORMULACELL_H
#define SIMPLE_SPREADSHEET_FORMULACELL_H

#include "cell.h"
#include "exp.h"
#include "exp.h"
#include <memory>
#include <string>
#include <sstream>
#include "exceptions/notANumberException.h"
#include "exceptions/divisionByZeroException.h"
#include "exceptions/cycleException.h"
#include "exceptions/errorCellLinkException.h"

class FormulaCell : public Cell {
public:
    explicit FormulaCell(std::string formula);

    std::shared_ptr<Cell> clone() const override;

    std::ostream &print(std::ostream &os) const override;

    bool hasError() const override;

    void setExpTree(std::shared_ptr<Exp> &expTree) override;

    const std::string &value() const override;

private:
    std::shared_ptr<Exp> expTreeRoot = nullptr;
    std::string stringValue;
    bool error = false;
};


#endif //SIMPLE_SPREADSHEET_FORMULACELL_H
