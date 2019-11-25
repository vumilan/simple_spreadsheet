#include <iostream>
#include "sheet.h"
#include "textCell.h"
#include "sheetController.h"

using namespace std;

Sheet load(const std::string &fileName) {
    std::ifstream file;
    file.open("examples/" + fileName);
    Sheet newSheet;
    std::string line, token;
    size_t y = 1;
    while (getline(file, line)) { // check every getline
        size_t x = 1, pos;
        // tokenize line
        while ((pos = line.find(';')) != std::string::npos) {
            token = line.substr(0, pos);
            line.erase(0, pos + 1);
            if (!token.empty())
                newSheet.put(x, y, token);
            ++x;
        }
        ++y;
    }
    return newSheet;
}

int main() {

    cout << "Simple spreadsheet v1.0 by Milan Vu" << endl;
    cout << "Press the key 'c' to create a new sheet." << endl;
    cout << "Press the key 'l' to load a sheet." << endl;
    cout << "Press the key 'x' to exit." << endl;
    char key;
    while (cin >> key) {
        if (key == 'c') {
            Sheet newSheet;
            SheetController().run(newSheet);
            return 0;
        } else if (key == 'l') {
            cout << "Enter the name of the sheet being loaded (from examples):" << endl;
            std::string sheetName;
            while (std::getline(std::cin, sheetName)) {
                if (!sheetName.empty()) {
                    Sheet newSheet = load(sheetName);
                    SheetController().run(newSheet);
                    return 0;
                }
            }
            return 0;
        } else if (key == 'x')
            return 0;
        else {
            cout << "Incorrect key, please try again." << endl;
        }
    }
    return 0;
}