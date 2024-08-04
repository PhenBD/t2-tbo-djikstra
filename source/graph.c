#include "../headers/graph.h"

struct graph{
    int *vertices;
    int qtd_vertices;
    Edge **edges;
    int qtd_edges;
};

Graph* graph_create(int qtd_vertices, int qtd_edges, FILE *edges){
    Graph *g = malloc(sizeof(Graph));

    g->qtd_vertices = qtd_vertices;
    g->qtd_edges = qtd_edges;

    g->edges = malloc(qtd_edges * sizeof(Edge*));
    g->vertices = malloc(qtd_vertices * sizeof(int));

    for(int i = 0; i < qtd_edges; i++){
        int src, dest;
        double weight;
        fscanf(edges, "%d %d %lf", &src, &dest, &weight);
        g->edges[i] = edge_create(src, dest, weight);
    }

    for(int i = 0; i < qtd_vertices; i++)
        g->vertices[i] = i;

    return g;
}

int int_hash(HashTable *h, void *key)
{
    int *k = (int *)key;
    return (*k * 83) % hash_table_size(h);
}

int int_cmp(void *a, void *b)
{
    int *aa = (int *)a;
    int *bb = (int *)b;

    if (*aa == *bb)
        return 0;
    else
        return 1;
}

double *graph_dijkstra(Graph *g, int src){
    double *dist = malloc(g->qtd_vertices * sizeof(double));
    PQ *pq = PQ_create(g->qtd_vertices, int_hash, int_cmp);

    for(int i = 0; i < g->qtd_vertices; i++){
        dist[i] = INFINITY;
    }
    dist[src] = 0;
    
    int *src_pointer = malloc(sizeof(int));
    *src_pointer = src;

    Item *s = item_create(src_pointer, 0);
    PQ_insert(pq, s);

    while (!(PQ_empty(pq)))
    {
        Item *v = PQ_delmin(pq);
        for(int i = 0; i < g->qtd_edges; i++){
            Edge *e = g->edges[i];

            if(edge_src(e) == *(int *)item_get_key(v)){
                if(dist[edge_dest(e)] > dist[edge_src(e)] + edge_weight(e)){
                    dist[edge_dest(e)] = dist[edge_src(e)] + edge_weight(e);

                    int *dest_pointer = malloc(sizeof(int));
                    *dest_pointer = edge_dest(e);

                    if(PQ_contains(pq, dest_pointer)){
                        PQ_decrease_key(pq, dest_pointer, dist[edge_dest(e)]);
                    } else {
                        Item *w = item_create(dest_pointer, dist[edge_dest(e)]);
                        PQ_insert(pq, w);
                    }
                }
            }
        }

        item_destroy(v);
    }
    
    PQ_destroy(pq);
    return dist;
}

void graph_print(Graph *g){
    for(int i = 0; i < g->qtd_edges; i++){
        printf("Aresta %d: %d -> %d, peso %lf\n", i, edge_src(g->edges[i]), edge_dest(g->edges[i]), edge_weight(g->edges[i]));
    }
}

void graph_destroy(Graph *g) {
    for(int i = 0; i < g->qtd_edges; i++)
        edge_destroy(g->edges[i]);
    free(g->edges);
    free(g->vertices);
    free(g);
}

