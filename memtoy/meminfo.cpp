#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "meminfo.h"
#include <string.h>

#define MEMINFO "/proc/meminfo"


int getMemInfo(int *total, int *free, int *buffers, int *cached){
    if(total == 0 || free == 0) return -1;

    FILE * meminfoFile;
    char buffer[100] = {0, };
    size_t result;

    meminfoFile = fopen ( MEMINFO , "r" );
    if (meminfoFile==NULL) {fputs ("File error",stderr); exit (1);}
   
    while(fgets(buffer, sizeof(buffer), meminfoFile)){
        char *tok;
        tok = strtok(buffer, " ");

        if(strcmp(tok, "MemTotal:") == 0){
            tok = strtok(NULL , " ");
//            printf("Total : %s\n ", tok);
            *total = atoi(tok);
        }
        else if(strcmp(tok, "MemFree:") == 0){
            tok = strtok(NULL , " ");
//            printf("Free : %s\n", tok);
            *free = atoi(tok);
        }
        else if(strcmp(tok, "Buffers:") == 0){
            tok = strtok(NULL , " ");
//            printf("Cached : %s\n", tok);
            *buffers= atoi(tok);
        }
        else if(strcmp(tok, "Cached:") == 0){
            tok = strtok(NULL , " ");
//            printf("Cached : %s\n", tok);
            *cached = atoi(tok);
        }
        else{
        
        }

        memset(buffer, 0, sizeof(buffer));
    }


    // terminate
    fclose (meminfoFile);
}
