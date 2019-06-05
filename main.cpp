#include <iostream>
#include "src/Sheet.h"
#include "src/TextCell.h"
#include "src/DateCell.h"

using namespace std;

int main() {
    cout << "Simple spreadsheet v0.0.0.0.0.1" << endl;
    Sheet a("first sheet");
    a.loadSheet("spreadsheet01.csv");

    a.put(1, 1, "10");
    a.put(1, 2, "=A1+10");
    a.put(1, 3, "=A2+15");
    a.put(1, 4, "=A3+A2+A1");
    a.put(1, 5, "=A4+13");
    a.put(1, 6, "=A5+13+C3");
    a.put(1, 7, "=A4");
    a.put(1, 1, "=A7");
    a.put(1, 1, "LAKATOS");
    a.put(3, 3, "=3*10-20/A1");
    a.put(4, 4, "=20+SIN(A1+2+(2+2))");
    a.put(5, 4, "=CONCAT(A1, 3040, 2+3+SIN(10), kslakad)");
    a.put(4, 5, "=(3+(2))");
    a.put(1, 1, "=20");
    a.put(1, 1, "=");
    a.put(1, 1, "");
    a.put(3, 3, "=CONCAT(E4,A2)");
    // print the loaded spreadsheet from the file
    a.printSheet(10, 10, 10, 10);
    return 0;
}