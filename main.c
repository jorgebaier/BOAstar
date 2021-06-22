/////////////////////////////////////////////////////////////////////
// Carlos Hernandez
// All rights reserved
/////////////////////////////////////////////////////////////////////

#include "stdio.h"
#include "include.h"
#include "heap.h"
#include "boastar.h"
#include "math.h"


#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>


void read_adjacent_table(const char *filename)
{
    FILE *f;
    int i, ori, dest, dist, t;
    f = fopen(filename, "r");
	int num_arcs = 0;
    if (f==NULL) {printf( "Cannot open file %s.\n", filename); exit(1);}
	fscanf(f, "%d %d", &num_gnodes, &num_arcs);
	fscanf(f, "\n");
    
    for (i = 0; i < num_gnodes; i++)
		adjacent_table[i][0] = 0;

    for (i = 0; i < num_arcs; i++)
    {
		fscanf(f,"%d %d %d %d\n",&ori,&dest,&dist,&t);
		adjacent_table[ori-1][0]++;
		adjacent_table[ori-1][adjacent_table[ori-1][0] * 3 - 2] = dest-1;
		adjacent_table[ori-1][adjacent_table[ori-1][0] * 3 - 1] = dist;
		adjacent_table[ori-1][adjacent_table[ori-1][0] * 3] = t;

		pred_adjacent_table[dest-1][0]++;
		pred_adjacent_table[dest-1][pred_adjacent_table[dest-1][0] * 3 - 2] = ori-1;
		pred_adjacent_table[dest-1][pred_adjacent_table[dest-1][0] * 3 - 1] = dist;
		pred_adjacent_table[dest-1][pred_adjacent_table[dest-1][0] * 3] = t;
    }
    fclose (f);
}



void generate_maze()
{
	int y;
    if (graph_node == NULL){ 
		graph_node = (gnode *) calloc(num_gnodes , sizeof(gnode));
		for (y = 0; y < num_gnodes; ++y)
		{
			graph_node[y].id = y;
			graph_node[y].gmin = LARGE;
			graph_node[y].h1 = LARGE;
			graph_node[y].h2 = LARGE;
		}
	}
}

/*----------------------------------------------------------------------------------*/  
int main(int argc, char** argv)
{
	char filename[128];
	if (argc != 4) {
		printf("Usage: %s [graph_file] [start_node] [goal_node]\n", argv[0]);
		exit(1);
	}
	strcpy(filename,argv[1]);
	start = atoi(argv[2])-1;
	goal  = atoi(argv[3])-1;
	read_adjacent_table(filename);
	generate_maze();
    call_boastar();
}
