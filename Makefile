CXX = g++
CFLAGS = -std=c++14 -Wall -g -Wextra -pedantic
OBJDIR = vumilan
OBJS =	$(addprefix $(OBJDIR)/, $(patsubst $(SRC)/%.cpp, %.o, $(wildcard $(SRC)/*.cpp)))
INC = include
SRC = src
LIB = lncurses
TARGET = main


.PHONY: all clean

all: clean $(OBJDIR) $(TARGET)
	@echo Done Building...

$(OBJDIR):
	@echo Making bin directory
	@mkdir $(OBJDIR)

$(OBJDIR)/%.o: $(SRC)/%.cpp
	@echo Building $@
	@$(CXX) $(CFLAGS) -c $< -o $@
	@echo Done Building $@


$(TARGET): $(OBJS)
	@echo Building executable $@
	@$(CXX) $(CFLAGS) -o $(OBJDIR)/$@ $^ -$(LIB)


clean:
	@echo Cleaning $(OBJDIR) $(TARGET) $(wildcard *.o)...
	@rm -f $(TARGET) $(wildcard *.o)
	@rm -rf $(OBJDIR)
	@echo Done Cleaning...

run:
	@./$(OBJDIR)/main
