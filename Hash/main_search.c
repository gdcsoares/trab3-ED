#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "search.h"
#include "hash.h"

void key_destroy(void * key){
   free(key);
}

void val_destroy(void * val){
  free(val);
}

void hash_destroy(void * hash_void){
    HashTable * hash = (HashTable*)hash_void;
    hash_table_destroy(hash,key_destroy,val_destroy);
}

void hash_clear(void * hash_void){
    HashTable * hash = (HashTable*)hash_void;
    hash_table_clear(hash);
}

int hash_string(HashTable * h, void * void_string){
    char * string = (char*)void_string;
    int M = hash_table_size(h);
    int i, a = 5179,b = 3643;

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

int main(int argc, char * argv[]){
    char * index_file = argv[1];
    HashTable * hash = load_index(index_file,hash_string, compare_keys, val_destroy,key_destroy, hash_destroy);
    char query[1000];
    printf("Query: ");
    scanf("%[^\n]", query);
    Vector * recommendations = search_docs(hash,query,hash_string,compare_keys,val_destroy,key_destroy,hash_destroy);
    print_recommendations(recommendations);
    for(int i=0 ; i < vector_size(recommendations);i++){
        recommendation_destroy(vector_get(recommendations,i));
    }
    vector_destroy(recommendations);
    return 0;
}