#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "index.h"

double get_timestamp()
{
    struct timespec now;
    timespec_get(&now, TIME_UTC);
    return now.tv_sec + (((double)now.tv_nsec) / 1e9);
}

Vector * build_files(char * diretorio){
    char path[100];
    sprintf(path,"%s/files.txt",diretorio);
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
    sprintf(line_path, "%s/%s", diretorio, line);

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

BinaryTree * index_build(Vector* files, int(*cmp)(void*,void*),void (*val_destroy)(void*),void (*key_destroy)(void*), void(*bt_destroy)(void*)){
    double start = get_timestamp(); 

    BinaryTree * index = binary_tree_construct();

    for(int i = 0; i < vector_size(files); i++){
        char * file = vector_get(files,i);
        Vector * words = read_file(vector_get(files,i));
        
        for(int a = 0; a < vector_size(words);a++){

            char * word = vector_get(words,a);
            if(binary_tree_search(index,word,cmp)!=NULL){
                BinaryTree * collection = (BinaryTree*)binary_tree_search(index,word,cmp); 

                if(binary_tree_search(collection,file,cmp)!=NULL){ 
                    int * freq_pointer = (int*)binary_tree_search(collection,file,cmp);
                    *freq_pointer = *freq_pointer+1;

                }
                else{
                    int freq = 1;

                    void *ponteiroVoid = malloc(sizeof(int));
                    memcpy(ponteiroVoid, &freq, sizeof(int));

                    binary_tree_add(collection,strdup(file),ponteiroVoid,cmp,val_destroy,key_destroy);
                }
                free(word);
            }

            else{
                int freq = 1;

                void *ponteiroVoid = malloc(sizeof(int));
                memcpy(ponteiroVoid, &freq, sizeof(int));

                BinaryTree * collection = binary_tree_construct();
                binary_tree_add(collection,strdup(file),ponteiroVoid,cmp,val_destroy,key_destroy);
                binary_tree_add(index,word,collection,cmp,bt_destroy,key_destroy);
            }
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

void index_save(BinaryTree * index,char * output,void (*print)(void*,FILE*)){
    FILE * idx = fopen(output,"w");
    fprintf(idx,"%d\n",binary_tree_size(index));
    binary_tree_print(index,idx,print);

    fclose(idx);
}