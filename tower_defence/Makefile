CC = g++
CFLAGS = -Wall
PROG = game
PROG_OBJ = main.o lib/CommonElement.o lib/GameManager.o lib/Tower.o \
	lib/PillTower.o lib/Cell.o lib/Map.o lib/Unit.o lib/LevelIcon.o \
	lib/BacteriaUnit.o lib/init_functions.o lib/Wave.o

all: $(PROG)

$(PROG) : $(PROG_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

.o : .cpp 
	$(CC) -c $^

clean : 
	rm -f *.o $(PROG_OBJ) $(PROG)
