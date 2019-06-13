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
    std::stringstream ss;
    if (functionType == 4) {
        for (const auto &expTree : expTrees) {
            ss << expTree->evaluateString();
        }
        return ss.str();
    } else {
        std::string out = expTrees[0]->evaluateString();
        if (functionType == 1)
            ss << sin(std::stod(out));
        else if (functionType == 2)
            ss << cos(std::stod(out));
        else
            ss << abs(std::stod(out));
        return ss.str();
    }
}