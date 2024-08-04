#include "../headers/PQ.h"

struct pq{
    Item **nodes;
    int *map;
    int size;
};

PQ *PQ_init(int maxN) {
    PQ *pq = (PQ *) malloc(sizeof(PQ));
    pq->nodes = (Item **) malloc((maxN + 1) * sizeof(Item *));
    pq->map = (int *) malloc((maxN + 1) * sizeof(int));
    pq->size = 0;

    return pq;
}


static void PQ_swap(PQ *pq, int i, int j) {
    item_exch(pq->nodes[i], pq->nodes[j]);
    pq->map[item_getId(pq->nodes[i])] = i;
    pq->map[item_getId(pq->nodes[j])] = j;
}

void PQ_fix_up(PQ *pq, int k) {
    while (k > 1 && item_more(pq->nodes[k/2], pq->nodes[k])) {
        PQ_swap(pq, k, k/2);
        k = k/2;
    }
}

void PQ_fix_down(PQ *pq, int sz, int k){
  while (2*k <= sz) {
    int j = 2*k;
    if (j < sz && item_more(pq->nodes[j], pq->nodes[j+1])){
      j++;
    }
    if (!item_more(pq->nodes[k], pq->nodes[j])) {
      break;
    }
    PQ_swap(pq, k, j);
    k = j;
  }
}

void PQ_insert(PQ* pq, Item *v) {
    pq->size++;
    pq->nodes[pq->size] = v;
    pq->map[item_getId(v)] = pq->size;
    PQ_fix_up(pq, pq->size);
}

Item *PQ_delmin(PQ *pq) {
    Item *min = item_create(item_getId(pq->nodes[1]), item_getValue(pq->nodes[1]));

    PQ_swap(pq, 1, pq->size);
    free(pq->nodes[pq->size]);
    pq->size--;
    PQ_fix_down(pq, pq->size, 1);

    return min;
}

Item *PQ_min(PQ *pq) {
    return pq->nodes[1];
}

void PQ_decrease_key(PQ *pq, int id, double value) {
    int i = pq->map[id];
    item_setValue(pq->nodes[i], value);
    PQ_fix_up(pq, i);
}

bool PQ_empty(PQ *pq) {
    return pq->size == 0;
}

int  PQ_size(PQ *pq) {
    return pq->size;
}

void PQ_finish(PQ *pq) {
    for (int i = 1; i < pq->size; i++) {
        free(pq->nodes[i]);
    }
    free(pq->nodes);
    free(pq->map);
    free(pq);
}

void PQ_print(PQ *pq) {
    for (int i = 1; i <= pq->size; i++) {
        printf("Slot %d: Identificador %d, prioridade %lf\n", i, item_getId(pq->nodes[i]), item_getValue(pq->nodes[i]));
    }
}


