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
//    Sheet a;
//
//    a.put(1, 1, "20");
//    a.put(1, 2, "=A1+10");
//    a.put(1, 1, "10");
//    a.put(1, 3, "=A2+15");
//    a.put(1, 4, "=A3+A2+A1");
//    a.put(1, 5, "=A4+13");
//    a.put(1, 6, "=A5+13+C3");
//    a.put(1, 7, "=A4");
//    a.put(1, 1, "=A7");
//    a.put(1, 1, "LAKATOS");
//    a.put(3, 3, "=3*10-20/A1");
//    a.put(4, 4, "=20+SIN(A1+2+(2+2))");
//    a.put(5, 4, "=CONCAT(A, 3040, B)");
//    a.put(4, 5, "=(3+(2))");
//    a.put(1, 1, "=20");
//    a.put(1, 1, "=");
//    a.put(1, 1, "");
//    a.put(3, 3, "=CONCAT(E4,A2,CONCAT(E4, E4, E4))");
//    a.save("sheet3.csv");

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