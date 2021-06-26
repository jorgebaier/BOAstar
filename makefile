CFLAGS      = -Wall -O3
LFLAGS      = -Wall -O3
CC      = gcc

OBJ     = obj/heap.o obj/boastar.o obj/graph.o obj/main_boa.o
OBJ_BOD = obj/heap.o obj/bod.o obj/graph.o obj/main_bod.o


all: boa bod

boa:  $(OBJ)
	$(CC) $(LFLAGS) -o boa $(OBJ)

bod:  $(OBJ_BOD)
	$(CC) $(LFLAGS) -o bod $(OBJ_BOD)

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f obj/*.o boa bod
