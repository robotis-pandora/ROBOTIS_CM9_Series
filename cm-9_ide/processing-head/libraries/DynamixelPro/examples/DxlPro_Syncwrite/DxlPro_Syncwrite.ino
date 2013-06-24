#include "DynamixelPro.h"
DynamixelPro DxlEx;

int itemp1[3];
int itemp2[3];
void setup() {
  DxlEx.begin(5);
  Serial2.begin(57600);
  DxlEx.writeByte(1,562,1);
  itemp1[0] = 1;
  itemp1[1] = 151875; //goal posiotion 1
  itemp1[2] = 10000;  //velocity 1

  itemp2[0] = 1;
  itemp2[1] = -151875; //goal position 2
  itemp2[2] = 5000;  //velocity 2

}
void loop(){
  DxlEx.syncWrite(596,2,itemp1,3);
  delay(3000);
  DxlEx.syncWrite(596,2,itemp2,3);
  delay(3000);
}

