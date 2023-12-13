#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binarytree.h"

int compare_key(void * key_1, void * key_2){
    char * string1=(char*)key_1;
    char * string2=(char*)key_2;

    return strcmp(string1,string2);
}

void key_destroy(void * key){

}

void val_destroy(void * key){
    
}


int main(){

    BinaryTree * bt = binary_tree_construct();

    int teste = 5;
    int teste2 = 15;

    char * key1 = "chave1";
    void * key1_void = malloc(strlen(key1) + 1);
    strcpy((char*)key1_void,key1);
    binary_tree_add(bt,key1_void,&teste,compare_key);


    char * key2 = "chave2";
    void * key2_void = malloc(strlen(key2) + 1);
    strcpy((char*)key2_void,key2);
    binary_tree_add(bt,key2_void,&teste2,compare_key);

    int * pointer = (int*)binary_tree_search(bt,key1,compare_key);
    int printar = *pointer;
    printf("%d\n",printar);

    int * pointer2 = (int*)binary_tree_search(bt,key2,compare_key);
    int printar2 = *pointer2;
    printf("%d\n",printar2);
    

    binary_tree_print(bt);
    /*Node * node = binary_tree_remove(bt,key1,compare_key);*/
    
    free(key1_void);
    free(key2_void);
    binary_tree_destroy(bt,key_destroy,val_destroy);

    return 0;
}