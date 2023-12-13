#ifndef HASH_H
#define HASH_H


typedef struct HashTable HashTable;

typedef int (*HashFunction)(HashTable *, void *);
typedef int (*CmpFunction)(void *k1, void *k2);

typedef struct
{
    void *key;
    void *val;
} HashTableItem;


HashTable *hash_table_construct(int table_size, HashFunction hash_fn, CmpFunction cmp_fn);
HashTableItem * _hash_pair_construct(void * key, void* value);
void hash_table_set(HashTable *h, void *key, void *val,void (*val_destroy)(void*));
void *hash_table_get(HashTable *h, void *key);
int hash_table_size(HashTable *h);
void hash_table_destroy(HashTable *h,void (*key_destroy)(void*),void (*val_destroy)(void*));
void _hash_pair_destroy(HashTableItem * item,void (*key_destroy)(void*),void (*val_destroy)(void*));

#endif