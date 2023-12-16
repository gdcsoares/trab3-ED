#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "search.h"

double get_timestamp()
{
    struct timespec now;
    timespec_get(&now, TIME_UTC);
    return now.tv_sec + (((double)now.tv_nsec) / 1e9);
}

Recommendation * recommendation_construct(void * key, void * freq){
    Recommendation * r = (Recommendation*)calloc(1,sizeof(Recommendation));
    r->doc = (char*)key;
    int * freq_int = (int*)freq;
    r->freq = *freq_int;
    free(freq);

    return r;
}


int recommendation_sort(void * r1_void, void * r2_void){
    Recommendation * r1 = (Recommendation*)r1_void;
    Recommendation * r2 = (Recommendation*)r2_void;

    return r1->freq-r2->freq;
}

BinaryTree * load_index(char * index_file, int(*cmp)(void*,void*), void (*val_destroy)(void*),void (*key_destroy)(void*),void(*bt_destroy)(void*)){
    FILE * index = fopen(index_file,"r");

    int n_words;
    fscanf(index,"%d",&n_words);

    BinaryTree* bt = binary_tree_construct();

    for(int i=0; i < n_words ; i++){
        char * word = (char *)malloc(50);
        fscanf(index,"%s",word);

        int n_documents;
        fscanf(index,"%d",&n_documents);

        BinaryTree * collection = binary_tree_construct();
        for(int a=0; a < n_documents; a++){
            char * file = (char *)malloc(100);
            int freq;
            fscanf(index,"%s %d", file, &freq);
            void *ponteiroVoid = malloc(sizeof(int));
            memcpy(ponteiroVoid, &freq, sizeof(int));
            binary_tree_add(collection,file,ponteiroVoid,cmp,val_destroy,key_destroy);
        }
        binary_tree_add(bt,word,collection,cmp,bt_destroy,key_destroy);
    }

    fclose(index);
    return bt;
}

Vector * search_docs(BinaryTree * bt,char * query, int(*cmp)(void*,void*),void (*val_destroy)(void*),void (*key_destroy)(void*),void (*bt_clear)(void*)){
    double start = get_timestamp(); 

    Vector *words = vector_construct();

    char *word = strtok(query, " ");

    while (word != NULL)
    {
        // o strdup faz um malloc internamente! Lembre-se de remove-lo!
        vector_push_back(words, strdup(word));
        word = strtok(NULL, " ");
    }

    Vector *unique = vector_unique(words,cmp);

    BinaryTree *recommendations = binary_tree_construct();

    for(int i=0 ; i <vector_size(unique) ; i++){
        char * word = vector_get(unique,i);

        if(binary_tree_search(bt,word,cmp)!=NULL){
            BinaryTree * collection = (BinaryTree*)binary_tree_search(bt,word,cmp); 

            if(binary_tree_size(collection)>0){

                for (int a = 0; a < binary_tree_size(collection); a++) {
                    char * file = (char*)binary_tree_node_key(collection,a);

                    if(binary_tree_search(recommendations,file,cmp)!=NULL){
                        int * freq = (int*)binary_tree_search(recommendations,file,cmp); 
                        int * freq_add = (int*)binary_tree_node_value(collection,a);
                        *freq = *freq + *freq_add;
                    }
                    else{
                        int * freq = (int*)binary_tree_node_value(collection,a);
                        binary_tree_add(recommendations,file,freq,cmp,val_destroy,key_destroy); 
                    }
                     
                }
            }
        }
    }

    vector_destroy(words);
    vector_destroy(unique);
    Vector * pairs = convert_in_pairs(recommendations);
    vector_sort(pairs,recommendation_sort);

    binary_tree_destroy(bt,NULL,bt_clear);
    double end = get_timestamp(); 
    double dt = (end - start);
    printf("Tempo para buscar palavras : %f\n", dt);

    return pairs;
}

Vector * convert_in_pairs(BinaryTree * bt){
    Vector * pairs = vector_construct();

    for(int i=0; i < binary_tree_size(bt); i++){
        void * doc = binary_tree_node_key(bt,i);
        void * freq = binary_tree_node_value(bt,i);

        Recommendation * r = recommendation_construct(doc,freq);
        vector_push_back(pairs,r);

    }

    binary_tree_clear(bt);

    return pairs;
}


void print_recommendations(Vector * rec){
    for(int i=0; i < 10;i++){
        if(i == vector_size(rec)){
            break;
        }
        Recommendation * r =vector_get(rec,i);
        printf("%s %d\n",r->doc,r->freq);
    }
}

void recommendation_destroy(Recommendation * rec){
    free(rec->doc);
    free(rec);
}


