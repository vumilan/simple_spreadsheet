//
// Created by Milan Vu on 2019-05-22.
//

#include "expNode.h"

/**
 * Constructor of node expression
 * @param op
 * @param left
 * @param right
 */
ExpNode::ExpNode(char op, std::shared_ptr<Exp> left, std::shared_ptr<Exp> right)
        : op(op), leftExpr(std::move(left)), rightExpr(std::move(right)) {

}

/**
 * Creates parent type pointer to this
 * @return shared_ptr<Exp>
 */
std::shared_ptr<Exp> ExpNode::clone() const {
    return std::make_shared<ExpNode>(ExpNode(*this));
}

/**
 * Evaluate numeric value of this node expression
 * @return double
 */
double ExpNode::evaluate() const {
    if (op == '+') {
        return leftExpr->evaluate() + rightExpr->evaluate();
    } else if (op == '-')
        return leftExpr->evaluate() - rightExpr->evaluate();
    else if (op == '*')
        return leftExpr->evaluate() * rightExpr->evaluate();
    // op == '/' here
    double rightNumber = rightExpr->evaluate();
    if (rightNumber == 0)
        throw DivisionByZeroException();
    return leftExpr->evaluate() / rightExpr->evaluate();
}

/**
 * Erase leading zeroes from a string
 * @param string
 * @return string
 */
std::string ExpNode::deleteUselessZeroes(const std::string &str) {
    size_t pos, i;
    if ((pos = str.find('.')) == std::string::npos)
        return str;
    std::string tmp = str.substr(pos);
    for (i = tmp.size() - 1; i >= 0; --i) {
        if (tmp[i] != '0' && tmp[i] != '.')
            break;
    }
    return str.substr(0, pos + i + 1);
}

/**
 * Evaluate string value of this node expression
 * @return string
 */
std::string ExpNode::evaluateString() const {
    return deleteUselessZeroes(std::to_string(this->evaluate()));
}