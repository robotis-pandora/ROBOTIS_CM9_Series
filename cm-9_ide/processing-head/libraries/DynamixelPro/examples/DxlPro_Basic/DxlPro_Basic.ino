#include <DynamixelPro.h>
DynamixelPro DxlEx;

void setup() {
  DxlEx.begin(1);
  Serial2.begin(57600);
  //Toque on to move dynamixel pro
  DxlEx.writeByte(1,562,1);
}

void loop() {

  //Turn on green LED in DXL PRO
  DxlEx.writeByte(1,564,255);
  //Move to goal position 151875 refer to position limit
  DxlEx.writeDword(1,596,151875);
  delay(2000);
  //Turn off green LED in DXL PRO
  DxlEx.writeByte(1,564,0);
  //Move to goal position -151875 refer to position limit
  DxlEx.writeDword(1,596,-151875);

  delay(2000);
  //Read DXL internal temperature
  Serial2.print(" DXL PRO Temperature = ");
  Serial2.println(DxlEx.readByte(1,625));

}


