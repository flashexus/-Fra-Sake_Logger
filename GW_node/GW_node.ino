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
  Com.RelayComData();
}
//--------------------------------------------------
void loop() {
  if (Com.CheckRcvData() == true){
    if(Com.RcvTmpData() == true){
      GW_SendData();
    }
  }    
  delay(POLLING_TIMING);
}
