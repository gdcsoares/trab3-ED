#include <stdio.h>
#include <stdlib.h>
#include "binarytree.h"

typedef struct Node{
    void * key;
    void * value;
    struct Node * left_son;
    struct Node * right_son;
}Node;

struct bt{
    Node * root;
    int size;
}