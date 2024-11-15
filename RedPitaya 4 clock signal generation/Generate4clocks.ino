

/*
  This code first sets the internal oscillator to 3200MHz.
  It then sets the output for all Clocks to 125MHz. Finally the output MODE is set to LVDS (Low Voltage
  Differential Signaling). 

  Available Output Modes: 
  * LVPECL_MODE
  * CMOS_MODE  
  * HCSL33_MODE
  * LVDS_MODE  
  * CMOS2_MODE 
  * CMOSD_MODE 
  * HCSL25_MODE

  Pages from Hardware Datasheet of Interest: 
  Pg. 22 Transmission Output Termination Setup and Values

  SparkFun Electronics
  Date: July 2022
  Author: Michael Croquette
*/

#include <Wire.h>
#include "SparkFun_5P49V60.h"

// Uses default address at 0x6A, alternate available at 0x68
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
  
  
  // Fist, Setting the internal oscillator to a known value. 
  Serial.println("Setting Internal Clock Frequency to 3200MHz.");
  clockGen.setVcoFrequency(3200.0); // Give float value in MHz 

  // Clock One----------------------------------------------------
  // Use internal phase lock loop for clock output calculation.
  clockGen.resetClockOne();
  clockGen.muxPllToFodOne();
  Serial.println("Setting Output Mode for Clock One to LVDS.");
  // There are many OUTPUT modes available for each clock - this example uses
  // LVPECL (Low voltage Positive Emitter Coupled Logic) mode.
  clockGen.clockOneConfigMode(LVDS_MODE);
  Serial.println("Setting Clock One Frequency to 125MHz.");
  clockGen.setClockOneFreq(125.0); // Give float value in MHz, 125.0 = 125000000Hz or 125MHz
  clockGen.clockOneControl(ENABLE);
  
  // --------------------------------------------------------------

  // Clock Two--------------------------------------------------
  // Use internal phase lock loop for clock output calculation.
  clockGen.muxPllToFodTwo();
  Serial.println("Setting Output Mode for Clock Two to LVDS.");
  clockGen.clockTwoConfigMode(LVDS_MODE);
  Serial.println("Setting Clock Two Frequency to 125MHz.");
  clockGen.setClockTwoFreq(125.0); // Give float value in MHz, 125.0 = 125000000Hz or 125MHz
  clockGen.clockTwoControl(ENABLE);
  
  // -----------------------------------------------------------

   // Clock Three--------------------------------------------------
  // Use internal phase lock loop for clock output calculation.
  clockGen.muxPllToFodThree();
  Serial.println("Setting Output Mode for Clock Two to LVDS.");
  clockGen.clockThrConfigMode(LVDS_MODE);
  Serial.println("Setting Clock Two Frequency to 125MHz.");
  clockGen.setClockThrFreq(125.0); // Give float value in MHz, 125.0 = 125000000Hz or 125MHz
  // -----------------------------------------------------------

   // Clock Four--------------------------------------------------
  // Use internal phase lock loop for clock output calculation.
  clockGen.muxPllToFodFour();
  Serial.println("Setting Output Mode for Clock Two to LVDS.");
  clockGen.clockFourConfigMode(LVDS_MODE);
  Serial.println("Setting Clock Two Frequency to 125MHz.");
  clockGen.setClockFourFreq(125.0); // Give float value in MHz, 125.0 = 125000000Hz or 125MHz
  // -----------------------------------------------------------



}

void loop(){
  delay(1000); 
}
