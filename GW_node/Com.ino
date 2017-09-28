#include "arduino.h"
#include "Com.h"
//---------------------------------------------------------------
#define BOUND_RATE      (9600)                 //GAMMA側の設定と合わせる必要があるためコンフィグにしない

COM Com;                                       //Instance
//---------------------------------------------------------------
COM::COM()
{
  RxData_cnt = 0;
  
  UINT roop_num;
  for ( roop_num = 0; roop_num < MAX_DATA_SIZE; roop_num++) {
    RxData_buffer[roop_num] = 0U;
  }
}
//---------------------------------------------------------------
void COM::Start(void)
{
    ComTxData.HeaderData = "AAAA";             //Set Header Data
    randomSeed(RANDOM_SEED_CH);    
    ComTxData.SensorID = String(random(
              ID_MIN_LIMIT,ID_MAX_LIMIT),HEX); //Set Sensor ID
    Serial.begin(BOUND_RATE);                 //Start LoRa Commnucation
}
//---------------------------------------------------------------
void COM::PackTxData(FLOAT SendData)
{
    ComTxData.TmpData = SendData;            
}
//---------------------------------------------------------------
void COM::SendTmpData(FLOAT SendData)
{
    PackTxData(SendData);                     //Set Tmp Data
    //--------------Send Packet--------------------
    Serial.print(ComTxData.HeaderData);
    Serial.print(ComTxData.TmpData);
    Serial.println(ComTxData.SensorID);
}
//---------------------------------------------------------------
BOOL COM::CheckRcvData(void) {
  UINT inputchar;
  BOOL Com_RcvData_flag = false;

  inputchar = Serial.available();
  if (inputchar != 0) {
    Com_RcvData_flag = true;
    Com.RxData_cnt = inputchar;
    digitalWrite(LED_PIN, HIGH);
  }
  return Com_RcvData_flag;
}
//---------------------------------------------------------------
BOOL COM::RecvTmpData(void)
{
  if(GetData() == true){  
    UnPackRxData();
  }
  return ValidateRxData();
}
//---------------------------------------------------------------
//全てのデータを受信仕切っていることを保証する
BOOL COM::GetData(void) {
  UINT rcv_data_cnt;
  rcv_data_cnt = 0;
  do{
    RxData_buffer[rcv_data_cnt] = Serial.read();
    Serial.write((RxData_buffer[rcv_data_cnt]));  //for debug
    rcv_data_cnt++;
//  } while ( inputData[rcv_data_cnt] != -1 );
  } while ( rcv_data_cnt != Com.RxData_cnt );

  return (!CheckRcvData());
}
//---------------------------------------------------------------
//受信データを温度情報用のオブジェクトに展開する
void COM::UnPackRxData(void){
//ComRxData 構造体　←　Char配列
  String tmp = (String (&RxData_buffer[0]));
  memcpy( &ComRxData, &tmp,sizeof(COM_TMP_DATA) );
  Serial.print(ComRxData);
}
//---------------------------------------------------------------
//受信した温度情報用のオブジェクトをチェックする
BOOL COM::ValidateRxData(void){
  return true;  
}


