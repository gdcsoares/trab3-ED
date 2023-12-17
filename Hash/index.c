#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hash.h"
#include "forward_list.h"
#include "index.h"

double get_timestamp()
{
    struct timespec now;
    timespec_get(&now, TIME_UTC);
    return now.tv_sec + (((double)now.tv_nsec) / 1e9);
}

Vector * build_files(char * diretorio){
    char path[100];
    snprintf(path,sizeof(path),"%s/files.txt",diretorio);
    FILE * file;
    file = fopen(path,"r");

    Vector * files_paths = vector_construct();

    char line[100];
    int i;
    while (fgets(line, sizeof(line), file) != NULL) {
        for (int i = 0; line[i] != '\0'; ++i) {
            if (line[i] == '\n') {
                line[i] = '\0';  // Substitui o '\n' por '\0' para indicar o fim da string
                break;
            }
        } 
    char line_path[150];
    snprintf(line_path,sizeof(line_path), "%s/%s", diretorio, line);

    vector_push_back(files_paths, strdup(line_path));
    }
    fclose(file);

    return files_paths;
}

Vector * read_file(void * name_file_void){
    char * name_file = (char*)name_file_void; 
    FILE * file = fopen(name_file,"r");

    fseek(file, 0, SEEK_END); 
    int file_size = ftell(file); 
    rewind(file); 

    char * string = (char *)malloc(file_size + 1);
    fread(string,1,file_size,file);
    string[file_size]= '\0';
    
    Vector *words = vector_construct();

    char *word = strtok(string, " ");
    while (word != NULL)
    {
        // o strdup faz um malloc internamente! Lembre-se de remove-lo!
        vector_push_back(words, strdup(word));
        word = strtok(NULL, " ");
    }
    free(string);

    fclose(file);
    return words;
}

HashTable * index_build(Vector* files,HashFunction hash_fn, CmpFunction cmp_fn, void (*val_destroy)(void*),void (*key_destroy)(void*), void(*hash_destroy)(void*)){
    double start = get_timestamp(); 

    HashTable * index = hash_table_construct(9293,hash_fn,cmp_fn);
    int n = 0;
    for(int i = 0; i < vector_size(files); i++){
        char * file = vector_get(files,i);
        Vector * words = read_file(vector_get(files,i));

        for(int a = 0; a < vector_size(words);a++){

            char * word = vector_get(words,a);

            if(hash_table_get(index,word)==NULL){
                HashTable * collection = hash_table_construct(733,hash_fn,cmp_fn);
                hash_table_set(index,strdup(word),collection,hash_destroy,key_destroy);
            }

            HashTable * collection = (HashTable*)hash_table_get(index,word); 
            
            if(hash_table_get(collection,file)!=NULL){ 
                int * freq_pointer = (int*)hash_table_get(collection,file);
                *freq_pointer = *freq_pointer+1;
            }
            else{
                int freq = 1;

                void *ponteiroVoid = malloc(sizeof(int));
                memcpy(ponteiroVoid, &freq, sizeof(int));
                hash_table_set(collection,strdup(file),ponteiroVoid,val_destroy,key_destroy);
            }

            
        }
        for(int i = 0; i < vector_size(words); i++){
            free(vector_get(words,i));
        }
        vector_destroy(words);
    }

    for(int i = 0; i < vector_size(files); i++){
        free(vector_get(files,i));
    }
    vector_destroy(files);

    double end = get_timestamp(); 
    double dt = (end - start);
    printf("Tempo para criar index : %f\n", dt);

    return index;
}

void index_save(HashTable * index,char * output){
    FILE * idx = fopen(output,"w");

    int n_words = hash_table_n_elements(index);

    fprintf(idx,"%d\n",n_words);

    for(int i = 0; i < hash_table_size(index); i++){
        ForwardList * words = hash_table_buckets(index,i);
    
        if(words!=NULL){
            Node * node_it = words->head;

            while(node_it!=NULL){
            
            HashTableItem * word = (HashTableItem*)node_it->value;
            fprintf(idx,"%s\n",(char*)_hash_pair_key(word));

            HashTable * collection = (HashTable*)_hash_pair_value(word);
            fprintf(idx,"%d\n",hash_table_n_elements(collection));
            for(int a = 0; a <hash_table_size(collection);a++){
                ForwardList * files = hash_table_buckets(collection,a);

                if(files!=NULL){
                    HashTableItem * file = files->head->value;
                    int * freq_pointer = (int*)_hash_pair_value(file);
                    int freq = *freq_pointer;
                    fprintf(idx,"%s %d\n",(char*)_hash_pair_key(file),*freq_pointer);
                }
            }

            node_it=node_it->next;

            }

        }
    }

    fclose(idx);
}