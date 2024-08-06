#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <stdio.h>
#include <stdlib.h>
#include "edge.h"
#include "forward_list.h"

typedef struct vertex Vertex;

Vertex* vertex_create(int vertex_id);
int vertex_get_id(Vertex *v);
void vertex_add_edge(Vertex *v, Edge *e);
int vertex_get_qtd_edges(Vertex *v);
Edge* vertex_get_edge(Vertex *v, int i);
void vertex_destroy(Vertex *v);

#endif
