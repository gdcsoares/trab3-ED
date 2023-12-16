#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "index.h"
#include "binarytree.h"

void key_destroy(void * key){
   
}

void val_destroy(void * val){
    free(val);
}

void bt_destroy(void * bt_void){
    BinaryTree * bt = (BinaryTree*)bt_void;

    binary_tree_destroy(bt,key_destroy,val_destroy);
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

    char * diretorio = argv[1];

    Vector * files = build_files(diretorio);
    BinaryTree * idx = index_build(files,compare_keys,val_destroy,key_destroy,bt_destroy);
    index_save(idx,"index.txt",print_index);
    binary_tree_destroy(idx,key_destroy,bt_destroy);
    return 0;
}