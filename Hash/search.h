#ifndef SEARCH_H
#define SEARCH_H

#include "hash.h"
#include "vector.h"

HashTable * load_index(char * index_file,HashFunction hash_fn, CmpFunction cmp_fn, void (*val_destroy)(void*),void (*key_destroy)(void*),void(*hash_destroy)(void*));
Vector * search_docs(HashTable * hash,char * query,HashFunction hash_fn, CmpFunction cmp_fn,void (*val_destroy)(void*),void (*key_destroy)(void*));
Vector * convert_in_pairs(HashTable * hash);

#endif