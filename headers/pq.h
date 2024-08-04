#ifndef PQ_H
#define PQ_H

#include <stdio.h>
#include <stdbool.h>
#include "item.h"
#include "hash.h"

typedef struct pq PQ;

// cria uma min PQ com capacidade maxN
PQ *PQ_create(int maxN, HashFunction hash_fn, CmpFunction cmp_fn);

// retorna o identificador do nó na posição i
void *PQ_get_key(PQ *pq, int i);

// compara nós, por valor
int PQ_compare_values(PQ *pq, int i, int j);

// troca dois elementos
static void PQ_swap(PQ *pq, int i, int j);

// sobe o nó k
void PQ_fix_up(PQ *pq, int k);

// desce o nó k
void PQ_fix_down(PQ *pq, int sz, int k);

// Insere Item na PQ. A maior prioridade é a do Item com menor campo 'value'
void PQ_insert(PQ* pq, Item *v);

// Remove Item com menor campo 'value' da PQ
Item *PQ_delmin(PQ *pq);

// Retorna Item com menor campo 'value' da PQ
Item *PQ_min(PQ *pq);

// Muda a prioridade do nó com identificador 'key' para 'value'
void PQ_decrease_key(PQ *pq, void *key, double value);

// Retorna True se a PQ contém o nó com identificador 'key'
bool PQ_contains(PQ *pq, void *key);

// Retorna True se a PQ não tem elementos
bool PQ_empty(PQ *pq);

// Número de elementos na PQ
int  PQ_size(PQ *pq);

// Libera memória
void PQ_destroy(PQ *pq);

#endif