#include <iostream>
#include <cstring>
#include <cstdlib>
#include <memory>
#include <set>
#include <map>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <ncurses.h>

using namespace std;

class Date {
public:
    Date(int year, int month, int day) : m_Year(year), m_Month(month), m_Day(day) {}

protected:
    int m_Year, m_Month, m_Day;
};

pair<int, int> getCellPos(const string &pos) {
    int column = 0;
    int row = 0;
    return make_pair(column, row);
};

// Cell
class Cell {
public:
    explicit Cell(const string &pos) {
        m_Column = getCellPos(pos).first;
        m_Row = getCellPos(pos).second;
    }

    virtual shared_ptr<Cell> clone() const = 0;

    virtual ~Cell() = default;

    // polymorphism (convert to Save Fromat & load from Save Fromat)
    // each child class will have a different convert and print function
    // f.e. A1=A3+A4 where A3=1 and A4=2, thus A1=3
    // we need to save A1=A3+A4 instead of the value 3
    // since if we load the cell back from a file and change the value of A3, A1 won't be changed
    virtual void convertToSF() const = 0;

    void loadFromSF() {

    };

    virtual ostream &print(ostream &os) const = 0;

    friend ostream &operator<<(ostream &os, const Cell &cell) {
        return cell.print(os);
    }

protected:
    int m_Column;
    int m_Row;
};

// Cell types
class CNumber : public Cell {
public:
    CNumber(const string &pos, double number) : Cell(pos) { m_Number = number; }

    shared_ptr<Cell> clone() const override {
        return make_shared<CNumber>(*this);
    }

    void convertToSF() const override;

    ostream &print(ostream &os) const override;

protected:
    double m_Number;
};

class CString : public Cell {
public:
    CString(const string &pos, const string &value) : Cell(pos) { m_String = value; }

    shared_ptr<Cell> clone() const override {
        return make_shared<CString>(*this);
    }

    void convertToSF() const override;

    ostream &print(ostream &os) const override;

protected:
    string m_String;
};

class CDate : public Cell {
public:
    CDate(const string &pos, const Date &date) : Cell(pos), m_Date(date) {}

    shared_ptr<Cell> clone() const override {
        return make_shared<CDate>(*this);
    }

    void convertToSF() const override;

    ostream &print(ostream &os) const override;

protected:
    Date m_Date;
};

class CFunction : public Cell {
public:
    CFunction(const string &pos, const string &function, double number) : Cell(pos) {}

    shared_ptr<Cell> clone() const override {
        return make_shared<CFunction>(*this);
    }

    void convertToSF() const override;

    ostream &print(ostream &os) const override;

protected:
    double m_Value;
    // set of other cells being linked to, will also contain itself for cycle prevention
    set<shared_ptr<Cell>> m_OtherCells;
};

// sorting functors

struct sortRows {
};
struct sortColumns {
};


// Sheet
class Sheet {
public:
    Sheet() = default;

    ~Sheet() = default;

    template<typename T>
    Sheet &put(const Cell &cell) {
        m_Sheet.emplace(make_pair(1, 1) , cell.clone());
        return *this;
    }

    void printSheet(int row, int column) {
        cout << "prints spreadsheet" << endl;
    }

    // loads/saves a spreadsheet from/to a file, returns false if there is any kind of error
    bool loadSheet(const char *fileName) {
        string fileNameStr = fileName;
        ifstream input_file(fileName, ios::binary | ios::in);
        return true;
    }

    bool saveSheet(const char *fileName) {
        return true;
    }

    Cell *getCell(const string &pos);

protected:
    // a map of cells, each cell has a pair of 2 numbers: row and column
    // each cell has a unique pair of row and column
    // using pointers for cell child access
    map<pair<unsigned, unsigned>, shared_ptr<Cell>> m_Sheet;
};

template<typename _T>
string toString(const _T &x) {
    ostringstream oss;
    oss << x;
    return oss.str();
}

int main() {
    cout << "This is my spreadsheet implementation." << endl;
    Sheet a;
    a.loadSheet("spreadsheet01.csv");
    // print the loaded spreadsheet from the file
    a.printSheet(10, 10);

    Sheet b;
    b.put(CNumber("A1", 12)).put(CString("B1", "hello"));
    b.printSheet(1, 2);
    // should print something like
    //   |  A  |  B  |
    //---+-----+-----+
    // 1 |   12|hello|
    //---+-----+-----+
    b.saveSheet("spreadsheet02.csv");
    b.put(CDate("C1", Date(1, 1, 2016)));
    b.put(CFunction("C2", "sin", 7));
    b.put(CFunction("C3", "abs", 7));
    b.put(CFunction("C4", "concat", 7));
    assert(toString(*b.getCell("A1")) == "12");
    b.getCell("A1") = b.getCell("C3") + b.getCell("C2");
    return 0;
}