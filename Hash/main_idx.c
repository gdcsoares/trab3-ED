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

    char * diretorio;
    scanf("%s",diretorio)

    Vector * files = build_files_names(diretorio);
    HashTable * idx = index_build(files,hash_string,compare_keys,val_destroy);
    index_save(idx);
    
    return 0;
}