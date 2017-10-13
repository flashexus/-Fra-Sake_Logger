#include "types.h"
#include "Com.h"
#include "TmpSensor.h"
#include "Task_Sch.h"
//---------------------------------------------------------------
#define LED_PIN           (13)
#define TASK0_PERIOD_PIN  (9)
#define TASK0_PERMIT_PIN  (8)
#define TASK2_PERMIT_PIN  (7)
#define APPEAL_TIME       (5000)
//---------------------------------------------------------------
typedef struct{
  ULONG task_period;
  BOOL  task_permit_flag;
}TASK_PRAM;
//---------------------------------------------------------------
void setup() {
  TmpSensor.Start();
  Com.Start();  
  pinMode(LED_PIN, OUTPUT);    
  digitalWrite(LED_PIN,LOW);
}
//---------------------------------------------------------------
void loop() {
  Task.sch();
  delay(100);                         //スリープからの復帰時調整用時間（必須）
}
//---------------------------------------------------------------
void Task_Sensing(void){
  FLOAT TmpData; 
  
  TmpData = TmpSensor.GetData();      //Get Temperature
  Com.SendTmpData(TmpData);           //Send Data     
}
//---------------------------------------------------------------
void Task_UpdateOrder(void){
  volatile TASK_PRAM task_pram[MAX_TASK_NUM];
  GetParam(task_pram);
  
  Update_Config(task_pram);
}
//---------------------------------------------------------------
void Task_SelfAppeal(void){
    pinMode(LED_PIN, OUTPUT);               
    digitalWrite(LED_PIN,HIGH);    
}
//---------------------------------------------------------------
void GetParam(TASK_PRAM* task_pram){
  pinMode(TASK0_PERIOD_PIN, INPUT);           
  pinMode(TASK0_PERMIT_PIN, INPUT);           
  pinMode(TASK2_PERMIT_PIN, INPUT);           

//  task_pram[0].task_period = TASK1_TIME_DEBUG;
//  task_pram[0].task_permit_flag = true; 

  if( digitalRead(TASK0_PERIOD_PIN) == LOW){
    task_pram[0].task_period = TASK1_TIME_DEBUG;
  }else{
    task_pram[0].task_period = TASK1_TIME_SHORT;
  }
  if( digitalRead(TASK0_PERMIT_PIN) == LOW){
    task_pram[0].task_permit_flag = true; 
  }else{
    task_pram[0].task_permit_flag = false;
  }

  task_pram[1].task_period = TASK2_TIME;
  task_pram[1].task_permit_flag = true;
  
  task_pram[2].task_period = TASK3_TIME;
  task_pram[2].task_permit_flag = false;
  
  if( digitalRead(TASK2_PERMIT_PIN) == HIGH){  
    task_pram[2].task_permit_flag = true; 
  }else{
    task_pram[2].task_permit_flag = false;
  }

}
//---------------------------------------------------------------
void Update_Config(TASK_PRAM* task_pram){
  UINT task_num;
 
  for(task_num = 0; task_num < MAX_TASK_NUM; task_num++){
    //タスクの実行周期の更新
    Task.Update_TaskPeriod(task_num,task_pram[task_num].task_period);

    //タスクの実行許可フラグの更新
    Task.Update_TaskPermission(task_num,task_pram[task_num].task_permit_flag);
  }
}

