#include <stdio.h>
#include "headers/PQ.h"
#include "headers/item.h"

int main() {

    // inicializando a PQ
    PQ *pq = PQ_init(10);

    // inserindo alguns elementos na PQ
    PQ_insert(pq, item_create(1, 10.0));
    PQ_insert(pq, item_create(6, 5.0));
    PQ_insert(pq, item_create(3, 3.0));
    PQ_insert(pq, item_create(4, 4.0));
    PQ_insert(pq, item_create(7, 7.0));
    PQ_insert(pq, item_create(2, 1.0));

    // alterando a prioridade de alguns elementos
    PQ_decrease_key(pq, 4, 0.5); // agora o nó 4 tem valor 0.5, sua posição no heap deve mudar
    PQ_decrease_key(pq, 6, 0.1); // agora o nó 6 tem valor 0.1, sua posição no heap deve mudar

    // removendo o menor elemento e imprimindo
    while (!PQ_empty(pq)) {
        Item *p = PQ_delmin(pq);
        printf("Identificador %d, prioridade %lf\n", item_getId(p), item_getValue(p));
        free(p);
    }

    PQ_finish(pq);
}
