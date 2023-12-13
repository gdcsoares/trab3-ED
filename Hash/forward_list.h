#ifndef FLIST_H
#define FLIST_H

#include "node.h"

typedef struct{
    Node * head;
    int size;
}ForwardList;

ForwardList * forward_list_construct();
void forward_list_push_front(ForwardList *flist, void * value);
void forward_list_destroy(ForwardList *flist, void (*destroy)(void*));
void forward_list_clear(ForwardList *flist);
int forward_list_size(ForwardList *flist);
void forward_list_print(ForwardList * flist,void (*print)(void*));
void * forward_list_get(ForwardList *flist,void * pointer, int (*comp)(void*, void*));
void * forward_list_pop_front(ForwardList *flist);
Node * forward_list_head(ForwardList* flist);
int forward_list_verify_string(ForwardList *flist, char * string);
void forward_list_sort(ForwardList * flist, int (*sort)(void*,void*));
ForwardList *forward_list_reverse(ForwardList *flist);
ForwardList * forward_list_copy(ForwardList * flist);
void forward_list_remove(ForwardList *flist,void * pointer, int (*comp)(void*, void*));
void forward_list_cat(ForwardList *l, ForwardList *m);

#endif