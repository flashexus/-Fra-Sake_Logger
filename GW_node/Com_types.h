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
  void RelayComData(void);
  BOOL RcvTmpData(void);
  BOOL CheckRcvData(void);
private: 
  COM_TMP_DATA ComTxData;
  STR ComRxData;
  UINT RxData_cnt;
  CHAR RxData_buffer[MAX_DATA_SIZE];
  void PackTxData(FLOAT SendData);
  void UnPackRxData(void);
  BOOL ValidateRxData(void);
  BOOL GetData(void);
};
#endif //COM_TYPES_H
