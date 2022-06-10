/////////////////////////////////////////////////////////////////////
// Xiaoxun Sun & Sven Koenig @ USC 2009
// All rights reserved
/////////////////////////////////////////////////////////////////////

#ifndef MAZEH
#define MAZEH

#include "include.h"

struct gnode;
typedef struct gnode gnode;

struct gnode // stores info needed for each graph node
{
  long long int id;
  unsigned h1;
  unsigned h2;
  unsigned long long int key;
  unsigned gmin;
  unsigned long heapindex;
  snode * Gop_first; // pointers to gop list
  snode * Gop_last;
};

struct snode;
typedef struct snode snode;

struct snode // NAMOA*'s search nodes
{
  int state;
  unsigned g1;
  unsigned g2;
  double key;
  unsigned long heapindex;
  snode *next; // two pointers used to implement the gop doubly linked list for NAMOA*
  snode *prev;
  snode *searchtree;
};

#endif
