LIB_DIR = src/lib
OBJ_DIR = obj
MAIN = src/main.cpp
PROG = game
DEPENDENCIES = .depend

VPATH = $(LIB_DIR)
SRCS = $(wildcard $(LIB_DIR)/*.cpp)
PROG_OBJ = $(patsubst $(LIB_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

CC = g++
CXXFLAGS = -Wall


all: $(PROG)

$(PROG): $(PROG_OBJ) $(OBJ_DIR)/main.o
	$(CC) $(CXXFLAGS) -o $@ $^ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

$(OBJ_DIR)/%.o: $(LIB_DIR)/%.cpp
	$(CC) $(CXXFLAGS) -c $^ -o $@

$(OBJ_DIR)/main.o: $(MAIN)
	$(CC) $(CXXFLAGS) -c $^ -o $@

depend: $(SRCS)
	$(CC) $(CXXFLAGS) -MM -c $^ > $(DEPENDENCIES)

clean: 
	rm -f $(OBJ_DIR)/*.o $(PROG_OBJ) $(PROG) $(DEPENDENCIES)

-include $(DEPENDENCIES)
