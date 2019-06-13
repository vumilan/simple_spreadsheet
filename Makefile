SOURCE_DIR = src
DOC_DIR = doc
BIN = vumilan
CXX = g++
RM = rm
CXXFLAGS = -std=c++14 -pedantic -Wall -Wno-long-long
LIB = -lncurses

.PHONY: all clean

all: main.o cell.o textCell.o formulaCell.o exp.o expFunction.o expNode.o expTerm.o sheet.o sheetController.o sheetView.o

main.o: $(SOURCE_DIR)/main.cpp
	@echo Building main.o
	@$(CXX) -c -o main.o $(CXXFLAGS) $^
	@echo Done

cell.o: $(SOURCE_DIR)/cell.cpp
	@echo Building cell.o
	@$(CXX) -c -o cell.o $(CXXFLAGS) $^
	@echo Done

textCell.o: $(SOURCE_DIR)/textCell.cpp
	@echo Building textCell.o
	@$(CXX) -c -o textCell.o $(CXXFLAGS) $^
	@echo Done

formulaCell.o: $(SOURCE_DIR)/formulaCell.cpp
	@echo Building formulaCell.o
	@$(CXX) -c -o formulaCell.o $(CXXFLAGS) $^
	@echo Done

exp.o: $(SOURCE_DIR)/exp.cpp
	@echo Building exp.o
	@$(CXX) -c -o exp.o $(CXXFLAGS) $^
	@echo Done

expFunction.o: $(SOURCE_DIR)/expFunction.cpp
	@echo Building expFunction.o
	@$(CXX) -c -o expFunction.o $(CXXFLAGS) $^
	@echo Done

expNode.o: $(SOURCE_DIR)/expNode.cpp
	@echo Building expNode.o
	@$(CXX) -c -o expNode.o $(CXXFLAGS) $^
	@echo Done

expTerm.o: $(SOURCE_DIR)/expTerm.cpp
	@echo Building expTerm.o
	@$(CXX) -c -o expTerm.o $(CXXFLAGS) $^
	@echo Done

sheet.o: $(SOURCE_DIR)/sheet.cpp
	@echo Building sheet.o
	@$(CXX) -c -o sheet.o $(CXXFLAGS) $^
	@echo Done

sheetController.o: $(SOURCE_DIR)/sheetController.cpp
	@echo Building sheetController.o
	@$(CXX) -c -o sheetController.o $(CXXFLAGS) $^
	@echo Done

sheetView.o: $(SOURCE_DIR)/sheetView.cpp
	@echo Building sheetView.o
	@$(CXX) -c -o sheetView.o $(CXXFLAGS) $^
	@echo Done

compile: all
	@echo Building executable
	@$(CXX) $(LIB) -o $(BIN) main.o cell.o textCell.o formulaCell.o exp.o expFunction.o expNode.o expTerm.o sheet.o sheetController.o sheetView.o
	@echo Done

clean:
	@echo Cleaning objects...
	@rm *.o $(BIN)
	@rm -rf doc
	@echo Done cleaning

run:
	@./$(BIN)

doc:
	doxygen Doxyfile
