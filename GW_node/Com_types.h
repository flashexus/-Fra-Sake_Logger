#ifndef COM_TYPES_H
#define COM_TYPES_H
#include "types.h"
//---------------------------------------------------------------
//Packet Format
typedef struct{
  STR   HeaderData;
  FLOAT TmpData;
  STR   SensorID;
}COM_TMP_DATA;    //*end code = CRLF

//---------------------------------------------------------------
class COM{
public: 
  COM();
  void Start(void);
  void SendTmpData(FLOAT SendData);
  BOOL RecvTmpData();
  BOOL CheckRcvData(void);
  void RelayComData(void);
private: 
  COM_TMP_DATA ComTxData;
  STR ComRxData;
  UINT RxData_cnt;
  CHAR RxData_buffer[MAX_DATA_SIZE];
  void PackTxData(FLOAT SendData);
  BOOL GetAndRelayData(void);
  void UnPackRxData(void);
  BOOL ValidateRxData(void);
};

#endif //COM_TYPES_H
