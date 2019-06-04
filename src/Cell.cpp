//
// Created by Milan on 11.05.2019.
//

#include "Cell.h"

/**
 * constructor of abstract class Cell
 *
 * @param value
 */
Cell::Cell(std::string formula) : formulaValue(std::move(formula)) {}

/**
 * operator << to call print of child classes
 *
 * @param os
 * @param cell
 * @return
 */
std::ostream &operator<<(std::ostream &os, const Cell &cell) {
    os << cell.formulaValue << ": ";
    return cell.print(os);
}

/**
 * Replace cell in cell relations
 * @param thisPtr
 */
void Cell::replaceFromRelations(std::shared_ptr<Cell> &thisPtr, std::shared_ptr<Cell> &newPtr) {
    for (const auto &ancestor : ancestorCells) {
        ancestor->descendantCells.erase(thisPtr);
        ancestor->descendantCells.insert(newPtr);
    }
    for (const auto &descendant : descendantCells) {
        descendant->ancestorCells.erase(thisPtr);
        descendant->ancestorCells.insert(newPtr);
    }
}

/**
 * Update relations between cells
 * Cell inherits all ancestors from ancestorCell and each ancestor gains a new descendant Cell
 * Function also checks if a cycle is being created during the process: If one of the ancestor is himself,
 * there is something wrong going on in this family
 * @param ancestorCell
 * @param thisCell
 * @return bool
 */
bool Cell::updateCellRelations(std::shared_ptr<Cell> &ancestorCell, std::shared_ptr<Cell> &thisCell) {
    // check if cycle will be created
    if (&*ancestorCell == this)
        return false;
    for (const auto &ancestor : ancestorCell->getAncestorCells()) {
        if (&*ancestor == this)
            return false;
    }
    // update descendants for each ancestor and inherit all ancestors from an ancestor
    for (const auto &ancestor : ancestorCell->getAncestorCells()) {
        ancestorCells.insert(ancestor);
        ancestor->descendantCells.insert(thisCell);
    }
    ancestorCells.insert(ancestorCell);
    ancestorCell->descendantCells.insert(thisCell);
    return true;
}

/**
 * getter of descendantCells set
 * @return std::set<std::shared_ptr<Cell>>
 */
const std::set<std::shared_ptr<Cell>> &Cell::getDescendantCells() const {
    return descendantCells;
}

/**
 * setter of descendantCells set
 * @param newDescendantCells
 */
void Cell::setDescendantCells(const std::set<std::shared_ptr<Cell>> &newDescendantCells) {
    Cell::descendantCells = newDescendantCells;
}

/**
 * getter of ancestorCells set
 * @return std::set<std::shared_ptr<Cell>>
 */
const std::set<std::shared_ptr<Cell>> &Cell::getAncestorCells() const {
    return ancestorCells;
}

/**
 * setter of ancestorCells set
 * @param newAncestorCells
 */
void Cell::setAncestorCells(const std::set<std::shared_ptr<Cell>> &newAncestorCells) {
    Cell::ancestorCells = newAncestorCells;
}
