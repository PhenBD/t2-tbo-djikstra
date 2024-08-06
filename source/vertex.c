#include "../headers/vertex.h"

struct vertex{
    int id;
    ForwardList *edges;
	int qtd_edges;
};

Vertex* vertex_create(int vertex_id){
    Vertex *v = calloc(1,sizeof(Vertex));
	v->edges = forward_list_construct();
    v->id = vertex_id;
	v->qtd_edges = 0;
    return v;    
}

void vertex_add_edge(Vertex *v, Edge *e){
	forward_list_push_front(v->edges, e);
	v->qtd_edges++;
}

int vertex_get_id(Vertex *v){
    return v->id;
}

int vertex_get_qtd_edges(Vertex *v){
	return v->qtd_edges;
}

Edge* vertex_get_edge(Vertex *v, int i){
	return forward_list_get(v->edges, i);
}

void vertex_destroy(Vertex *v){
	for (int i = 0; i < v->qtd_edges; i++)
	{
		Edge *e = vertex_get_edge(v, i);
		edge_destroy(e);
	}
    forward_list_destroy(v->edges);
    free(v);
}
