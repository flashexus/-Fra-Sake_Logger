#ifndef COM_TYPES_H
#define COM_TYPES_H
#include "types.h"
//---------------------------------------------------------------
//Packet Format
typedef struct{
  STR   HeaderData;
  FLOAT TmpData;
  STR SensorID;
}COM_TMP_DATA;    //*end code = CRLF

//---------------------------------------------------------------
class COM{
public: 
  COM();
  void Start(void);
  void SendTmpData(FLOAT SendData);
private: 
  COM_TMP_DATA ComTmpData;
  void PackTxData(FLOAT SendData);  
};

#endif //COM_TYPES_H
