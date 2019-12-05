#include <Wire.h>
#include "SparkFun_5P49V60.h"

SparkFun_5P49V60 clockGen;

void setup(){

  Wire.begin();
  Serial.begin(115200);

  if (clockGen.begin() == true){
    Serial.println("Clock Generator Ready.");
  }
  else {
    Serial.println("Could not communicate with the SparkFun Clock Generator.");
    while(1);
  }

  uint8_t address = clockGen._readRegister(0x10);
  Serial.println(address, BIN);
  
  clockGen.bypassRefDivider(ENABLE);
  clockGen._readRegister(DIVIDER_VCO_REG);

}

void loop(){
 delay(100); 
}
