//
// Created by Milan Vu on 2019-06-08.
//

#ifndef SIMPLE_SPREADSHEET_SHEETCONTROLLER_H
#define SIMPLE_SPREADSHEET_SHEETCONTROLLER_H

#include "sheetView.h"
#include <ncurses.h>

class SheetController {

public:

    SheetController();

    ~SheetController() = default;

    void moveLeft(SheetView &view);

    void moveRight(SheetView &view);

    void moveUp(SheetView &view);

    void moveDown(SheetView &view);

    void pressedEnter(SheetView &view);

    void handleInput(SheetView &view, int enteredKey);

    void run(Sheet &sheet);

private:
    size_t x;
    size_t y;


};


#endif //SIMPLE_SPREADSHEET_SHEETCONTROLLER_H
