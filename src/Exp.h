//
// Created by Milan Vu on 2019-05-22.
//

#ifndef SIMPLE_SPREADSHEET_EXP_H
#define SIMPLE_SPREADSHEET_EXP_H

/**
 * Parent virtual class for the Recursive descent parser
 * The math expression taken from input is parsed into the cell as a tree
 */
class Exp {
public:
    virtual void print() const = 0;
    virtual std::shared_ptr<Exp> clone() const = 0;
    virtual ~Exp() = default;
};


#endif //SIMPLE_SPREADSHEET_EXP_H
