#ifndef PQ_H
#define PQ_H

#include <stdio.h>
#include <stdbool.h>
#include "item.h"

typedef struct pq PQ;

// cria uma min PQ com capacidade maxN
PQ *PQ_init(int maxN);

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

// Muda a prioridade do nó com identificador 'id' para 'value'
void PQ_decrease_key(PQ *pq, int id, double value);

// Retorna True se a PQ não tem elementos
bool PQ_empty(PQ *pq);

// Número de elementos na PQ
int  PQ_size(PQ *pq);

// Libera memória
void PQ_finish(PQ *pq);

// Imprime a PQ
void PQ_print(PQ *pq);

#endif
