CFLAGS      = -Wall -O3
LFLAGS      = -Wall -O3
CC      = gcc

OBJ     = obj/heap.o obj/boastar.o obj/graph.o obj/main_boa.o
OBJ_BOD = obj/heap.o obj/bod.o obj/graph.o obj/main_bod.o
OBJ_NAMOADR = obj/heap.o obj/namoadr.o obj/graph.o obj/main_namoadr.o


all: boa bod namoadr

boa:  $(OBJ)
	$(CC) $(LFLAGS) -o boa $(OBJ)

bod:  $(OBJ_BOD)
	$(CC) $(LFLAGS) -o bod $(OBJ_BOD)

namoadr:  $(OBJ_NAMOADR)
	$(CC) $(LFLAGS) -o namoadr $(OBJ_NAMOADR)


obj/%.o: src/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f obj/*.o boa bod namoadr
