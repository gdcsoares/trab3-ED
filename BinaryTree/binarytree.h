#ifndef BT_H
#define BT_H

#include "node.h"

typedef struct bt BinaryTree;

BinaryTree * binary_tree_construct();
void binary_tree_add(BinaryTree *bt, void *key, void * value,int (*comp)(void*, void *));
void * binary_tree_search(BinaryTree * bt, void * key,int (*comp)(void*, void *));
void binary_tree_remove(BinaryTree * bt, void * key,int (*comp)(void*, void *));
void transplant(BinaryTree *bt,Node * node, Node * son);
void binary_tree_print(BinaryTree *bt);
Node * binary_tree_min(Node * node);
Node * binary_tree_max(Node * node);
void binary_tree_destroy(BinaryTree * bt,void (*key_destroy)(void*),void (*val_destroy)(void*));




#endif