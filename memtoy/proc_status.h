/*****************************************************************************************************************


  GNU GENERAL PUBLIC LICENSE
  Version 2, June 1991

  Copyright (C) 1989, 1991 Free Software Foundation, Inc., <http://fsf.org/>
  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
  Everyone is permitted to copy and distribute verbatim copies
  of this license document, but changing it is not allowed.


  bug report: http://github.com/sshtel/linuxtoy

 ***************************************************************************************************************/


#ifndef __PROC_STATUS_H
#define __PROC_STATUS_H

typedef struct {
    int vmPeak;
    int vmHWM;
    int vmRSS;
} ProcStatus;

int get_proc_stat(int pid, ProcStatus *procStatus);

#endif
