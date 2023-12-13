#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hash.h"

Vector * build_files(char * diretorio){
    char caminhoArquivo[100];
    snprintf(caminhoArquivo,sizeof(caminhoArquivo),"%s/files.txt",diretorio);
    fopen(caminhoArquivo,"r");

    Vector * files_paths = vector_construct();

    char line [100];
    while(fgets()!=NULL){


        vector_push_back(files_paths,line);
    }

    return files_paths;
}