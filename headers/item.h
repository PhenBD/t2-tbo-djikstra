#ifndef ITEM_H
#define ITEM_H

#include <stdlib.h>

typedef struct item Item;

// cria um nó
Item *item_create(int key, double value);

// retorna identificador do nó
int item_getKey(Item *i);

// retorna valor do nó
double item_getValue(Item *i);

// altera valor do nó
void item_setValue(Item *i, double value);

// compara nós, por valor
int item_more(Item *a, Item *b);

// troca dois nós
void item_exch(Item *a, Item *b);

#endif
