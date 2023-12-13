#ifndef INDEX_H
#define INDEX_H

#include "hash.h"
#include "vector.h"

Vector * build_files_names(char * diretorio);
char * read_file(void * name);
HashTable * index_build(Vector* files,HashFunction hash_fn, CmpFunction cmp_fn, void (*val_destroy)(void*))
void index_save(HashTable * index);



#endif