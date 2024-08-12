#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <stdio.h>
#include <stdlib.h>
#include "edge.h"
#include "forward_list.h"

typedef struct vertex Vertex;

/**
 * Cria um novo vértice com o ID especificado.
 *
 * @param vertex_id O ID do vértice a ser criado.
 * @return Um ponteiro para o vértice criado.
 */
Vertex* vertex_create(int vertex_id);

/**
 * Obtém o ID do vértice especificado.
 *
 * @param v O ponteiro para o vértice.
 * @return O ID do vértice.
 */
int vertex_get_id(Vertex *v);

/**
 * Adiciona uma aresta ao vértice especificado.
 *
 * @param v O ponteiro para o vértice.
 * @param e O ponteiro para a aresta a ser adicionada.
 */
void vertex_add_edge(Vertex *v, Edge *e);

/**
 * Obtém a quantidade de arestas do vértice especificado.
 *
 * @param v O ponteiro para o vértice.
 * @return A quantidade de arestas do vértice.
 */
int vertex_get_qtd_edges(Vertex *v);

/**
 * Obtém a aresta do vértice especificado no índice especificado.
 *
 * @param v O ponteiro para o vértice.
 * @param i O índice da aresta a ser obtida.
 * @return O ponteiro para a aresta.
 */
Edge* vertex_get_edge(Vertex *v, int i);

/**
 * Destroi o vértice especificado, liberando a memória alocada.
 *
 * @param v O ponteiro para o vértice a ser destruído.
 */
void vertex_destroy(Vertex *v);

#endif
