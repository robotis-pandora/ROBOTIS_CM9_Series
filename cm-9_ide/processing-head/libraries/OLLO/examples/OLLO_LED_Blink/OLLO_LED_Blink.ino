/*
 OLLO LED Module example

 Blink OLLO LED Module on CM-904(not CM-900), it has 4 OLLO 5Pin port
 connect LED Module to port 3.

 You can buy DYNAMIXEL in ROBOTIS-SHOP
  http://www.robotis-shop-en.com/shop/step1.php?number=751&b_code=B20070914051413&c_code=C20100528064118 
  You can also find all information 
  http://support.robotis.com/
  
 Created to CM9 by ROBOTIS,.LTD. 30 MAY 2013
*/

#include <OLLO.h>
OLLO myOLLO;

void setup(){
  myOLLO.begin(3);//LED Module must be connected at port 3.
}
void loop(){
  //writeLED( port number, left LED(blue), right LED(yellow) )
  myOLLO.writeLED(3,1,0);
  delay(100);
  myOLLO.writeLED(3,0,1);
  delay(100);
}


