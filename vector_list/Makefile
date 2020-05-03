CC = gcc
CFLAGS = -Wall
PROG = main
PROG_OBJ = main.o lib/list.o lib/vector.o

all: $(PROG)

$(PROG) : $(PROG_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

.o : .c
	$(CC) -c $^

clean : 
	rm -f *.o $(PROG_OBJ) $(PROG)
