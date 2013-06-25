/*
 Dynamixel Wheel Mode Example
 
 Turns left the dynamixel , then turn right for one second,
 repeatedly.
 Dynamixel constants and control table are declared in below header
 work\hardware\robotis\cores\robotis\dxl_constants.h
 
 You can buy DYNAMIXEL in ROBOTIS-SHOP
 [KOREAN]
 http://www.robotis-shop-kr.com/goods_list.php?Index=273
 [English]
 http://www.robotis-shop-en.com/shop/step_submain.php?b_code=B20070914050547
 
 You can also find all information about DYNAMIXEL
 http://support.robotis.com/
 
 Ported to CM9 from the ROBOTIS E-manual 21 Oct 2012
 */

void setup() {
  // Initialize the dynamixel bus:
  Dxl.begin(1);
  Dxl.writeWord(1, 8, 0); //disable CCW Angle Limit(L) to use wheel mode
}

void loop() {
  Dxl.writeWord(1, 32, 400); 
  delay(5000);
  Dxl.writeWord(1, 32, 400 | 0x400); //reverse
  delay(5000); 
  Dxl.writeWord(1, 32, 0); //stop
  delay(2000);
}
