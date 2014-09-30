#ifndef __PROC_STATUS_H
#define __PROC_STATUS_H

typedef struct {
    int vmPeak;
    int vmHWM;
    int vmRSS;
} ProcStatus;

int get_proc_stat(int pid, ProcStatus *procStatus);

#endif
