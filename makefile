CFLAGS      = -Wall -O3
LFLAGS      = -Wall -O3
CC      = gcc

OBJ     = heap.o boastar.o graph.o main_boa.o
OBJ_BOD = heap.o bod.o graph.o main_bod.o


all: boa bod

boa:  $(OBJ)
	$(CC) $(LFLAGS) -o boa $(OBJ)

bod:  $(OBJ_BOD)
	$(CC) $(LFLAGS) -o bod $(OBJ_BOD)

.cc.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o boa bod
