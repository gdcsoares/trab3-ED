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

Node * add_recursive(Node *node, void * key, void * value,int (*comp)(void*, void *),void (*val_destroy)(void*),void (*key_destroy)(void*)) {
    if (node == NULL){
        return node_construct(key, value, NULL, NULL);
    }
    if (comp(node->key, key) > 0){
        node->left_son = add_recursive(node->left_son, key, value,comp,val_destroy,key_destroy);
    }
    else if (comp(node->key, key) < 0){
        node->right_son = add_recursive(node->right_son, key, value,comp,val_destroy,key_destroy);
    }
    else{
        val_destroy(node->value);
        node->value = value;
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
        if(node->value!=NULL){
            if(val_destroy!=NULL){
                val_destroy(node->value);
                node->value = NULL;
            }
        }
        if(node->key!=NULL){
            if(key_destroy!=NULL){
                key_destroy(node->key);
                node->key = NULL;
            }
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

void node_print(Node *node,FILE * file,void (*print)(void*,FILE*)) {
    if (node== NULL) {
        return;
    } 
    
    node_print(node->left_son,file,print);
    print(node,file);
    node_print(node->right_son,file,print);

}

void * node_in_order_value(Node * node,int i){
    if (node == NULL) {
        return NULL;
    } 

    int left = sub_tree_count(node->left_son);

    if(i<left){
        return node_in_order_value(node->left_son,i);
    }
    else if(i>left){
        return node_in_order_value(node->right_son,i-left-1);
    }
    else{
        return node->value;
    }
}

void * node_in_order_key(Node * node,int i){
    if (node == NULL) {
        return NULL;
    } 

    int left = sub_tree_count(node->left_son);

    if(i<left){
        return node_in_order_key(node->left_son,i);
    }
    else if(i>left){
        return node_in_order_key(node->right_son,i-left-1);
    }
    else{
        return node->key;
    }
}


int sub_tree_count(Node * node) {
    if (node == NULL) {
        return 0;
    } else {
        int left = sub_tree_count(node->left_son);
        int right = sub_tree_count(node->right_son);

        return 1 + left + right;
    }
}

Node * node_search(Node * node, void * key,int (*comp)(void*, void *)){
    while(node!=NULL && comp(key,node->key)!=0){
        if(comp(key,node->key)<0){
            node=node->left_son;
        }
        else{
            node=node->right_son;
        }
    }
    if(node == NULL){
        return NULL;
    }
    return node;
}