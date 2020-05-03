LIB_DIR = src/lib
OBJ_DIR = obj
MAIN = src/main.cpp
PROG = snake
DEPENDENCIES = ${OBJ_DIR}/.depend

VPATH = $(LIB_DIR)
SRCS = $(wildcard $(LIB_DIR)/*.cpp)
PROG_OBJ = $(patsubst $(LIB_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

CXX = g++
CXXFLAGS += -Wall -std=c++17


all: depend $(PROG)

-include $(DEPENDENCIES)

$(PROG): $(PROG_OBJ) $(OBJ_DIR)/main.o
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(LIB_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/main.o: $(MAIN)
	$(CXX) $(CXXFLAGS) -c $< -o $@

depend: $(SRCS) $(MAIN)
	$(CXX) $(CXXFLAGS) -MM -c $^ > $(DEPENDENCIES)
	sed -i 's/[a-zA-Z0-9_]*[.]o/$(OBJ_DIR)\/&/' $(DEPENDENCIES)

clean: 
	rm -f $(OBJ_DIR)/*.o $(PROG_OBJ) $(PROG) $(DEPENDENCIES)