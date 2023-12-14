#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "search.h"


HashTable * load_index(char * index_file,HashFunction hash_fn, CmpFunction cmp_fn, void (*val_destroy)(void*),void (*key_destroy)(void*),void(*hash_destroy)(void*)){
    FILE * index = fopen(index_file,"r");

    int n_words;
    fscanf(index,"%d",&n_words);

    HashTable * hash = hash_table_construct(9293,hash_fn,cmp_fn);

    for(int i=0; i < n_words ; i++){
        char * word = (char *)malloc(50);
        fscanf(index,"%s",word);

        int n_documents;
        fscanf(index,"%d",&n_documents);

        HashTable * collection = hash_table_construct(733,hash_fn,cmp_fn);
        for(int a=0; a < n_documents; a++){
            char * file = (char *)malloc(100);
            int freq;
            fscanf(index, "%s %d", file, &freq);
            hash_table_set(collection,file,&freq,val_destroy,key_destroy);
        }

        hash_table_set(hash,word,collection,hash_destroy,key_destroy);
    }

    fclose(index);
    return hash;
}

Vector * search_docs(HashTable * hash,char * query,HashFunction hash_fn, CmpFunction cmp_fn,void (*val_destroy)(void*),void (*key_destroy)(void*)){
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    Vector *words = vector_construct();

    char *word = strtok(query, " ");

    while (word != NULL)
    {
        // o strdup faz um malloc internamente! Lembre-se de remove-lo!
        vector_push_back(words, strdup(word));
        word = strtok(NULL, " ");
    }

    Vector *unique = vector_unique(words,cmp_fn);

    HashTable *recommendations = hash_table_construct(9293, hash_fn, cmp_fn);

    for(int i=0 ; i <vector_size(unique) ; i++){
        char * word = vector_get(unique,i);

        if(hash_table_get(hash,word)!=NULL){
            HashTable * collection = (HashTable*)hash_table_get(hash,word);
            
            for(int a=0; a < hash_table_size(collection);a++){
                ForwardList * files = hash_table_buckets(collection,a);

                if(files!=NULL){
                    HashTableItem * item = files->head->value;
                    char * file = _hash_pair_key(item);

                    if(hash_table_get(recommendations,file)!=NULL){
                        int * freq_add = (int*)hash_table_get(recommendations,file);
                        int * freq_old = _hash_pair_value(item);
                        int freq_new = * freq_add + * freq_old;
                        hash_table_set(recommendations,file,&freq_new,val_destroy,key_destroy);
                    }
                    else{
                        int * freq = _hash_pair_value(item);
                        hash_table_set(recommendations,file,freq,val_destroy,key_destroy);        
                    }
                    
                }
            }
        }
    }

    double end = get_timestamp(); 
    double dt = (end - start);
    printf("Tempo para buscar palavras : %f\n", dt);
}


