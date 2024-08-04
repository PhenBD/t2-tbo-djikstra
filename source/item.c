#include "../headers/item.h"

struct item{
    void *key;           // identificador do nó
    double value;     // valor associado ao nó
};

Item *item_create(void *key, double value) {
    Item *t = malloc(sizeof(Item));
    t->key = key;
    t->value = value;
    
    return t;
}

void *item_get_key(Item *i){
    return i->key;
}

double item_get_value(Item *i){
    return i->value;
}

void item_set_value(Item *i, double value){
    i->value = value;
}

int item_more(Item *a, Item *b){
    return a->value > b->value;
}

void item_exch(Item *a, Item *b){
    Item t = *a;
    *a = *b;
    *b = t;
}

void item_destroy(Item *i){
    free(i->key);
    free(i);
}