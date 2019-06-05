//
// Created by Milan Vu on 2019-06-01.
//

#ifndef SIMPLE_SPREADSHEET_FORMULACELL_H
#define SIMPLE_SPREADSHEET_FORMULACELL_H

#include "Cell.h"
#include "Exp.h"
#include "Exp.h"
#include <memory>
#include <string>
#include <sstream>
#include "exceptions/NotANumberException.h"
#include "exceptions/DivisionByZeroException.h"
#include "exceptions/CycleException.h"
#include "exceptions/ErrorCellLinkException.h"

class FormulaCell : public Cell {
public:
    explicit FormulaCell(std::string formula);

    std::shared_ptr<Cell> clone() const override;

    std::string convertToSF() const override;

    std::ostream &print(std::ostream &os) const override;

    bool hasError() const override {
        return error;
    }

    void setExpTree(std::shared_ptr<Exp> &expTree) override {
        expTreeRoot = expTree;
        if (expTreeRoot) {
            try {
                stringValue = expTreeRoot->evaluateString();
                error = false;
            }
            catch (DivisionByZeroException &e) {
                stringValue = "#DIV/0!";
                error = true;
            }
            catch (CycleException &e) {
                stringValue = "#CYCLE!";
                error = true;
            }
            catch (NotANumberException &e) {
                stringValue = "#VALUE!";
                error = true;
            }
            catch (ErrorCellLinkException &e) {
                stringValue = "#LINK!";
                error = true;
            }
            catch (...) {
                stringValue = "#ERROR!";
                error = true;
            }
        } else {
            stringValue = "#FORMULA!";
            error = true;
        }
    }

    const std::string &value() const override {
        return stringValue;
    }

private:
    std::shared_ptr<Exp> expTreeRoot = nullptr;
    std::string stringValue;
    bool error = false;
};


#endif //SIMPLE_SPREADSHEET_FORMULACELL_H
