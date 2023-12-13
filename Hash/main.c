#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

void key_destroy(void * key){

}

void val_destroy(void * key){
    
}

int hash_string(HashTable * h, void * void_string){
    char * string = (char*)void_string;
    int M = hash_table_size(h);
    int i, a = 127,b = 107;

    for(i = 0; *string != '\0';string++,a = a*b%(M-1)){
        i=(a*i + *string) % M;
    }

    return i;
}

int compare_keys(void * key1_void, void * key2_void){
    char * string1=(char*)key1_void;
    char * string2=(char*)key2_void;

    return strcmp(string1,string2);
}

int main(){

    HashTable * h = hash_table_construct(691,hash_string,compare_keys);
    int teste = 5;
    char * key1 = "chave";
    void * key1_void = malloc(strlen(key1) + 1);
    strcpy((char*)key1_void,key1);
    hash_table_set(h,key1,&teste);
    free(key1_void);

    int * pointer = (int*)hash_table_get(h,key1);
    int printar = *pointer;
    printf("%d\n",printar);

    hash_table_destroy(h,key_destroy,val_destroy);

    return 0;
}