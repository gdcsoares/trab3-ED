#ifndef NODE_H
#define NODE_H


typedef struct Node
{
    void * value;
    struct Node * next;
}Node;

Node *node_construct(void * value, Node * next);
void node_destroy(Node *node, void (*destroy)(void*));
void node_swap(Node *n1, Node * n2);






#endif