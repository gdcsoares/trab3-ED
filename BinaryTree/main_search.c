#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "search.h"
#include "binarytree.h"

void key_destroy(void * key){
    free(key);
}

void val_destroy(void * val){
    free(val);
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

void print_collection(void * node_void,FILE * file){
    Node * node = (Node*)node_void;
    int * freq_pointer = (int*)node->value;
    int freq = *freq_pointer;
    fprintf(file,"%s %d\n",(char*)node->key,freq);
}


void print_index(void * node_void,FILE * file){
    Node * node = (Node*)node_void;
    fprintf(file,"%s\n",(char*)node->key);
    fprintf(file,"%d\n",binary_tree_size(node->value));
    binary_tree_print(node->value,file,print_collection);
}


int main(int argc, char * argv[]){
    char * index_file = argv[1];
    BinaryTree * bt = load_index(index_file,compare_keys, val_destroy,key_destroy, bt_destroy);
    char query[1000];
    printf("Query: ");
    scanf("%[^\n]", query);
    Vector * recommendations = search_docs(bt,query,compare_keys,val_destroy,key_destroy,bt_clear);
    print_recommendations(recommendations);
    for(int i=0 ; i < vector_size(recommendations);i++){
        recommendation_destroy(vector_get(recommendations,i));
    }
    vector_destroy(recommendations);
    return 0;
}