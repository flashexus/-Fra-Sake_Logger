#ifndef TASK_SCH_TYPES_H
#define TASK_SCH_TYPES_H
//---------------------------------------------------------------
#include "types.h"

typedef struct{
  volatile ULONG Task_period;
  volatile BOOL  Task_exec_flag;
  volatile BOOL  Task_permit_flag;
  void (*ptr_exec_task)(void);
}TASK_INFO;

class TASK_SCH{
private:
  TASK_INFO Task_info[MAX_TASK_NUM];
  volatile  ULONG Task_schTimer;
  volatile  UINT Task_UpdateCnt;
  void UpdateTimer(void);  
  void exec_task(void);
public:
  TASK_SCH();   
  void UpdateSch(void);
  void CountUpTimer(void);
  void sch(void);
  void Update_TaskPeriod(UCHAR task_no,ULONG period);
  void Update_TaskPermission(UCHAR task_no,BOOL permit_flag);
};
#endif
