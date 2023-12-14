#ifndef INDEX_H
#define INDEX_H

#include "hash.h"
#include "vector.h"

Vector * build_files(char * diretorio);
Vector * read_file(void * name_file_void);
HashTable * index_build(Vector* files,HashFunction hash_fn, CmpFunction cmp_fn, void (*val_destroy)(void*),void (*key_destroy)(void*),void(*hash_destroy)(void*));
void index_save(HashTable * index,char * output);



#endif