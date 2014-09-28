#ifndef __PROC_STATUS_H
#define __PROC_STATUS_H

#define VMPEAK_B    0
#define VMHWM_B     4
#define VMRSS_B     5


void getVmPeak(int pid, int *vmPeak);
void getVmHWM(int pid, int *vmHWM);
void getVmRSS(int pid, int *vmRSS);


#endif
