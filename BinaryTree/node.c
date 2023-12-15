#include <stdio.h>
#include <stdlib.h>
#include "node.h"


Node * node_construct(void * key, void * value, Node * left, Node * right){
    Node * node = (Node*)calloc(1,sizeof(Node));
    node->key = key;
    node->value = value;
    node->left_son = left;
    node->right_son = right;

    return node;
}

Node * add_recursive(Node *node, void * key, void * value,int (*comp)(void*, void *)) {
    if (node == NULL){
        return node_construct(key, value, NULL, NULL);
    }
    if (comp(node->key, key) > 0){
        node->left_son = add_recursive(node->left_son, key, value,comp);
    }
    else if (comp(node->key, key) < 0){
        node->right_son = add_recursive(node->right_son, key, value,comp);
    }
    else{
        node->val = value;
    }

    return node;
}

Node * find_parent(Node * root,Node * node){
    if(root==NULL || root==node){
        return NULL;
    }

    if ((root->left_son != NULL && root->left_son == node) || (root->right_son != NULL && root->right_son == node)) {
        return root;  
    }

    Node * left = find_parent(root->left_son,node);
    if(left!=NULL){
        return left;
    }

    return find_parent(root->right_son,node);
}


void node_destroy_recursive(Node * node,void (*key_destroy)(void*),void (*val_destroy)(void*)){
    if(node!=NULL){
        node_destroy_recursive(node->left_son,key_destroy,val_destroy);
        node_destroy_recursive(node->right_son,key_destroy,val_destroy);

        if(val_destroy!=NULL){
            val_destroy(node->value);
        }
        if(key_destroy!=NULL){
            key_destroy(node->key);
        }

        if(node!=NULL){
            free(node);
        }
    }
}

void node_clear_recursive(Node * node){
    if(node!=NULL){
        node_clear_recursive(node->left_son);
        node_clear_recursive(node->right_son);

        if(node!=NULL){
            free(node);
        }
    }
}

void node_print(Node *node) {
    if (node== NULL) {
        return;
    }
    
    node_print(node->left_son);
    int * pointer = (int*)node->value;
    int printar = *pointer;
    printf("%d ", printar);
    node_print(node->right_son);
}