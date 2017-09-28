#include "Com.h"
//--------------------------------------------------
#define LED_PIN        (13)
#define POLLING_TIMING (2000)
//--------------------------------------------------
void setup() {
  // put your setup code here, to run once:
  //eeAddress = 0;
  pinMode(LED_PIN, OUTPUT);
  Com.Start();
}
//--------------------------------------------------
void GW_SendData(void) {
  //T.B.D
}
//--------------------------------------------------
void loop() {
  if (Com.CheckRcvData() == true){
    if(Com.RecvTmpData() == true){
      GW_SendData();
    }
  }    
  delay(POLLING_TIMING);
}