#ifndef VECTOR_H
#define VECTOR_H

typedef struct vector Vector;

Vector * vector_construct(); 

void vector_destroy(Vector * v);

void vector_push_back(Vector *v, void * val); 

int vector_size(Vector *v); 

void printVoidPtrVector(Vector * v);

void * vector_get(Vector *v, int i); 

void vector_set(Vector *v, int i, void * val); 

void * vector_remove(Vector *v, int i); 

void * vector_pop_front(Vector *v); 

void * vector_pop_back(Vector *v); 

void vector_insert(Vector *v, int i, void * val); 

void vector_swap(Vector *v, int i, int j); 

void vector_sort(Vector *v,int (*sort)(void*,void*));

void vector_reverse(Vector *v); 

Vector *vector_copy(Vector *v); 

void vector_clear(Vector *v);

#endif