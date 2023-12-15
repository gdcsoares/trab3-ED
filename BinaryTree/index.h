#ifndef INDEX_H
#define INDEX_H

#include "binarytree.h"
#include "vector.h"

Vector * build_files(char * diretorio);
Vector * read_file(void * name_file_void);
BinaryTree * index_build(Vector* files,int(*cmp)(void*,void*), void (*val_destroy)(void*),void (*key_destroy)(void*),void(*bt_destroy)(void*));
void index_save(BinaryTree * index,char * output);



#endif