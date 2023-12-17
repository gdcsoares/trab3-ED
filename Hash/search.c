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
    r->freq = (int*)freq;

    return r;
}

int recommendation_sort(void * r1_void, void * r2_void){
    Recommendation * r1 = (Recommendation*)r1_void;
    Recommendation * r2 = (Recommendation*)r2_void;

    return r1->freq-r2->freq;
}

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
            void *ponteiroVoid = malloc(sizeof(int));
            memcpy(ponteiroVoid, &freq, sizeof(int));
            hash_table_set(collection,file,ponteiroVoid,val_destroy,key_destroy);
        }

        hash_table_set(hash,word,collection,hash_destroy,key_destroy);
    }

    fclose(index);
    return hash;
}

Vector * search_docs(HashTable * hash,char * query,HashFunction hash_fn, CmpFunction cmp_fn,void (*val_destroy)(void*),void (*key_destroy)(void*),void (*hash_destroy)(void*)){
    double start = get_timestamp(); 

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
                        int * freq = (int*)hash_table_get(recommendations,file);
                        int * freq_add = _hash_pair_value(item);
                        *freq = * freq + * freq_add;

                    }
                    else{
                        int * freq = _hash_pair_value(item);
                        int freq_new;
                        void *ponteiroVoid = malloc(sizeof(int));
                        memcpy(ponteiroVoid, &freq, sizeof(int));
                        hash_table_set(recommendations,strdup(file),ponteiroVoid,val_destroy,key_destroy);        
                    }
                    
                }
            }
        }
        free(word);
    }

    vector_destroy(words);
    vector_destroy(unique);
    Vector * pairs = convert_in_pairs(recommendations);
    vector_sort(pairs,recommendation_sort);

    hash_table_destroy(hash,key_destroy,hash_destroy);
    double end = get_timestamp(); 
    double dt = (end - start);
    printf("Tempo para buscar palavras : %f\n", dt);

    return pairs;
}

Vector * convert_in_pairs(HashTable * hash){
    Vector * pairs = vector_construct();

    for(int i=0; i < hash_table_size(hash); i++){
        ForwardList * files = hash_table_buckets(hash,i);

        if(files!=NULL){
            HashTableItem * item = files->head->value;
            Recommendation * r = recommendation_construct(_hash_pair_key(item),_hash_pair_value(item));
            vector_push_back(pairs,r);
        }

    }

    hash_table_clear(hash);

    return pairs;
}

void print_recommendations(Vector * rec){
    for(int i=0; i < 10;i++){
        if(i == vector_size(rec)){
            break;
        }
        Recommendation * r =vector_get(rec,i);
        int * freq_pointer = r->freq;
        printf("%s %d\n",r->doc,*freq_pointer);
    }
}

void recommendation_destroy(Recommendation * rec){
    free(rec->doc);
    free(rec->freq);
    free(rec);
}


