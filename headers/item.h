#ifndef ITEM_H
#define ITEM_H

#include <stdlib.h>

typedef struct item Item;

// cria um nó
Item *item_create(void *key, double value);

// retorna identificador do nó
void *item_get_key(Item *i);

// retorna valor do nó
double item_get_value(Item *i);

// altera valor do nó
void item_set_value(Item *i, double value);

// compara nós, por valor
int item_more(Item *a, Item *b);

// troca dois nós
void item_exch(Item *a, Item *b);

// libera memória do nó
void item_destroy(Item *i);

#endif
