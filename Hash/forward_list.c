#include "forward_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ForwardList * forward_list_construct(){
    return (ForwardList*)calloc(1,sizeof(ForwardList));
}

void forward_list_push_front(ForwardList *flist, void * value){

    flist->head = node_construct(value,flist->head);
    flist->size++;
}

void forward_list_destroy(ForwardList *flist, void (*destroy)(void*)){
    Node * node_it = flist->head;
    Node * next;
    while(node_it!=NULL){
        next = node_it->next;
        node_destroy(node_it, destroy);
        node_it=next;
    }
    free(flist);
}

void forward_list_clear(ForwardList *flist){
    Node * node_it = flist->head;
    Node * next;
    while(node_it!=NULL){
        next = node_it->next;
        free(node_it);
        node_it=next;
    }
    free(flist);
}
int forward_list_size(ForwardList *flist){
    return flist->size;
}

void forward_list_print(ForwardList * flist,void (*print)(void*)){
    Node * node_it = flist->head;
    while(node_it!=NULL){ 
        print(node_it->value);
        printf("\n");
        node_it =node_it ->next;
    }
}

int forward_list_verify_string(ForwardList *flist, char * string){
    Node * node_it = flist->head;
    while(node_it!=NULL){ 
        if(strcmp(node_it->value,string)==0){
            return 1;
        }
        node_it =node_it->next;
    }
    return 0;
}

void * forward_list_get(ForwardList *flist,void * pointer, int (*comp)(void*, void *)){
    Node * node_it = flist->head;

    while(comp(node_it->value,pointer)!=0 && node_it!=NULL){
        node_it=node_it->next;
    }
    return node_it->value;
}

/*void * forward_list_pop_front(ForwardList *flist){
    Node * node_it = flist->head;
    data_type value = node_it->value;
    Node * next = node_it->next;
    node_destroy(node_it);
    flist->head= next;

    return value;
}
*/

ForwardList *forward_list_reverse(ForwardList *flist){
    ForwardList * reverse = forward_list_construct();
    Node * node_it = flist->head;
    while(node_it!=NULL){
        forward_list_push_front(reverse,node_it->value);
        node_it=node_it->next;
    }
    /*Node * rev_prev = NULL;
    Node * rev_head = reverse->head;
    Node * rev_next = NULL;
    while(rev_head!=NULL){
        rev_next = rev_head->next;
        rev_head->next = rev_prev;

        rev_prev = rev_head;
        rev_head = rev_next;
    }

    reverse->head = rev_prev;
    */
    return reverse; 
}

ForwardList * forward_list_copy(ForwardList * flist){
    ForwardList * copy = forward_list_construct();
    Node * node_it = flist->head;
    while(node_it!=NULL){
        forward_list_push_front(copy,node_it->value);
        node_it=node_it->next;
    }
    Node * copy_prev = NULL;
    Node * copy_head = copy->head;
    Node * copy_next = NULL;
    while(copy_head!=NULL){
        copy_next = copy_head->next;
        copy_head->next = copy_prev;

        copy_prev = copy_head;
        copy_head = copy_next;
    }

    copy->head = copy_prev;
    
    return copy;
}

void forward_list_remove(ForwardList *flist, void * pointer, int (*comp)(void*, void*)){
    Node * node_it = flist->head;
    Node * prev;
    Node * next = NULL;
    while(node_it!=NULL){
        next = node_it->next;
        if(comp(node_it->value,pointer)==0){
            if(node_it==flist->head){
                flist->head=next;
                free(node_it);
            }
            else{
                prev->next=next;
                free(node_it);
            }
            flist->size--; 
        }
        prev = node_it;
        node_it = next;
    }
}

Node * forward_list_head(ForwardList* flist){
    return flist->head;
}

void forward_list_sort(ForwardList * flist, int (*sort)(void*,void*)){
    int swapped = 1;
    Node* node_it;
    Node* prev = NULL;
    while(swapped!=0){
        swapped = 0;
        node_it = flist->head;
        while (node_it->next != prev) {
            if (sort(node_it->value,node_it->next->value)>0) {
                node_swap(node_it, node_it->next);
                swapped = 1;
            }
            node_it = node_it->next;
        }
        prev = node_it;
    };
}

void forward_list_cat(ForwardList *l, ForwardList *m){
    Node * node_it = m->head;
    while(node_it!=NULL){
        forward_list_push_front(l,node_it->value);
        node_it=node_it->next;
    }
}