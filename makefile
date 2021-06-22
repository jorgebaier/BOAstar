CFLAGS      = -Wall -O3
LFLAGS      = -Wall -O3
CC      = gcc

OBJ     = heap.o boastar.o main.o

boastar:  $(OBJ)
	$(CC) $(LFLAGS) -o boastar $(OBJ)

.cc.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o boastar
