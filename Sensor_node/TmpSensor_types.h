#ifndef TMP_SEN_TYPES_H
#define TMP_SEN_TYPES_H
//---------------------------------------------------------------
#include "types.h"
#include <OneWire.h>
#include <DallasTemperature.h>
//---------------------------------------------------------------
class TMP_SENSOR{
private:
  OneWire oneWire;            // Setup a oneWire instance to communicate with any OneWire devices 
  DallasTemperature sensors;  // Pass our oneWire reference to Dallas Temperature. 
public:   
  TMP_SENSOR();
  void Start(void);
  FLOAT GetData(void);
};
#endif
