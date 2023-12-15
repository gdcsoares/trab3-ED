#ifndef SEARCH_H
#define SEARCH_H

#include "binarytree.h"
#include "vector.h"

typedef struct
{
    char *doc;
    int freq;
}Recommendation;

BinaryTree * load_index(char * index_file,HashFunction hash_fn, CmpFunction cmp_fn, void (*val_destroy)(void*),void (*key_destroy)(void*),void(*hash_destroy)(void*));
Vector * search_docs(HashTable * hash,char * query,HashFunction hash_fn, CmpFunction cmp_fn,void (*val_destroy)(void*),void (*key_destroy)(void*),void (*hash_destroy)(void*));
Vector * convert_in_pairs(HashTable * hash);
void print_recommendations(Vector * rec);
Recommendation * recommendation_construct(void * key, void * freq);
int recommendation_sort(void * r1_void, void * r2_void);
void recommendation_destroy(Recommendation * rec);

#endif