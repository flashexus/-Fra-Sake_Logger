#include "Com.h"
#include <EEPROM.h>

//-------------------------FixedParameter----------------------------
#define BOUND_RATE      (9600)                 //GAMMA,RaspPI側の設定と合わせる必要があるためコンフィグにしない
#define ID_MIN_LIMIT    (0x1000)               //必ず4桁欲しいため
#define ID_MAX_LIMIT    (0xFFFF)
#define EEP_WRITE_WAIT  (100)

COM Com;                                       //Instance
//---------------------------------------------------------------
///////////////////メンバ変数初期化//////////////////////////////
COM::COM()
{
  //----------------メンバ初期化---------------------
  RxData_cnt = 0U;
  memset(&ComRxData,'\0',sizeof(ComRxData));
  memset(RxData_buffer,'\0',MAX_DATA_SIZE);
}
//---------------------------------------------------------------
///////////////////シリアル通信開始//////////////////////////////
void COM::Start(void)
{
    //-----メソッドを使用して初期化する場合はこちらに記述する-------
    ComTmpData.HeaderData = TMP_DATA_HEADER;   //Set Header Data
    ComTmpData.SensorID = GetIDData();         //Set Sensor ID
    
    Serial.begin(BOUND_RATE);                 //Start LoRa Commnucation
}
//---------------------------------------------------------------
////////////////////送信データのパッキング////////////////////////
void COM::PackTxData(FLOAT SendData)
{
    ComTmpData.TmpData = SendData;            
}
//---------------------------------------------------------------
////////////////温度データのシリアル送信//////////////////////////
void COM::SendTmpData(FLOAT SendData)
{
    PackTxData(SendData);                     //Set Tmp Data
    //--------------Send Packet--------------------
    Serial.print(ComTmpData.HeaderData);
    Serial.print(ComTmpData.TmpData);
    Serial.println(ComTmpData.SensorID); 
}
//---------------------------------------------------------------
STR COM::GetIDData(void)
{
  UINT Node_ID_INT;
  STR Node_ID;
  
  EEPROM.get(NODE_ID_ADDRESS,Node_ID_INT);
   
  if(Node_ID_INT == EEP_BRANK_DATA){
    randomSeed(RANDOM_SEED_CH);
    Node_ID_INT =  random(ID_MIN_LIMIT,ID_MAX_LIMIT);
    
    EEPROM.put(NODE_ID_ADDRESS,Node_ID_INT);   
    delay(EEP_WRITE_WAIT);
  }
  Node_ID = STR(Node_ID_INT,HEX);       
  return Node_ID;
}
//---------------------------------------------------------------
//////////受信データがあればデータ数を格納、フラグTrue返却////////
BOOL COM::CheckRcvData(void){
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
///////受信データ取得後に展開し、バリデーション////////////////////
BOOL COM::RcvTmpData(void)
{
  if(GetData() == true){  
    UnPackRxData();
  }    
  return ValidateRxData();
}
//---------------------------------------------------------------
////////////全てのデータを受信仕切っていることを保証する///////////
BOOL COM::GetData(void) {
  UINT rcv_data_cnt;
  rcv_data_cnt = 0;
  do{
      RxData_buffer[rcv_data_cnt] = Serial.read();
//    Serial.write((RxData_buffer[rcv_data_cnt])); //for debug
      rcv_data_cnt++;
//  } while ( inputData[rcv_data_cnt] != -1 );    
  } while ( rcv_data_cnt != Com.RxData_cnt );      //受信可能なデータ数を格納
                                                   //ゴミデータは混ざらない想定
  return (!CheckRcvData());                        //受信可能データがない場合True
}
//---------------------------------------------------------------
///////////受信データを温度情報用のオブジェクトに展開する//////////
void COM::UnPackRxData(void){
//ComRxData 構造体　←　Char配列
  ComRxData = (String (&RxData_buffer[0]));
}
//---------------------------------------------------------------
//////////受信した温度情報用のオブジェクトをチェックする///////////
BOOL COM::ValidateRxData(void){
  //ひとまず素通し
  return true;  
}
//---------------------------------------------------------------
////////////////////シリアル通信の中継///////////////////////////
void COM::RelayComData(void){
  //中継機能は同じシリアルのチャンネル使用のみ対応
  Serial.print(ComRxData);
}

