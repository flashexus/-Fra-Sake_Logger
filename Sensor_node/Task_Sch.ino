#include "Task_Sch.h"
#include "avr/sleep.h"
//#include "avr/wdt.h"
//---------------------------------------------------------------


//---------------------------------------------------------------
volatile BOOL wakeUpflag;                 
//---------------------------------------------------------------

TASK_SCH Task;                                //Instance
//---------------------------------------------------------------
///////////////////メンバ変数初期化//////////////////////////////
TASK_SCH::TASK_SCH():
Task_schTimer(0),Task_UpdateCnt(WDT_CNT_TIME)
    {
      wakeUpflag = false;
      Task_info[0].Task_period = TASK1_TIME_DEBUG;
      Task_info[0].Task_exec_flag = false;
      Task_info[0].Task_permit_flag = true;
      Task_info[0].ptr_exec_task = task0;
      Task_info[1].Task_period = TASK2_TIME;
      Task_info[1].Task_exec_flag = false;
      Task_info[1].Task_permit_flag = true;
      Task_info[1].ptr_exec_task = task1;
      Task_info[2].Task_period = TASK3_TIME;
      Task_info[2].Task_exec_flag = false;
      Task_info[2].Task_permit_flag = false;
      Task_info[2].ptr_exec_task = task2;
}
//---------------------------------------------------------------
///////////////////スケジューラー本体//////////////////////////////
void TASK_SCH::sch(void){
  WDT_Setup();
  UpdateTimer();
  UpdateSch();
  exec_task(); 
}
//---------------------------------------------------------------
///////////////////メンバ変数初期化//////////////////////////////
void TASK_SCH::UpdateTimer(void){
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_mode();
  
  while( wakeUpflag == false ){;}

  MCUSR &= ~(1 << WDRF);
  wakeUpflag = false;
}
//---------------------------------------------------------------
///////////////////タイマ更新//////////////////////////////
void TASK_SCH::CountUpTimer(void){
  Task_schTimer += Task_UpdateCnt;
}
//---------------------------------------------------------------
///////////////////スケジュール更新管理//////////////////////////////
void TASK_SCH::UpdateSch(void){
volatile  UINT task_num;

  for(task_num = 0; task_num < MAX_TASK_NUM; task_num++)
  {
    if( (Task_schTimer % (Task_info[task_num].Task_period)) == 0 ){
      Task_info[task_num].Task_exec_flag = true;
     }
  }
}
//---------------------------------------------------------------
///////////////////タスク実行管理//////////////////////////////
void TASK_SCH::exec_task(void){
volatile  UINT task_num;
  for(task_num = 0; task_num < MAX_TASK_NUM; task_num++)
  {
    if(Task_info[task_num].Task_exec_flag == true){
     Task_info[task_num].Task_exec_flag = false;
     if( Task_info[task_num].Task_permit_flag == true ){
       Task_info[task_num].ptr_exec_task();
     }
    }
  }
}
//---------------------------------------------------------------
///////////////////タスク実行周期更新////////////////////////////
void TASK_SCH::Update_TaskPeriod(UCHAR task_no,ULONG period){
  Task_info[task_no].Task_period = period;
  Task_info[task_no].Task_exec_flag = false;
}
//---------------------------------------------------------------
///////////////////タスク実行許可更新//////////////////////////////
void TASK_SCH::Update_TaskPermission(UCHAR task_no,BOOL permit_flag){
  Task_info[task_no].Task_permit_flag = permit_flag;
}
//---------------------------------------------------------------
////////////////////////////WDT初期化//////////////////////////////
void WDT_Setup(void){
  //WDT_CNT_TIMEの設定と合わせた待ち時間にすること
  asm("wdr");
  WDTCSR |= (1 << WDCE)|(1 << WDE);
  WDTCSR = (1 << WDIE)|(1 << WDP3);     // 4 sec
}
//---------------------------------------------------------------
///////////////////WDT割り込みハンドラ//////////////////////////////
ISR(WDT_vect){
  Task.CountUpTimer();
  wakeUpflag = true;
}

