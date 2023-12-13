#include "stdio.h"
#include "stdlib.h"
#include "node.h"


Node *node_construct(void * value, Node * next){

    Node * node=(Node*)calloc(1,sizeof(Node));
    node->value = value;
    node->next = next;
    return node;

};

void node_destroy(Node *node, void (*destroy)(void*)){
    destroy(node->value);
    free(node);
};


void node_swap(Node * n1, Node *n2){
    void * temp = n1->value;
    n1->value = n2->value;
    n2->value = temp;
}