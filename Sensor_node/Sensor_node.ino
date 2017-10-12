#include "types.h"
#include "Com.h"
#include "TmpSensor.h"
#include "Task_Sch.h"
//---------------------------------------------------------------
#define LED_PIN       (13)
//---------------------------------------------------------------
void setup() {
  pinMode(LED_PIN, OUTPUT);           //for debug
  TmpSensor.Start();
  Com.Start();  
}
//---------------------------------------------------------------
void loop() {
//  digitalWrite(LED_PIN,HIGH);    
  Task.sch();
//  digitalWrite(LED_PIN,LOW);  
  delay(100);                         //スリープからの復帰時調整用時間（必須）
}
//---------------------------------------------------------------
void Task_Sensing(void){
  FLOAT TmpData; 
  TmpData = TmpSensor.GetData();      //Get Temperature
  Com.SendTmpData(TmpData);           //Send Data     
}

