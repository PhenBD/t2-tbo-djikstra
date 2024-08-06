#include "../headers/graph.h"

struct graph{
    Vertex **vertices;
    int qtd_vertices;
    int qtd_edges;
};

Graph* graph_create(int qtd_vertices, int qtd_edges, FILE *edges){
    Graph *g = malloc(sizeof(Graph));

    g->qtd_vertices = qtd_vertices;
    g->qtd_edges = qtd_edges;

    g->vertices = malloc(qtd_vertices * sizeof(Vertex*));

    for(int i = 0; i < qtd_vertices; i++){
        g->vertices[i] = vertex_create(i);
    }

    for(int i = 0; i < qtd_edges; i++){
        int src, dest;
        double weight;
        fscanf(edges, "%d %d %lf", &src, &dest, &weight);
        vertex_add_edge(g->vertices[src], edge_create(src, dest, weight));
    }

    return g;
}

double *graph_dijkstra(Graph *g, int src){
    double *dist = malloc(g->qtd_vertices * sizeof(double));
    PQ *pq = PQ_create(g->qtd_vertices);
    int *visited = malloc(g->qtd_vertices * sizeof(int));

    for(int i = 0; i < g->qtd_vertices; i++){
        dist[i] = INFINITY;
        visited[i] = 0;
    }
    dist[src] = 0;
    
    Item *s = item_create(src, 0);
    PQ_insert(pq, s);

    while (!(PQ_empty(pq)))
    {
        Item *v = PQ_delmin(pq);
        int u = item_getKey(v);

        if (visited[u]) continue;
        visited[u] = 1;

        for(int i = 0; i < vertex_get_qtd_edges(g->vertices[u]); i++){
            Edge *e = vertex_get_edge(g->vertices[u], i);
            int dest = edge_dest(e);
            int src = edge_src(e);

            if(src == item_getKey(v)){
                if(dist[dest] > dist[src] + edge_weight(e)){
                    dist[dest] = dist[src] + edge_weight(e);

                    if(PQ_contains(pq, dest)){
                        PQ_decrease_key(pq, dest, dist[dest]);
                    }else{
                        Item *w = item_create(dest, dist[dest]);
                        PQ_insert(pq, w);
                    }
                }
            }
        }

        free(v);
    }
    
    free(visited);
    PQ_destroy(pq);
    return dist;
}

void graph_print(Graph *g){
    for(int i = 0; i < g->qtd_edges; i++){
        // printf("Aresta %d: %d -> %d, peso %lf\n", i, edge_src(g->edges[i]), edge_dest(g->edges[i]), edge_weight(g->edges[i]));
    }
}

void graph_destroy(Graph *g) {
    for(int i = 0; i < g->qtd_vertices; i++)
        vertex_destroy(g->vertices[i]);
    free(g->vertices);
    free(g);
}

