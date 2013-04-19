/*
 Dynamixel setPosition Example

 Turns left the dynamixel , then turn right for one second,
 repeatedly with different velocity.

 setPosition method is made by Martin S. Mason(Professor @Mt. San Antonio College)

 Created to CM9 series by ROBOTIS,.LTD.
*/
void setup() {
  /*Initialize as 1Mbps baud rate*/
  Dxl.begin(1);
}

void loop() {
  /*ID 1 dynamixel moves to position 0 with velocity 100*/
  Dxl.setPosition(1,0,100);
  delay(1000);// it has more delay time for slow movement
  /*ID 1 dynamixel moves to position 500 with velocity 300*/
  Dxl.setPosition(1,500,300);
  delay(500);
}
