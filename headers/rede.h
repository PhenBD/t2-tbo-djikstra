#ifndef REDE_H
#define REDE_H

#include "graph.h"

typedef struct rede Rede;

Rede *rede_create_from_file(FILE *input);

void rede_calc_inflacao_RTT(Rede *r, FILE *output);

void rede_destroy(Rede *r);

#endif 