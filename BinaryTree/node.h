#ifndef NODE_H
#define NODE_H

typedef struct Node{
    void * key;
    void * value;
    struct Node * left_son;
    struct Node * right_son;
}Node;

Node * node_construct(void * key, void * value, Node * left, Node * right);
Node * add_recursive(Node *node, void * key, void * value,int (*comp)(void*, void *),void (*val_destroy)(void*),void (*key_destroy)(void*));
Node * find_parent(Node * root,Node * node);
void node_destroy_recursive(Node * node,void (*key_destroy)(void*),void (*val_destroy)(void*));
void node_clear_recursive(Node * node);
void node_print(Node *node,FILE * file,void (*print)(void*,FILE*));
void * node_in_order_value(Node * node,int i);
void * node_in_order_key(Node * node,int i);
int sub_tree_count(Node * node);
Node * node_search(Node * node, void * key,int (*comp)(void*, void *));

#endif