#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "proc_status.h"

#define PROC "/proc"
#define STAT "/status"

char *vm_str[64] = { 
    "VmPeak:", 
    "", 
    "", 
    "", 
    "VmHWM:", 
    "VmRSS:" 
};



bool checkAndGet(char *str, int id, int *value){
    if(str == NULL) return false;
    if(id > 64 || id < 0) return false;
    char *tok;
    tok = strtok(str, " ");

        printf("tok: %s\n ", str);
    if(strcmp(tok, vm_str[id]) == 0){
        tok = strtok(NULL , " ");
        printf("tok: %s\n ", tok);
        *value= atoi(tok);
        return true;
    }
    return false;
}


void getVmPeak(int pid, int *vmPeak){
    FILE * statusFile;
    char buffer[100] = {0, };
    size_t result;

    char status_file[32];
    sprintf(status_file, "/proc/%d/status", pid);

    statusFile = fopen (status_file , "r" );
    if (statusFile==NULL) {fputs ("File error",stderr); exit (1);}

    while(fgets(buffer, sizeof(buffer), statusFile)){
        if(checkAndGet(buffer, VMPEAK_B, vmPeak)) { 
            break;
        }
    }
    fclose(statusFile);
}
void getVmHWM(int pid, int *vmHWM){

}
void getVmRSS(int pid, int *vmRSS){

}


