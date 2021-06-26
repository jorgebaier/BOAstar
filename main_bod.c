/////////////////////////////////////////////////////////////////////
// Carlos Hernandez
// All rights reserved
/////////////////////////////////////////////////////////////////////


#include "include.h"
#include "heap.h"
#include "graph.h"
#include "bod.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>

/*----------------------------------------------------------------------------------*/
int main(int argc, char** argv) {
	char filename[128];
	if (argc != 3) 	{
		printf("Usage: %s [graph_file] [start_node] \n", argv[0]);
		exit(1);
	}
	strcpy(filename, argv[1]);
	start = atoi(argv[2]) - 1;
	read_adjacent_table(filename);
	new_graph();
	call_bod();
}
