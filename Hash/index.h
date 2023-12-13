#ifndef INDEX_H
#define INDEX_H

#include "hash.h"

char ** build_files_names()
char * read_file(char * name);
int count_files(c)
HashTable * index_build(char ** files,HashFunction hash_fn, CmpFunction cmp_fn, void (*val_destroy)(void*))
void index_save(HashTable * index);



#endif