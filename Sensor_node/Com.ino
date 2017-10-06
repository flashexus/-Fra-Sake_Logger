#include "Com.h"
//---------------------------------------------------------------
#define BOUND_RATE      (9600)
#define ID_MIN_LIMIT    (0x1000)               //必ず4桁欲しいため
#define ID_MAX_LIMIT    (0xFFFF)
#define RANDOM_SEED_CH  (analogRead(0))

COM Com;                                       //Instance
//---------------------------------------------------------------
COM::COM()
{
}
//---------------------------------------------------------------
void COM::Start(void)
{
    ComTmpData.HeaderData = "AAAA";            //Set Header Data
    randomSeed(RANDOM_SEED_CH);    
    ComTmpData.SensorID = String(random(
              ID_MIN_LIMIT,ID_MAX_LIMIT),HEX); //Set Sensor ID
    Serial.begin(BOUND_RATE);                 //Start LoRa Commnucation
}
//---------------------------------------------------------------
void COM::PackTxData(FLOAT SendData)
{
    ComTmpData.TmpData = SendData;            
}
//---------------------------------------------------------------
void COM::SendTmpData(FLOAT SendData)
{
    PackTxData(SendData);                     //Set Tmp Data
    //--------------Send Packet--------------------
    Serial.print(ComTmpData.HeaderData);
    Serial.print(ComTmpData.TmpData);
    Serial.println(ComTmpData.SensorID); 
}
//---------------------------------------------------------------


