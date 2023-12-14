#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

#define VECTOR_INIT_SIZE 1


struct vector{
    void* *data;
    int size;
    int allocated;
};

Vector * vector_construct(){
    Vector * v = (Vector*)calloc(1,sizeof(Vector));
    
    v->allocated = VECTOR_INIT_SIZE;
    v->size = 0;
    v->data = (void**)calloc(v->allocated,sizeof(void*));

    return v;
}   

void vector_destroy(Vector * v){
    free(v->data);
    free(v);
}

void vector_push_back(Vector *v, void * val){

    if(v->size==v->allocated){
        v->allocated++;
        v->data = (void**)realloc(v->data,v->allocated*sizeof(void*));
    }

    v->data[v->size]=val;
    v->size++;
}

int vector_find(Vector *v, void* val, int (*cmp)(void*, void*))
{
    int i = 0;
    while (i < vector_size(v))
    {
        if (!cmp(vector_get(v, i), val))
            return i;
        i++;
    }

    return -1;
}

int vector_size(Vector *v){
    return v->size;
}

void * vector_get(Vector *v, int i){
    if(i>=0 || i<v->size){
        return v->data[i];
    }
    else{
        printf("ERRO!Indice nao encontrado");
        exit(0);
    }
}

void vector_set(Vector *v, int i, void * val){
    if(i>=0 || i<v->size){
        v->data[i]=val;
    }
    else{
        printf("ERRO!Indice nao encontrado");
        exit(0);
    }
}

void * vector_remove(Vector *v, int i){
    void * val = v->data[i];

    for (int a = i + 1; a < v->size; a++) {
        v->data[a - 1] = v->data[a];
    }

    v->size--;
    return val;
}

void * vector_pop_front(Vector *v){
    return vector_remove(v, 0);
}

void * vector_pop_back(Vector *v){
    return vector_remove(v, (v->size-1));
}

void vector_insert(Vector *v, int i, void * val){

    if(v->size==v->allocated){
        v->allocated++;
        v->data = (void**)realloc(v->data,v->allocated*sizeof(void*));
    }

    for (int a=v->size; a >= i; a--){
        v->data[a+1]=v->data[a];
    }

    v->data[i]=val;
    v->size++;
}

void vector_swap(Vector *v, int i, int j){
    void * val1 = v->data[i];
    void * val2 = v->data[j];

    v->data[j]=val1;
    v->data[i]=val2;
}

void vector_sort(Vector *v,int (*sort)(void*,void*)){
    int n = v->size;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (sort(v->data[j],v->data[j+1])>0) {
                void * temp = v->data[j];
                v->data[j] = v->data[j + 1];
                v->data[j + 1] = temp;
            }
        }
    }
}

void vector_reverse(Vector *v){
    float j = v->size/2;
    int back= v->size-1;

    for(int i=0 ; i < j; i++){
        vector_swap(v, i, back);
        back--;
    }
}

Vector *vector_unique(Vector *v, int (*cmp)(void*, void*))
{
    Vector *output = vector_construct();

    for (int i = 0; i < vector_size(v); i++)
        if (vector_find(output, vector_get(v, i), cmp) == -1)
            vector_push_back(output, v->data[i]);

    return output;
}
