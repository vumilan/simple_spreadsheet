//
// Created by Milan Vu on 2019-06-08.
//

#ifndef SIMPLE_SPREADSHEET_SHEETCONTROLLER_H
#define SIMPLE_SPREADSHEET_SHEETCONTROLLER_H

#include "sheetView.h"
#include <ncurses.h>

class SheetController{

public:

    SheetController();
    ~SheetController() = default;

    void moveLeft(WINDOW* win);
    void moveRight(WINDOW* win);
    void moveUp(WINDOW* win);
    void moveDown(WINDOW* win);
    void openEditor(Sheet &sheet, std::pair<size_t, size_t> cursor);
    void pressEnter(Sheet &sheet, std::pair<size_t, size_t> cursor);
    void pressBackspace(Sheet &sheet, std::pair<size_t, size_t> cursor);

    void handleInput(WINDOW* win, std::pair<size_t, size_t> cursor, Sheet &sheet, int ch);
    bool validateFormula(std::string formula);
    void parseCell(WINDOW* win, std::pair<size_t, size_t> cursor, Sheet &sheet);

    void run(Sheet &sheet);

private:
    int row, col;
    const int maxCol = 80;
    const int maxRow = 23;
    const int maxCellSize = 8;




};


#endif //SIMPLE_SPREADSHEET_SHEETCONTROLLER_H
