#ifndef BOASTARH
#define BOASTARH

#define MAX_SOLUTIONS 1000000
#define MAX_RECYCLE   1000000

extern gnode *graph_node;
extern unsigned num_gnodes;
extern unsigned int adjacent_table[MAXNODES][MAXNEIGH];
extern unsigned int pred_adjacent_table[MAXNODES][MAXNEIGH];
extern unsigned int goal, start; 

void call_boastar();

#endif
