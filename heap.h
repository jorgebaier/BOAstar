/////////////////////////////////////////////////////////////////////
// Xiaoxun Sun & Sven Koenig @ USC 2009
// All rights reserved
/////////////////////////////////////////////////////////////////////

#ifndef HEAPH
#define HEAPH

#include "node.h"

extern unsigned long int heapsize;
extern unsigned long int stat_percolations;

void emptyheap_dij();
gnode *popheap_dij();
gnode *topheap_dij();
void deleteheap_dij(gnode *thiscell);
void insertheap_dij(gnode *thiscell);
gnode *posheap_dij(int i);
int sizeheap_dij();
long int opensize();

void emptyheap(); 
snode *popheap();
snode *topheap();
void deleteheap(snode *thiscell);
void insertheap(snode *thiscell);
int sizeheap();
snode *posheap(int i);
#endif
