/////////////////////////////////////////////////////////////////////
// Carlos Hernandez
// All rights reserved
/////////////////////////////////////////////////////////////////////

#include "heap.h"
#include "node.h"
#include "include.h"
#include "namoadr.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

gnode* graph_node;
unsigned num_gnodes;
unsigned adjacent_table[MAXNODES][MAXNEIGH];
unsigned pred_adjacent_table[MAXNODES][MAXNEIGH];
unsigned goal, start;
gnode* start_state;
gnode* goal_state;
snode* start_node;

unsigned long long int stat_expansions = 0;
unsigned long long int stat_generated = 0;
unsigned long long int stat_gopoperations = 0;
unsigned long long int minf_solution = LARGE;

unsigned solutions[MAX_SOLUTIONS][2];
snode* recycled_nodes[MAX_RECYCLE];
int next_recycled = 0;

unsigned nsolutions = 0;
unsigned stat_pruned = 0;
unsigned stat_created = 0;

void initialize_parameters() {
    start_state = &graph_node[start];
    goal_state = &graph_node[goal];
    stat_percolations = 0;
}

int backward_dijkstra(int dim) {
    for (int i = 0; i < num_gnodes; ++i)
        graph_node[i].key = LARGE;
    emptyheap_dij();
    goal_state->key = 0;
    insertheap_dij(goal_state);

    while (topheap_dij() != NULL) {
        gnode* n;
        gnode* pred;
        short d;
        n = popheap_dij();
        if (dim == 1)
            n->h1 = n->key;
        else
            n->h2 = n->key;
        ++stat_expansions;
        for (d = 1; d < pred_adjacent_table[n->id][0] * 3; d += 3) {
            pred = &graph_node[pred_adjacent_table[n->id][d]];
            int new_weight = n->key + pred_adjacent_table[n->id][d + dim];
            if (pred->key > new_weight) {
                pred->key = new_weight;
                insertheap_dij(pred);
            }
        }
    }
    return 1;
}

snode* new_node() {
	snode* state;
	
	if (next_recycled > 0) { //to reuse pruned nodes in memory
		state = recycled_nodes[--next_recycled];
     }
     else{
		state = (snode*)malloc(sizeof(snode));
        ++stat_created;
    }
    state->heapindex = 0;
    state->gopnext = NULL;
    state->gopprev = NULL;
    return state;
}



void addGop(snode *n){
	if (graph_node[n->state].gopfirst == NULL){
		graph_node[n->state].gopfirst = graph_node[n->state].goplast = n;
		n->gopprev = n->gopnext = NULL;
	}else{
		graph_node[n->state].goplast->gopnext = n;
		n->gopprev = graph_node[n->state].goplast;
		graph_node[n->state].goplast = n;
		n->gopnext = NULL;
	}
}


void addGopFront(snode *n){
	n->gopnext = graph_node[n->state].gopfirst;
	if (graph_node[n->state].gopfirst != NULL)
		graph_node[n->state].gopfirst->gopprev = n;
	graph_node[n->state].gopfirst = n;
	n->gopprev = NULL;	
}


void removeGop(snode *n){
	if (n->gopprev != NULL)
		n->gopprev->gopnext = n->gopnext; 
	else
		graph_node[n->state].gopfirst = n->gopnext;
	if (n->gopnext != NULL)
		n->gopnext->gopprev = n->gopprev;
	else
		graph_node[n->state].goplast = n->gopprev;
}


void UpdateOpen(snode *n){
	snode *x = graph_node[n->state].gopfirst;
	while (x != NULL){
		if (x->g1 >= n->g1 && x->g2 >= n->g2){
			deleteheap(x);
			removeGop(x);	
		}
		x = x->gopnext;
		stat_gopoperations++;
	}
	addGop(n);
	insertheap(n);
}	

void moveTofront(snode *n){
	if (graph_node[n->state].gopfirst != graph_node[n->state].goplast){
		removeGop(n);
		addGopFront(n);
	}
}


short isDominated(unsigned g1,unsigned g2, unsigned n){
	snode* x;
	x = graph_node[n].gopfirst;
	while (x != NULL){
		if (x->g1 <= g1 && x->g2 <= g2){
#ifdef M3 //in include.h
			if (graph_node[n].gopfirst != x) 
				moveTofront(x);
#endif
			return 1;	
		}
		stat_gopoperations++;
		x = x->gopnext;
	}
return 0;
}



int namoadr() {
    nsolutions = 0;
    stat_pruned = 0;

    emptyheap();

    start_node = new_node();
    ++stat_created;
    start_node->state = start;
    start_node->g1 = 0;
    start_node->g2 = 0;
    start_node->key = 0;
    start_node->searchtree = NULL;
    insertheap(start_node);
    graph_node[start].gopfirst = start_node;   


    stat_expansions = 0;

    while (topheap() != NULL) {
        snode* n = popheap(); //best node in open
        short d;
		
		removeGop(n);
		
        if (n->g2 + graph_node[n->state].h2 >= minf_solution) {
            stat_pruned++;
            if (next_recycled < MAX_RECYCLE) {
                recycled_nodes[next_recycled++] = n;
            }
            continue;
        }

        graph_node[n->state].gmin = n->g2;

        if (n->state == goal) {
            //printf("GOAL [%d,%d] nsolutions:%d expanded:%llu generated:%llu heapsize:%d pruned:%d\n", n->g1, n->g2, nsolutions, stat_expansions, stat_generated, sizeheap(), stat_pruned);
            solutions[nsolutions][0] = n->g1;
            solutions[nsolutions][1] = n->g2;
            nsolutions++;
            if (nsolutions >= MAX_SOLUTIONS) {
                printf("Maximum number of solutions reached, increase MAX_SOLUTIONS!\n");
                exit(1);
            }
            if (minf_solution > n->g2)
                minf_solution = n->g2;
            continue;
        }

        ++stat_expansions;

        for (d = 1; d < adjacent_table[n->state][0] * 3; d += 3) {
            snode* succ;
            double newk1, newk2, newkey;
            unsigned nsucc = adjacent_table[n->state][d];
            unsigned cost1 = adjacent_table[n->state][d + 1];
            unsigned cost2 = adjacent_table[n->state][d + 2];

            unsigned newg1 = n->g1 + cost1;
            unsigned newg2 = n->g2 + cost2;
            unsigned h1 = graph_node[nsucc].h1;
            unsigned h2 = graph_node[nsucc].h2;

            if (newg2 >= graph_node[nsucc].gmin || newg2 + h2 >= minf_solution || isDominated(newg1,newg2,nsucc))
                continue;

            newk1 = newg1 + h1;
            newk2 = newg2 + h2;

            succ = new_node();

            succ->state = nsucc;
            stat_generated++;

            newkey = newk1 * (double)BASE + newk2;
            succ->searchtree = n;
            succ->g1 = newg1;
            succ->g2 = newg2;
            succ->key = newkey;
            UpdateOpen(succ);
        }
    }

    return nsolutions > 0;
}

/* ------------------------------------------------------------------------------*/
void call_namoadr() {
    float runtime;
    struct timeval tstart, tend;
    unsigned long long min_cost;
    unsigned long long min_time;

    initialize_parameters();

    gettimeofday(&tstart, NULL);

    //Dijkstra h1
    if (backward_dijkstra(1))
        min_cost = start_state->h1;
    //Dijkstra h2
    if (backward_dijkstra(2))
        min_time = start_state->h2;

    //NAMOA*dr
    namoadr();

    gettimeofday(&tend, NULL);
    runtime = 1.0 * (tend.tv_sec - tstart.tv_sec) + 1.0 * (tend.tv_usec - tstart.tv_usec) / 1000000.0;
    //		printf("nsolutions:%d Runtime(ms):%f Generated: %llu statexpanded1:%llu\n", nsolutions, time_astar_first1*1000, stat_generated, stat_expansions);
    printf("%lld;%lld;%d;%f;%llu;%llu;%u;%llu\n",
        start_state->id + 1,
        goal_state->id + 1,
        nsolutions,
        runtime * 1000,
        stat_generated,
        stat_expansions,
        stat_created,
        stat_gopoperations);
}
