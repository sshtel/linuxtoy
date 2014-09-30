#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "proc_status.h"

#define PROC "/proc"
#define STAT "/status"

#define VMPEAK_B    0
#define VMHWM_B     4
#define VMRSS_B     5


char *vm_str[64] = { 
    "VmPeak:",      //VMPEAK_B
    "",             //1
    "",             //2
    "",             //3
    "VmHWM:",       //VMHWM_B
    "VmRSS:"        //VMRSS_B
};



bool checkAndGet(char *str, int id, int *value){
    if(str == NULL) return false;
    if(id > 64 || id < 0) return false;
    char *tok;
    tok = strtok(str, " \t");

    if(strcmp(tok, vm_str[id]) == 0){
        tok = strtok(NULL , " \t");
        //printf("tok: %s\n ", tok);
        *value= atoi(tok);
        return true;
    }
    return false;
}

int get_proc_stat(int pid, ProcStatus *procStatus)
{
    int vmPeak = 0, vmHWM = 0, vmRSS = 0;

    FILE * statusFile;
    char buffer[100] = {0, };
    size_t result;

    char status_file[32];
    sprintf(status_file, "/proc/%d/status", pid);
    statusFile = fopen (status_file , "r" );
    if (statusFile==NULL) { //fputs ("File error\n",stderr); 
        procStatus->vmPeak = 0;
        procStatus->vmHWM = 0;
        procStatus->vmRSS = 0;
        return -1;
    }

    char *tok;

    while(fgets(buffer, sizeof(buffer), statusFile)){
        tok = strtok(buffer, " \t");

        if(strcmp(tok, vm_str[VMPEAK_B]) == 0){
            tok = strtok(NULL , " \t");
            //printf("tok: %s\n ", tok);
            vmPeak = atoi(tok);
        }
        else if(strcmp(tok, vm_str[VMHWM_B]) == 0){
            tok = strtok(NULL , " \t");
            //printf("tok: %s\n ", tok);
            vmHWM = atoi(tok);
        }
        else if(strcmp(tok, vm_str[VMRSS_B]) == 0){
            tok = strtok(NULL , " \t");
            //printf("tok: %s\n ", tok);
            vmRSS = atoi(tok);
        }
        else{   continue; }
    }
    fclose(statusFile);

    procStatus->vmPeak = vmPeak;
    procStatus->vmHWM = vmHWM;
    procStatus->vmRSS = vmRSS;

    return 0;
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


