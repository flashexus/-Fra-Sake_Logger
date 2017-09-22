//---------------------------------------------------------------
//Tmp Sensor Module 
//TargetDevice:DS18B20
//Connect to Arduino + GAMMA Shield 
//   Arduino            Sensor 
//    D12               DQ(White Line)
//    Power(5V)         PullUpRegist(4.7K ohm)    
//    GND               GND(Red Line)
//
//---------------------------------------------------------------
#include "TmpSensor.h"
//---------------------------------------------------------------
#define SENSOR_PIN    (12)
#define ONE_WIRE_BUS  (SENSOR_PIN)
//---------------------------------------------------------------
TMP_SENSOR TmpSensor;                             //Instance
//---------------------------------------------------------------
TMP_SENSOR::TMP_SENSOR():
    oneWire(ONE_WIRE_BUS),sensors(&oneWire)
{
  }
//---------------------------------------------------------------
void TMP_SENSOR::Start(void){
  sensors.begin();                                // Start up the library
}
//---------------------------------------------------------------
FLOAT TMP_SENSOR::GetData(void){
  sensors.requestTemperatures();                  // Send the command to get temperatures
  //Serial.println(sensors.getTempCByIndex(0));   // for debug
  return sensors.getTempCByIndex(0);
}
