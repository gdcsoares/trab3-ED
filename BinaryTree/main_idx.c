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

int main(int argc, char * argv[]){

    char * diretorio = argv[1];

    Vector * files = build_files(diretorio);
    BinaryTree * idx = index_build(files,hash_string,compare_keys,val_destroy,key_destroy,hash_destroy);
    index_save(idx,"index.txt");
    binary_tree_destroy(idx,key_destroy,bt_destroy);
    return 0;
}