//
// Created by Milan Vu on 2019-06-01.
//

#include "formulaCell.h"

/**
 * Constructor of formula cell
 * @param formula
 */
FormulaCell::FormulaCell(std::string formula) : Cell(std::move(formula)) {}

/**
 * Creates parent type pointer to this
 * @return shared_ptr<Cell>
 */
std::shared_ptr<Cell> FormulaCell::clone() const {
    return std::make_shared<FormulaCell>(FormulaCell(*this));
}

/**
 * Prints formula and cell value into ostream
 * @param os
 * @return ostream
 */
std::ostream &FormulaCell::print(std::ostream &os) const {
    os << stringValue;
    return os;
}

/**
 * Sets a newly created expression tree to this cell
 * Called when a formula cell is being created or being updated
 * This method also catches all defined exceptions and sets the cell value accordingly
 * @param expTree
 */
void FormulaCell::setExpTree(std::shared_ptr<Exp> &expTree) {
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

/**
 * Getter of the information whether this cell has an error
 * @return bool
 */
bool FormulaCell::hasError() const {
    return error;
}

/**
 * Getter of the value of this cell
 * @return string
 */
const std::string &FormulaCell::value() const {
    return stringValue;
}