#ifndef TASK_SCH_TYPES_H
#define TASK_SCH_TYPES_H
//---------------------------------------------------------------
#include "types.h"
class TASK{
private:
  volatile  BOOL Task1_exec_flag;
  volatile  UINT Task_schTimer;
  volatile  UINT Task_exec_time;
  volatile  UINT Task_UpdateCnt;
  void UpdateTimer(void);  
  void exec_task(void);
public:
  TASK();   
  void UpdateSch(void);
  void sch(void);
};
#endif
