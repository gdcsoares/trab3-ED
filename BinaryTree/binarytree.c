#include <stdio.h>
#include <stdlib.h>
#include "binarytree.h"

struct bt{
    Node * root;
    int size;
};

BinaryTree * binary_tree_construct(){
    return (BinaryTree*)calloc(1,sizeof(BinaryTree));
}

void binary_tree_add(BinaryTree *bt, void *key, void * value,int (*comp)(void*, void *)) {
    bt->root = add_recursive(bt->root, key, value, comp);
    bt->size++;
}

void * binary_tree_search(BinaryTree * bt, void * key,int (*comp)(void*, void *)){
    Node * node = bt->root;
    while(node!=NULL && comp(key,node->key)!=0){
        if(comp(key,node->key)<0){
            node=node->left_son;
        }
        else{
            node=node->right_son;
        }
    }
    return node->value;
}

Node * binary_tree_min(Node *  node){
    while(node->left_son!=NULL){
        node=node->left_son;
    }

    return node;
}

Node * binary_tree_max(Node * node){
    while(node->right_son!=NULL){
        node=node->right_son;
    }

    return node;
}

Node * binary_tree_remove(BinaryTree * bt, void * key,int (*comp)(void*, void *)){
    Node * node = binary_tree_search(bt,key,comp);
    if(node->left_son == NULL){
        transplant(bt, node, node->right_son);
    }
    else if(node->right_son == NULL){
        transplant(bt, node, node->left_son);
    }
    else{
        Node * successor = binary_tree_min(node->right_son);
        if(find_parent(bt->root,successor)!=node){
            transplant(bt,successor,successor->right_son);
            successor->right_son = node->right_son;
            Node * r_parent = find_parent(bt->root,successor->right_son);
            r_parent = successor;
        }
        transplant(bt,successor,successor->right_son);
        successor->left_son = node->left_son;
        Node * l_parent = find_parent(bt->root,successor->left_son);
        l_parent = successor;
    }

    return node;
}

void transplant(BinaryTree *bt, Node * node, Node * son){
    Node * parent = find_parent(bt->root,node);

    if(parent==NULL){
        bt->root = son;
    }
    else if(node == parent->left_son){
        parent->left_son = son;
    }
    else{
        parent->right_son = son;
    }

    if(son!=NULL){
        Node * parent2 = find_parent(bt->root,son);
        parent2 = parent;
    }
}

void binary_tree_print(BinaryTree *bt) {
    printf("Tree: ");
    node_print(bt->root);
    printf("\n");
}

void binary_tree_destroy(BinaryTree * bt,void (*key_destroy)(void*),void (*val_destroy)(void*)){
    node_destroy_recursive(bt->root,key_destroy,val_destroy);
    if(bt!=NULL){
        free(bt);
    }
}