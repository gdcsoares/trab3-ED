#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "forward_list.h"


struct HashTable
{
    ForwardList ** buckets;
    HashFunction hash_fn;
    CmpFunction cmp_fn;
    int table_size;
    int n_elements;
};

HashTable *hash_table_construct(int table_size, HashFunction hash_fn, CmpFunction cmp_fn)
{
    HashTable *hash_tbl = calloc(1, sizeof(HashTable));

    hash_tbl->table_size = table_size;
    hash_tbl->hash_fn = hash_fn;
    hash_tbl->cmp_fn = cmp_fn;
    hash_tbl->buckets = calloc(table_size, sizeof(ForwardList *));

    return hash_tbl;
}

HashTableItem * _hash_pair_construct(void * key, void* value){
    HashTableItem * item = (HashTableItem*)calloc(1,sizeof(HashTableItem));

    item->key = key;
    item->val = value;

    return item;
}

void hash_table_set(HashTable *h, void *key, void *val,void (*val_destroy)(void*)){
    int key_val = h->hash_fn(h, key);

    if(h->buckets[key_val]==NULL){
        h->buckets[key_val]=forward_list_construct();
        h->n_elements++;
    }

    Node * node_it = h->buckets[key_val]->head;
    int i = 0;

    while(node_it!=NULL){

        HashTableItem * item = node_it->value;

        if(h->cmp_fn(item->key,key)==0){
            val_destroy(item->val);
            item->val=val;
            i = 1;
            break;
        }

        node_it = node_it->next;
    }

    if(i==0){
        HashTableItem * new = _hash_pair_construct(key,val);
        forward_list_push_front(h->buckets[key_val],new);
    }

}

void * hash_table_get(HashTable *h, void *key){
    int key_val = h->hash_fn(h, key);

    if(h->buckets[key_val] == NULL){
        return NULL;
    }

    Node * node_it = h->buckets[key_val]->head;

    while(node_it!=NULL){

        HashTableItem * item = node_it->value;

        if(h->cmp_fn(item->key,key)==0){
            return item->val;
        }

        node_it = node_it->next;
    }

    return NULL;
}

int hash_table_size(HashTable *h){
    return h->table_size;
}

void hash_table_destroy(HashTable *h,void (*key_destroy)(void*),void (*val_destroy)(void*))
{
    for (int i = 0; i < h->table_size; i++)
    {
        if (h->buckets[i] != NULL)
        {
            Node *n = h->buckets[i]->head;

            while (n != NULL)
            {
                HashTableItem *pair = n->value;
                _hash_pair_destroy(pair,key_destroy,val_destroy);
                n = n->next;
            }

            forward_list_clear(h->buckets[i]);
        }
    }

    free(h->buckets);
    free(h);
}

void _hash_pair_destroy(HashTableItem * item, void (*key_destroy)(void*),void (*val_destroy)(void*)){
    key_destroy(item->key);
    val_destroy(item->val);
    free(item);
}