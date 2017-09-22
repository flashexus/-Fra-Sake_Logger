#include "arduino.h"
#include "Com.h"
//---------------------------------------------------------------
#define BOUND_RATE  9600
COM Com;                                       //Instance
//---------------------------------------------------------------
COM::COM()
{
    ComTmpData.HeaderData = "AAAA";            //Set Header Data
}
//---------------------------------------------------------------
void COM::Start(void)
{
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
    Serial.println(ComTmpData.TmpData);
}
