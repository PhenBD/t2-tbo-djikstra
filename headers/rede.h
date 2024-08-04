#ifndef REDE_H
#define REDE_H

#include "graph.h"

typedef struct rede Rede;

Rede *rede_create_from_file(FILE *input);

void rede_calc_inflacao_RTT(Rede *r, FILE *output);

int edge_hash(HashTable *h, void *key);

int edge_cmp(void *a, void *b);

void rede_destroy(Rede *r);

#endif 