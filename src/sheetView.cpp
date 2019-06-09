//
// Created by Milan Vu on 2019-06-08.
//

#include "sheetView.h"

SheetView::SheetView(Sheet &sheet) {
    initscr();
    noecho();

    win = newwin(maxRow + 3, maxColumn * cellLen + cellLen, 0, 0);
    scrollok(win, TRUE);
    keypad(win, TRUE);
    wmove(win, 0, 0);
    curs_set(0);
    this->sheet = sheet;
    updateCellValueView({1, 1});
}

SheetView::~SheetView() {
    exitSheet();
}

std::string SheetView::headerLetter(int colNum) {
    char a[2] = {'@', '@'};
    std::string str;
    colNum++;
    if (colNum <= 26) {
        str += static_cast<char>(a[0] + colNum);
    } else if (colNum > 26 && colNum <= 52) {
        str += static_cast<char>(a[0] + 1);
        str += static_cast<char>(a[1] + (colNum - 26));
    } else if (colNum > 52 && colNum <= 78) {
        str += static_cast<char>(a[0] + 2);
        str += static_cast<char>(a[1] + (colNum - 52));
    } else if (colNum > 78 && colNum <= 104) {
        str += static_cast<char>(a[0] + 3);
        str += static_cast<char>(a[1] + (colNum - 78));
    }

    return str;
}

void SheetView::drawHeader() {
    std::string str;
    attr_t old_attr;
    short old_pair;
    int size = cellLen;
    // saves old styles
    wattr_get(win, &old_attr, &old_pair, nullptr);
    // apply new style
    wattron(win, A_STANDOUT);

    // Cell information
    mvwaddstr(win, 0, 0, "Cell coordinates:");

    mvwaddstr(win, 1, 0, "Cell formula:");

    mvwaddstr(win, 2, 0, "Cell value:");

    // Print header row
    for (size_t i = 0; i < maxColumn * cellLen; i++) {
        wmove(win, 4, cellLen + i);
        if (i != 0 && i % cellLen == cellLen / 2) {
            str = headerLetter(i / cellLen);
            waddstr(win, str.c_str());
        } else {
            waddstr(win, " ");
        }
    }

    // Print header column
    for (size_t i = 0; i < maxRow; i++) {
        wmove(win, i + 5, 0);
        if (i == 9)size--;
        for (int j = 0; j < size; j++) {
            if (j == cellLen / 2) {
                wprintw(win, "%d", i + 1);
            } else {
                waddch(win, ' ');
            }
        }
    }
    // applies back old styles
    wattr_set(win, old_attr, old_pair, nullptr);
}

std::string SheetView::fillHashtags(size_t len) {
    std::string out;
    for (size_t i = 0; i < len; i++) {
        out += '#';
    }
    return out;
}

std::string SheetView::fillSpaces(size_t len) {
    std::string out;
    for (size_t i = 0; i < len; i++) {
        out += ' ';
    }
    return out;
}

void SheetView::drawSheet() {
    size_t col = firstCellCoordinates.first, row = firstCellCoordinates.second;
    for (size_t y = 1; y <= sheet.getMaxRow(); ++y) {
        for (size_t x = 1; x <= sheet.getMaxColumn(); ++x) {
            auto iter = sheet.getCells().find(std::make_pair(x, y));
            if (iter == sheet.getCells().end())
                mvwaddstr(win, row, col, fillSpaces(cellLen).c_str());
            else {
                if (iter->second->value().size() > cellLen)
                    mvwaddstr(win, row, col, fillHashtags(cellLen).c_str());
                else {
                    mvwaddstr(win, row, col, fillSpaces(cellLen).c_str());
                    mvwaddstr(win, row, col, iter->second->value().c_str());
                }
            }
            col += cellLen;
        }
        row++, col = firstCellCoordinates.first;
    }
}

//std::string SheetView::columnNumberToStr(size_t colNum) {
//
//}

void SheetView::updateCellValueView(std::pair<size_t, size_t> cursorPos) {
//    wmove(win, cursorToCoordinates.second, cursorToCoordinates.first);
    std::stringstream ss;
    ss << cursorPos.first << ":" << cursorPos.second;
    if (ss.str().size() > maxInfoCellWidth)
        mvwaddstr(win, cursorToCoordinates.second, cursorToCoordinates.first, fillHashtags(maxInfoCellWidth).c_str());
    else {
        mvwaddstr(win, cursorToCoordinates.second, cursorToCoordinates.first, fillSpaces(maxInfoCellWidth).c_str());
        mvwaddstr(win, cursorToCoordinates.second, cursorToCoordinates.first, ss.str().c_str());
    }
    auto sheetIter = sheet.getCells().find(cursorPos);
    std::string formula, value;
    if (sheetIter != sheet.getCells().end()) {
        formula = sheetIter->second->formula();
        value = sheetIter->second->value();
    }
    if (formula.size() > maxInfoCellWidth)
        mvwaddstr(win, cursorToFormula.second, cursorToFormula.first, fillHashtags(maxInfoCellWidth).c_str());
    else {
        mvwaddstr(win, cursorToFormula.second, cursorToFormula.first, fillSpaces(maxInfoCellWidth).c_str());
        mvwaddstr(win, cursorToFormula.second, cursorToFormula.first, formula.c_str());
    }
    if (value.size() > maxInfoCellWidth)
        mvwaddstr(win, cursorToValue.second, cursorToValue.first, fillHashtags(maxInfoCellWidth).c_str());
    else {
        mvwaddstr(win, cursorToValue.second, cursorToValue.first, fillSpaces(maxInfoCellWidth).c_str());
        mvwaddstr(win, cursorToValue.second, cursorToValue.first, value.c_str());
    }
}

void SheetView::writingInCell(std::pair<size_t, size_t> cursorPos, const std::string &str) {
    mvwaddstr(win, cursorPos.second - 1 + firstCellCoordinates.second, (cursorPos.first - 1) * cellLen + firstCellCoordinates.first, str.c_str());
    drawSheet();
}

WINDOW *SheetView::getWin() {
    return win;
}

void SheetView::exitSheet() {
    delwin(win);
    endwin();
}

const std::pair<size_t, size_t> &SheetView::getFirstCellCoordinates() const {
    return firstCellCoordinates;
}

Sheet &SheetView::getSheet() {
    return sheet;
}

size_t SheetView::getMaxRow() const {
    return maxRow;
}

size_t SheetView::getMaxColumn() const {
    return maxColumn;
}
