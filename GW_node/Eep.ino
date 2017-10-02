#include <EEPROM.h>

UINT   eeAddress;
//--------------------------------------------------
void Eep_SaveData(UINT eep_data_cnt,  CHAR* inputData){
  UINT write_data_cnt;
  write_data_cnt = 0;
  do {
    EEPROM.write(eeAddress, inputData[write_data_cnt]);
    eeAddress ++;
    write_data_cnt++;
    delay(5);
  } while ( write_data_cnt != eep_data_cnt );
  digitalWrite(LED_PIN, LOW);
}
//--------------------------------------------------
void Eep_ReadData(void)
{
  CHAR eepData;                     //Variable to store data read from EEPROM.
  INT eeAddress;                    //EEPROM address to start reading from  

  //Get the float data from the EEPROM at position 'eeAddress'
  EEPROM.get(eeAddress, eepData);
  Serial.println(eepData);          //This may print 'ovf, nan' if the data inside the EEPROM is not a valid float.
  eeAddress += sizeof(eepData);     //Move address to the next byte after float 'f'.

  if(eeAddress > 512){              //for debug
    Serial.end();
  }
}
