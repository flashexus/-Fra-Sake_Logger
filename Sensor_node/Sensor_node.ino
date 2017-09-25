#include "types.h"
#include "Com.h"
#include "TmpSensor.h"
//---------------------------------------------------------------
#define SENSING_TIME  (6000)
#define LED_PIN       (13)
//---------------------------------------------------------------
void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT); //for debug
  TmpSensor.Start();
  Com.Start();  
}
//---------------------------------------------------------------
void loop() {
  // put your main code here, to run repeatedly:
  FLOAT TmpData;
  
  TmpData = TmpSensor.GetData();      //Get Temperature
  Com.SendTmpData(TmpData);           //Send Data
  delay(SENSING_TIME);                //Wait Sense Timing

}
