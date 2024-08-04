#ifndef EDGE_H_
#define EDGE_H_

#include <stdlib.h>
#include <stdio.h>

typedef struct edge Edge;

Edge* edge_create(int src, int dest, double weight);

double edge_weight(Edge *e);

int edge_src(Edge *e);

int edge_dest(Edge *e);

int edge_weight_compare(const void *a, const void *b);

void edge_destroy(Edge *e);

#endif 
