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
  
}

void bt_destroy(void * bt_void){
    BinaryTree * bt = (BinaryTree*)bt_void;

    binary_tree_destroy(bt,key_destroy,val_destroy);
}

void bt_clear(void * bt_void){
    BinaryTree * bt = (BinaryTree *)bt_void;
    binary_tree_clear(bt);
}

int compare_keys(void * key1_void, void * key2_void){
    char * string1=(char*)key1_void;
    char * string2=(char*)key2_void;

    return strcmp(string1,string2);
}

int main(int argc, char * argv[]){
    char * index_file = argv[1];
    BinaryTree * hash = load_index(index_file,hash_string, compare_keys, val_destroy,key_destroy, hash_destroy);
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