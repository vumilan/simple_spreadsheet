//
// Created by Milan Vu on 2019-06-04.
//

#include "expFunction.h"

/**
 * Constructor of function expression which takes one expression tree
 * For functions such as: SIN, COS, ABS
 * @param functionType
 * @param expTree
 */
ExpFunction::ExpFunction(int functionType, std::shared_ptr<Exp> &expTree) : functionType(functionType) {
    expTrees.push_back(expTree);
}

/**
 * Constructor of function expression which takes a vector of expression trees
 * For functions such as: CONCAT
 * @param functionType
 * @param expTrees
 */
ExpFunction::ExpFunction(int functionType, std::vector<std::shared_ptr<Exp>> &expTrees) : functionType(functionType),
                                                                                          expTrees(expTrees) {
}

/**
 * Creates parent type pointer to this
 * @return shared_ptr<Exp>
 */
std::shared_ptr<Exp> ExpFunction::clone() const {
    return std::make_shared<ExpFunction>(ExpFunction(*this));
}

/**
 * Evaluate numeric value of this function expression
 * @return double
 */
double ExpFunction::evaluate() const {
    return std::stod(this->evaluateString());
}

/**
 * Evaluate string value of this function expression
 * @return string
 */
std::string ExpFunction::evaluateString() const {
    std::string strOut;
    if (functionType == 4) {
        for (const auto &expTree : expTrees) {
            strOut += expTree->evaluateString();
        }
        return strOut;
    } else {
        strOut = expTrees[0]->evaluateString();
        if (functionType == 1) {
            return std::to_string(sin(std::stod(strOut)));
        } else if (functionType == 2) {
            return std::to_string(cos(std::stod(strOut)));
        } else {
            return std::to_string(abs(std::stod(strOut)));
        }
    }
}