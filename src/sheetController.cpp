//
// Created by Milan Vu on 2019-06-08.
//

#include "sheetController.h"

SheetController::SheetController() {
    x = 1, y = 1;
}

void SheetController::moveLeft(SheetView &view) {
    if (x > 1)
        --x;
    view.updateCellValueView(std::make_pair(x, y));
}

void SheetController::moveRight(SheetView &view) {
    if (x < view.getMaxColumn())
        ++x;
    view.updateCellValueView(std::make_pair(x, y));
}

void SheetController::moveUp(SheetView &view) {
    if (y > 1)
        --y;
    view.updateCellValueView(std::make_pair(x, y));
}

void SheetController::moveDown(SheetView &view) {
    if (y < view.getMaxRow())
        ++y;
    view.updateCellValueView(std::make_pair(x, y));
}

void SheetController::pressedEnter(SheetView &view) {
    int enteredKey;
    std::string str;
    while ((enteredKey = wgetch(view.getWin())) != '\n') {
        if (enteredKey == KEY_BACKSPACE && !str.empty())
            str = str.substr(0, str.size() - 1);
        else
            str += (char) enteredKey;
        view.writingInCell(std::make_pair(x, y), str);
    }
    view.getSheet().put(x, y, str);
    view.updateCellValueView(std::make_pair(x, y));
    view.drawSheet();
}

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

        case KEY_BACKSPACE:

            break;

        case '\n':
        case KEY_ENTER:
            pressedEnter(view);
            break;

        default:
            break;
    }
}

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