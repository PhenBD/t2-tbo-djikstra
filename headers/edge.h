#ifndef EDGE_H_
#define EDGE_H_

#include <stdlib.h>
#include <stdio.h>

typedef struct edge Edge;

/**
 * Cria uma nova aresta com os parâmetros fornecidos.
 *
 * @param src O vértice de origem da aresta.
 * @param dest O vértice de destino da aresta.
 * @param weight O peso da aresta.
 * @return Um ponteiro para a nova aresta criada.
 */
Edge* edge_create(int src, int dest, double weight);

/**
 * Função que retorna o peso de uma aresta.
 *
 * @param e Ponteiro para a aresta.
 * @return O peso da aresta.
 */
double edge_weight(Edge *e);
 
/**
 * Obtém o vértice de origem de uma aresta.
 *
 * @param e Ponteiro para a aresta.
 * @return O vértice de origem da aresta.
 */
int edge_src(Edge *e);

/**
 * Obtém o vértice de destino de uma aresta.
 *
 * @param e Ponteiro para a aresta.
 * @return O vértice de destino da aresta.
 */
int edge_dest(Edge *e);
 
/**
 * Compara o peso de duas arestas.
 *
 * @param a Ponteiro para a primeira aresta.
 * @param b Ponteiro para a segunda aresta.
 * @return Um valor negativo se a primeira aresta tiver peso menor que a segunda,
 *         um valor positivo se a primeira aresta tiver peso maior que a segunda,
 *         ou zero se as arestas tiverem o mesmo peso.
 */
int edge_weight_compare(const void *a, const void *b);
 
/**
 * Libera a memória alocada para uma aresta.
 *
 * @param e Ponteiro para a aresta.
 */
void edge_destroy(Edge *e);

#endif 
