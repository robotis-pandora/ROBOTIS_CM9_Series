/*
 OLLO Color Sensor example
 
 Read RGB Color ADC value from OLLO Color Sensor module on CM-904.
 connect OLLO Color Module to port 1.
 
 Created to CM9 by ROBOTIS,.LTD. 30 MAY 2013
 */

#include <OLLO.h>
OLLO myOLLO;

void setup(){
  myOLLO.begin(1);//Gyro X Axis must be connected at port 2.
 // myOLLO.begin(2);//Gyro Y Axis must be connected at port 2.
}
void loop(){
  SerialUSB.print("RED ADC = ");
  SerialUSB.print(myOLLO.readColor(1,RED)); 
  SerialUSB.print("  GREEN ADC = ");
  SerialUSB.print(myOLLO.readColor(1,GREEN));
  SerialUSB.print("  BLUE ADC = ");
  SerialUSB.println(myOLLO.readColor(1,BLUE));
  
  delay(60);
}


