#include "../headers/pq.h"

struct pq{
    Item **nodes;
    HashTable *map;
    int size;
};

PQ *PQ_create(int maxN, HashFunction hash_fn, CmpFunction cmp_fn) {
    PQ *pq = (PQ *) malloc(sizeof(PQ));
    pq->nodes = (Item **) malloc((maxN + 1) * sizeof(Item *));
    pq->map = hash_table_construct(maxN + 1, hash_fn, cmp_fn);
    pq->size = 0;

    return pq;
}

void *PQ_get_key(PQ *pq, int i) {
    return item_get_key(pq->nodes[i]);
}

int PQ_compare_values(PQ *pq, int i, int j) {
    return item_more(pq->nodes[i], pq->nodes[j]);
}

static void PQ_swap(PQ *pq, int i, int j) {
    item_exch(pq->nodes[i], pq->nodes[j]);

    int *aux_i = malloc(sizeof(int));
    *aux_i = i;

    int *aux_j = malloc(sizeof(int));
    *aux_j = j;

    hash_table_set(pq->map, PQ_get_key(pq, i), aux_i);
    hash_table_set(pq->map, PQ_get_key(pq, j), aux_j);
}

void PQ_fix_up(PQ *pq, int k) {
    while (k > 1 && PQ_compare_values(pq, k/2, k)) {
        PQ_swap(pq, k, k/2);
        k = k/2;
    }
}

void PQ_fix_down(PQ *pq, int sz, int k){
  while (2*k <= sz) {
    int j = 2*k;
    if (j < sz && PQ_compare_values(pq, j, j + 1)){
      j++;
    }
    if (!PQ_compare_values(pq, k, j)) {
      break;
    }
    PQ_swap(pq, k, j);
    k = j;
  }
}

void PQ_insert(PQ* pq, Item *v) {
    pq->size++;
    pq->nodes[pq->size] = v;
    int *aux = malloc(sizeof(int));
    *aux = pq->size;
    hash_table_set(pq->map, item_get_key(v), aux);
    PQ_fix_up(pq, pq->size);
}

Item *PQ_delmin(PQ *pq) {
    Item *min = item_create(item_get_key(pq->nodes[1]), item_get_value(pq->nodes[1]));

    PQ_swap(pq, 1, pq->size);
    free(pq->nodes[pq->size]);
    pq->size--;
    PQ_fix_down(pq, pq->size, 1);

    return min;
}

Item *PQ_min(PQ *pq) {
    return pq->nodes[1];
}

void PQ_decrease_key(PQ *pq, void *key, double value) {
    int *i = hash_table_get(pq->map, key);
    item_set_value(pq->nodes[*i], value);
    PQ_fix_up(pq, *i);
}

bool PQ_contains(PQ *pq, void *key) {
    return hash_table_get(pq->map, key) != NULL;
}

bool PQ_empty(PQ *pq) {
    return pq->size == 0;
}

int  PQ_size(PQ *pq) {
    return pq->size;
}

void PQ_destroy(PQ *pq) {
    for (int i = 1; i < pq->size; i++) {
        free(pq->nodes[i]);
    }
    free(pq->nodes);
    hash_table_destroy(pq->map);
    free(pq);
}


