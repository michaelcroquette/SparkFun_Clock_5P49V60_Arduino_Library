/*
  This example code first sets the internal oscillator to 1600MHz using the
  following equation:
  (Desired Frequency)/(Crystal Frequency) = Divider Value
  This value divides the Phase Lock Loop within the Clock Generator to get the
  desired internal voltage controlled oscillator frequency. 
  From here we can then use the equation for the OUTPUT divider to determine the
  OUTPUT value of Clock One:
  ((Internal Oscillator Frequncy)/2)/(Desired OUTPUT) = Divider Value
  Pages from Datasheet of Interest: 
  Pg. 22 Transmission Output Termination Setup and Values
  SparkFun Electronics
  Date: February, 2020
  Author: Elias Santistevan
*/

#include <Wire.h>
#include "SparkFun_5P49V60.h"

SparkFun_5P49V60 clockGen;
uint16_t feedBack; 

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


  // Fist, Setting the internal oscillator to a value that makes for easier
  // divisors (100 in this case).
  // PLL Divider - To get 1600MHz (1.6GHz): 1600MHz/16MHz (Clock) = 100
  clockGen.setPllFeedbackIntDiv(100);
  Serial.print("Feedback Integer Divider for PLL: ");
  Serial.println(clockGen.readPllFeedBackIntDiv());

  // Enable the VCO with the new settings. 
  // PLL will not take new settings without this function call.
  clockGen.calibrateVco();

  // Clock One -----------------------------------------------------
  // To get 16MHz Output = (1600MHz/2)/22MHz = 36.3636
  // Integer portion = 36
  // Fractional portion = .36 -> Need to convert to a HEX value
  // 2^24 * .36 = 6039796.76
  // Round the value to closest integer = 6039797
  clockGen.setIntDivOutOne(36);
  clockGen.setFractDivFodOne(6039797);
  Serial.print("FOD One Integer Divider: ");
  Serial.println(clockGen.readIntDivOutOne());
  Serial.print("FOD One Fractional Divider: ");
  Serial.println(clockGen.readFractDivFodOne());
  clockGen.muxPllToFodOne();
  // There are many OUTPUT modes available for each clock - this example uses
  // LVPECL (Low voltage Positive Emitter Coupled Logic) mode and terminates 
  // the clock with a 100Ohm resistance to GND.
  clockGen.clockOneConfigMode(LVPECL_MODE);
  clockGen.clockOneControl(ENABLE);
  // --------------------------------------------------------------

}

void loop(){
  delay(1000); 
}