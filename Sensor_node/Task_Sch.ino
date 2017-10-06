#include "Task_Sch.h"
#include "avr/sleep.h"
//#include "avr/wdt.h"
//---------------------------------------------------------------
#define task1()       Task_Sensing()
#define WDT_CNT_TIME  4                   //秒単位設定
#define TASK1_TIME    56                   //秒単位設定 誤差調整含む
//---------------------------------------------------------------
volatile BOOL wakeUpflag;                 //Instance
//---------------------------------------------------------------

TASK Task;
//---------------------------------------------------------------
TASK::TASK():
     Task1_exec_flag(false),Task_schTimer(0),Task_exec_time(TASK1_TIME),Task_UpdateCnt(WDT_CNT_TIME)
     {
}
//---------------------------------------------------------------
void TASK::sch(void){
  WDT_Setup();
  UpdateTimer();
  exec_task(); 
}
//---------------------------------------------------------------
void TASK::UpdateTimer(void){
  wakeUpflag = false;
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_mode();
  
  while( wakeUpflag == false ){;}

  MCUSR &= ~(1 << WDRF);
}
//---------------------------------------------------------------
void TASK::exec_task(void){
  if(Task1_exec_flag == true){   
    Task1_exec_flag = false;
    task1();
  }
}
//---------------------------------------------------------------
void TASK::UpdateSch(void){
  Task_schTimer += Task_UpdateCnt;
  if (Task_schTimer >= Task_exec_time){
    Task_schTimer = 0U;
    Task1_exec_flag = true; 
  }
}
//---------------------------------------------------------------
void WDT_Setup(void){
  asm("wdr");
  WDTCSR |= (1 << WDCE)|(1 << WDE);
  WDTCSR = (1 << WDIE)|(1 << WDP3);     // 4 sec
}
//---------------------------------------------------------------
ISR(WDT_vect){
  wakeUpflag = true;
  Task.UpdateSch();
}

