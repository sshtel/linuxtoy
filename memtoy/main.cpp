#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#include "meminfo.h"
#include "proc_status.h"

using namespace std;

void printUsage(){
    printf("Usage  : ./memtoy { option } { pid }  { interval(sec, [1,999]) }  { filename optional) }\n"
           "Option : \"print\" | \"log\"  \n"
            );
}

int main(int argc, char *argv[]){

    //Normal Loop
    FILE *outputFile = 0;

    time_t current_time;
    struct tm *st;

    if(argc < 4){
        printUsage();
        exit(1);
    }

    printf(" %s %s %s %s %s\n", argv[0], argv[1], argv[2], argv[3], argv[4] );

    bool isPrint = false;
    bool isLog = false;
    if(strcmp(argv[1], "print") == 0){
        isPrint = true;
    }
    else if(strcmp(argv[1], "log") == 0){
        isPrint = true;
        isLog = true;
    }
    else{
        printUsage();
        exit(1);
    }
    
    //pid
    int pid = atoi(argv[2]);
    if(pid < 0){
        exit(1);
    }

    //interval
    int interval_sec = 1;
    if(strlen(argv[3]) > 3){ 
        printf("wrong parameter\n"); 
        printUsage();
        exit(1); 
    }
    interval_sec = atoi(argv[3]);
    if(interval_sec == 0) interval_sec = 1;

    //save file

    if(isLog){
        time(&current_time);
        st = localtime(&current_time);
        char outfile[256] = {0, };
        char date[32];
        sprintf(date, "%0004d%02d%02d_%02d%02d%02d",
                st->tm_year + 1900,
                st->tm_mon + 1,
                st->tm_mday,
                st->tm_hour,
                st->tm_min,
                st->tm_sec);

        if(argc >= 5 ){
            strcpy(outfile, argv[4]);
            strcat(outfile, "_");
            strcat(outfile, date);
            strcat(outfile, ".csv");
        }
        else{
            strcpy(outfile, date);
            strcat(outfile, ".csv");
        }
        outputFile = fopen(outfile, "w");
        if(!outputFile){
            printf("File creation failed \n");
            exit(1);
        }
    }
    else{
        outputFile = 0;
    }

    char time_line[128] = {0, };
    char line[128] = {0, };
    char proc_status_line[128] = {0, };
    char column_line[128] = {0, };


    //write fields
    memset(column_line, 0, sizeof(column_line));
    sprintf(column_line, "%-21s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s,%-10s\n", 
            "Date,       Time", 
            "Total", "Free", "Buffers", "Cached", "Used",
            "VmPeak", "VmHWM", "VmRSS"
            );
    printf("%s", column_line);
    if(outputFile){
        fwrite(column_line, 1, strlen(column_line), outputFile);
    }

    int total, free, buffers, cached;
    ProcStatus pStat;

    int printColumnCount = 0;
    while(1){
        time(&current_time);
        st = localtime(&current_time);

        //get data
        getMemInfo(&total, &free, &buffers, &cached);
        get_proc_stat(pid, &pStat);

        int used = total;
        used -= free; used -= buffers; used -= cached;
        memset(time_line, 0, sizeof(time_line));
        memset(line, 0, sizeof(line));
        memset(proc_status_line, 0, sizeof(proc_status_line));
        sprintf(time_line, "%0004d-%02d-%02d,%02d:%02d:%02d",
                st->tm_year + 1900,
                st->tm_mon + 1,
                st->tm_mday,
                st->tm_hour,
                st->tm_min,
                st->tm_sec);

        sprintf(line, "%-10d,%-10d,%-10d,%-10d,%-10d",
                total,free,buffers,cached,used
                );

        sprintf(proc_status_line, "%-10d,%-10d,%-10d", 
                pStat.vmPeak, pStat.vmHWM, pStat.vmRSS
                );

        if(isPrint){
            printColumnCount++;
            printf("[%s] ", time_line);
            printf("%s", line);
            printf("%s\n", proc_status_line);
            if(printColumnCount > 50)
            {
                printf("%s", column_line);
                printColumnCount = 0;
            }
        }
        if(outputFile){
            fwrite(time_line, 1, strlen(time_line), outputFile);
            fwrite(",", 1, 1, outputFile);
            fwrite(line, 1, strlen(line), outputFile);
            fwrite(",", 1, 1, outputFile);
            fwrite(proc_status_line, 1, strlen(proc_status_line), outputFile);
            fwrite("\n", 1, 1, outputFile);
            fflush(outputFile);
        }
        
        sleep(interval_sec);
    }

    if(outputFile){
        fclose(outputFile);
    }

    return 0;
}
