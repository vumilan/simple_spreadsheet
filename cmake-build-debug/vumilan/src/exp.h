//
// Created by Milan Vu on 2019-05-22.
//

#ifndef SIMPLE_SPREADSHEET_EXP_H
#define SIMPLE_SPREADSHEET_EXP_H

#include <memory>
#include <string>

/**
 * Parent virtual class for the Recursive descent parser
 * The math expression taken from input is parsed into the cell as a tree
 */
class Exp {
public:
    /**
     * Evaluates numeric value of the expression
     * Expression tree is being evaluated recursively
     * @return double
     */
    virtual double evaluate() const = 0;

    /**
     * Evaluates string value of the expression (since sheet supports operations of strings as well)
     * Expression tree is being evaluated recursively
     * @return string
     */
    virtual std::string evaluateString() const = 0;

    /**
     * Polymorphic function to clone child classes
     * @return pointer to child class which is the type of parent class
     */
    virtual std::shared_ptr<Exp> clone() const = 0;

    virtual ~Exp() = default;
};


#endif //SIMPLE_SPREADSHEET_EXP_H
