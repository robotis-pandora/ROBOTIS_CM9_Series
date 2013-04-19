/*
 Dynamixel Basic Example

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
}

void loop() {
    delay(500);              // Wait for 1 second (1000 milliseconds)
    Dxl.writeWord(1, 30, 0); //Turn dynamixel ID 1 to position 0
    delay(500);              // Wait for 1 second (1000 milliseconds)
    Dxl.writeWord(1, 30, 300);//Turn dynamixel ID 1 to position 300
}
