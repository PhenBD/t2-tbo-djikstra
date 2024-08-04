#ifndef GRAPH_H
#define GRAPH_H

#include "edge.h"
#include "pq.h"
#include <math.h>

typedef struct graph Graph;

Graph *graph_create(int qtd_vertices, int qtd_edges, FILE *edges);

double *graph_dijkstra(Graph *g, int src);

int int_hash(HashTable *h, void *key);

int int_cmp(void *a, void *b);

void graph_print(Graph *g);

void graph_destroy(Graph *g);

#endif 
