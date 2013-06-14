/*
  EEPROM Emulation Example
 
 Demonstrates how to use flash memory as EEPROM in CM9 board.
 Created by ROBOTIS,.LTD. 2013-06-12
 */

#include "EEPROM.h"
int i;
EEPROM CM9_EEPROM;
void setup(){
  
  CM9_EEPROM.begin();
  for(i=0;i < 10;i++){
    CM9_EEPROM.write(i,i*2);// write i*2 to virtual address 0~9
  }
}
void loop(){
  delay(1000);
  for(i=0;i < 10;i++){
    SerialUSB.print("EEPROM Address = ");SerialUSB.print(i);
    SerialUSB.print("  Data = ");SerialUSB.println(CM9_EEPROM.read(i));// read data from virtual address 0~9
  }
}

