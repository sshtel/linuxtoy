#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>


#define MEMINFO "/proc/meminfo"
using namespace std;


int getMemInfo(int *total, int *free);


int getMemInfo(int *total, int *free){
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
        else{
        
        }

        memset(buffer, 0, sizeof(buffer));
    }


    // terminate
    fclose (meminfoFile);

    if(*total == 0 || *free ==0){
        return -1;
    }


    return 0;
}

int main(int argc, char *argv[]){

    int total, free;
    struct timeval tv;
    long sec, usec;
    //Normal Loop
    FILE *outputFile = 0;

    time_t current_time;
    struct tm *st;

    if(argc <= 1){
        printf("Usage : ./linuxmem { filename | 0(no save) } { interval(sec) } { \"print\" (optional)  } \n");
        exit(1);
    }

    printf(" %s %s %s \n", argv[0], argv[1], argv[2] );
    char line[100] = {0, };



    //save file
    if(strcmp(argv[1], "0") == 0){
        //no save
    }
    else{
        char outfile[100] = {0, };
        strcpy(outfile, argv[1]);
        strcat(outfile, ".csv");
        outputFile = fopen(outfile, "w");
        if(!outputFile){
            printf("File creation failed \n");
            exit(1);
        }
    }

    int interval_sec = 1;
    if(argc >= 3){
        if(strlen(argv[2]) > 1){ 
            printf("wrong parameter\n"); 
            printf("Usage : ./linuxmem { filename | 0(no save) } { interval(sec) } { \"print\" (optional)  } \n");
            exit(1); 
        }
        interval_sec = atoi(argv[2]);
        if(interval_sec == 0) interval_sec = 1;
         
    }

    bool isPrint = false;
    if(argc >= 4){
        if(strcmp(argv[3], "print") == 0){
            isPrint = true;
        }
    }

    //write fields
    if(outputFile){
        memset(line, 0, sizeof(line));
        strcpy(line, "date, time, total, free, used\n");
        fwrite(line, 1, strlen(line), outputFile);
    }

    //beginning time
    long beginSec = 0;
    gettimeofday(&tv, 0);
    beginSec = tv.tv_sec;


    while(1){
        gettimeofday(&tv, 0);
        sec = tv.tv_sec - beginSec;
        usec = tv.tv_usec;

        time(&current_time);
        st = localtime(&current_time);

        getMemInfo(&total, &free);

        memset(line, 0, sizeof(line));
        sprintf(line, "%0004d-%02d-%02d,\t%02d:%02d:%02d, \t%d,\t%d,\t%d\n", 
                st->tm_year + 1900,
                st->tm_mon + 1,
                st->tm_mday,
                st->tm_hour,
                st->tm_min,
                st->tm_sec,
                total,
                free,
                total-free);
        //sprintf(line, "%d.%000006d,\t%d,\t%d,\t%d\n", sec, usec, total, free, total-free);


        if(isPrint){
            printf("%s", line);
        }
        if(outputFile){
            fwrite(line, 1, strlen(line), outputFile);
            fflush(outputFile);
        }
        
        sleep(interval_sec);
    }

    if(outputFile){
        fclose(outputFile);
    }

    return 0;
}
