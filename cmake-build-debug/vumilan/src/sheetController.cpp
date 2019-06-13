//
// Created by Milan Vu on 2019-06-08.
//

#include "sheetController.h"

/**
 * Constructor of SheetController
 * Holds the information where in the sheet the cursor is on
 */
SheetController::SheetController() {
    x = 1, y = 1;
}

/**
 * Move cursor to the left
 * @param view
 */
void SheetController::moveLeft(SheetView &view) {
    if (x > 1)
        --x;
    view.updateCellValueView({x, y});
}

/**
 * Move cursor to the right
 * @param view
 */
void SheetController::moveRight(SheetView &view) {
    if (x < view.getMaxColumn())
        ++x;
    view.updateCellValueView({x, y});
}

/**
 * Move cursor up
 * @param view
 */
void SheetController::moveUp(SheetView &view) {
    if (y > 1)
        --y;
    view.updateCellValueView({x, y});
}

/**
 * Move cursor down
 * @param view
 */
void SheetController::moveDown(SheetView &view) {
    if (y < view.getMaxRow())
        ++y;
    view.updateCellValueView({x, y});
}

/**
 * When enter is pressed, go into cell editing mode
 * @param view
 */
void SheetController::pressedEnter(SheetView &view) {
    int enteredKey;
    std::string str;
    auto cellIter = view.getSheet().getCells().find({x, y});
    if (cellIter != view.getSheet().getCells().end())
        str = cellIter->second->formula();
    view.writingInCell({x, y}, str);
    while ((enteredKey = wgetch(view.getWin())) != '\n') {
        if (enteredKey == 127) { // if backspace, erase last char
            if (!str.empty()) {
                str.pop_back();
                // print with a space to erase last char form window
                view.writingInCell({x, y}, str + ' ');
            }
        } else if (enteredKey > 31 && enteredKey < 127) { // if char is printable
            str += static_cast<char>(enteredKey);
            view.writingInCell({x, y}, str);
        }
    }
    view.getSheet().put(x, y, str);
    view.updateCellValueView({x, y});
    view.drawSheet();
}

/**
 * Handles control keys
 * @param view
 * @param enteredKey
 */
void SheetController::handleInput(SheetView &view, int enteredKey) {
    switch (enteredKey) {
        case KEY_LEFT:
            moveLeft(view);
            break;
        case KEY_RIGHT:
            moveRight(view);
            break;
        case KEY_UP:
            moveUp(view);
            break;
        case KEY_DOWN:
            moveDown(view);
            break;
        case '\n':
            pressedEnter(view);
            break;
        default:
            break;
    }
}

/**
 * Run class which creates sheetView and handles the whole process
 * @param sheet
 */
void SheetController::run(Sheet &sheet) {
    SheetView view(sheet);
    view.drawHeader();
    view.drawSheet();
    int enteredKey;
    while ((enteredKey = wgetch(view.getWin())) != 'q' && enteredKey != 's') {
        handleInput(view, enteredKey);
    }
    view.exitSheet();
    if (enteredKey == 's') {
        std::cout << "Enter a name for this sheet to be saved:" << std::endl;
        std::string sheetName;
        while (std::getline(std::cin, sheetName)) {
            if (!sheetName.empty()) {
                view.getSheet().save(sheetName);
                break;
            }
        }
    }
}