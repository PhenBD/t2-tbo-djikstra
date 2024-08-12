#ifndef GRAPH_H
#define GRAPH_H

#include "vertex.h"
#include "pq.h"
#include <math.h>

typedef struct graph Graph;

/**
 * Cria um grafo com o número especificado de vértices e arestas.
 *
 * @param qtd_vertices O número de vértices no grafo.
 * @param qtd_edges O número de arestas no grafo.
 * @param edges O arquivo contendo as informações das arestas.
 * @return Um ponteiro para o grafo criado.
 */
Graph *graph_create(int qtd_vertices, int qtd_edges, FILE *edges);

/**
 * Calcula o caminho mais curto a partir de um vértice de origem usando o algoritmo de Dijkstra.
 *
 * @param g O grafo no qual o algoritmo será executado.
 * @param src O vértice de origem a partir do qual o caminho mais curto será calculado.
 * @return Um ponteiro para um array de doubles contendo as distâncias mínimas do vértice de origem para cada vértice no grafo.
 *         O array deve ser liberado pelo chamador após o uso.
 */
double *graph_dijkstra(Graph *g, int src);

/**
 * Função responsável por destruir um grafo.
 *
 * Esta função libera a memória alocada para cada vértice do grafo e, em seguida, libera a memória alocada para o próprio grafo.
 *
 * @param g O ponteiro para o grafo a ser destruído.
 */
void graph_destroy(Graph *g);

#endif 
