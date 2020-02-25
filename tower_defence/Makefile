 
CC = g++
CFLAGS = -Wall
PROG = main
PROG_OBJ = main.o lib/CommonElement.o lib/cell.o lib/map.o

all: $(PROG)

$(PROG) : $(PROG_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

.o : .cpp 
	$(CC) -c $^

clean : 
	rm -fv *.o $(PROG_OBJ) $(PROG)
