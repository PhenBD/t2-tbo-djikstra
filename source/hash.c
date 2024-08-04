
#include "hash.h"

struct HashTable
{
    ForwardList **buckets;
    HashFunction hash_fn;
    CmpFunction cmp_fn;
    int table_size;
    int n_elements;
};

struct HashTableIterator
{
    HashTable *table;
    int current_bucket;
    ListIterator *current_item;
};

HashTableItem *hash_table_item_construct(void *key, void *val){
    HashTableItem *hi = (HashTableItem *)malloc(sizeof(HashTableItem));

    hi->key = key;
    hi->val = val;

    return hi;
}

HashTable *hash_table_construct(int table_size, HashFunction hash_fn, CmpFunction cmp_fn)
{
    HashTable *hash_tbl = calloc(1, sizeof(HashTable));

    hash_tbl->table_size = table_size;
    hash_tbl->hash_fn = hash_fn;
    hash_tbl->cmp_fn = cmp_fn;
    hash_tbl->buckets = (ForwardList **)calloc(table_size, sizeof(ForwardList *));

    return hash_tbl;
}

void *hash_table_set(HashTable *h, void *key, void *val)
{
    int hash_value = h->hash_fn(h, key);

    if (h->buckets[hash_value] == NULL)
    {
        h->buckets[hash_value] = forward_list_construct();
    }
    
    HashTableItem *hi = forward_list_find(h->buckets[hash_value], key, h->cmp_fn);

    if (hi == NULL)
    {
        hi = hash_table_item_construct(key, val);
        forward_list_push_front(h->buckets[hash_value], hi);
        h->n_elements++;
    }
    else
    {
        void *aux = hi->val;
        hi->val = val;

        return aux;
    }

    return NULL;
}

void *hash_table_get(HashTable *h, void *key)
{
    int hash_value = h->hash_fn(h, key);

    if (h->buckets[hash_value] == NULL)
    {
        return NULL;
    }
    
    HashTableItem *hi = forward_list_find(h->buckets[hash_value], key, h->cmp_fn);

    if (hi != NULL)
    {
        return hi->val;
    }
    
    return NULL;
}

void *hash_table_pop(HashTable *h, void *key)
{
    int hash_value = h->hash_fn(h, key);
    
    HashTableItem *hi = forward_list_find(h->buckets[hash_value], key, h->cmp_fn);

    forward_list_remove(h->buckets[hash_value], hi);

    if (forward_list_size(h->buckets[hash_value]) == 0)
    {
        forward_list_destroy(h->buckets[hash_value]);
        h->buckets[hash_value] = NULL;
    }

    return hi;
}
/*
HashTableItem *bucket_find(ForwardList *l, void *key, int (*cmp_fn)(data_type data, void *key))
{
    ListIterator *li = list_front_iterator(l);
    HashTableItem *item = NULL;

    while (!(list_iterator_is_over(li)))
    {
        item = list_iterator_next(li);
        if (!cmp_fn(item->key, key))
            return item;
    }

    list_iterator_destroy(li);
    return NULL;
}*/

int hash_table_size(HashTable *h)
{
    return h->table_size;
}

int hash_table_num_elems(HashTable *h)
{
    return h->n_elements;
}

void hash_table_destroy(HashTable *h)
{
    for (int i = 0; i < h->table_size; i++)
    {        
        if (h->buckets[i] != NULL)
        {
            Node *n = h->buckets[i]->head;

            while (n != NULL)
            {
                HashTableItem *pair = n->value;
                hash_pair_destroy(pair);
                n = n->next;
            }

            forward_list_destroy(h->buckets[i]);
        }
    }

    free(h->buckets);
    free(h);
}

void hash_pair_destroy(HashTableItem *hi){
    // free(hi->key);
    free(hi->val);
    free(hi);
}

HashTableIterator *hash_table_iterator(HashTable *h)
{
    HashTableIterator *iterator = (HashTableIterator *)malloc(sizeof(HashTableIterator));
    iterator->table = h;
    iterator->current_bucket = 0;
    iterator->current_item = NULL;
    return iterator;
}

int hash_table_iterator_is_over(HashTableIterator *it)
{
    return it->current_bucket >= it->table->table_size;
}

HashTableItem *hash_table_iterator_next(HashTableIterator *it)
{
    HashTableItem *item = NULL;

    while (!(hash_table_iterator_is_over(it)))
    {
        if (it->table->buckets[it->current_bucket] != NULL)
        {
            if (it->current_item == NULL)
            {
                it->current_item = list_front_iterator(it->table->buckets[it->current_bucket]);
                item = list_iterator_next(it->current_item);
            }
            else
            {
                if (!(list_iterator_is_over(it->current_item)))
                {
                    item = list_iterator_next(it->current_item);
                }
                else
                {
                    list_iterator_destroy(it->current_item);
                    it->current_item = NULL;
                    it->current_bucket++;
                    continue;
                }   
            }
            
            if (item != NULL)
            {
                return item;
            }
        }

        it->current_bucket++;
    }

    return NULL;
}

void hash_table_iterator_destroy(HashTableIterator *it)
{
    list_iterator_destroy(it->current_item);
    free(it);
}