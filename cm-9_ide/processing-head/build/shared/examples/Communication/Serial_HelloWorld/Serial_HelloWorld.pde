/*
  Bluetooth port print out "Hello World!!" to PC 
  You can see it any terminal program, putty, TeraTerm, Hyper Terminal, etc...

  CM900's USART2 pins(2,3) are connected to Bluetooth/Zigbee connector.
  To use bluetooth or zigbee on CM900, you can buy BT110(Bluetooth) or Zig110(Zigbee) as option
  
  You can connect the below products to J9 Connector in CM-900
  [BT-110A] or [BT-110A Set]
  http://www.robotis-shop-kr.com/goods_detail.php?goodsIdx=875
  [ZIG-110A Set]
  http://www.robotis-shop-kr.com/goods_detail.php?goodsIdx=405
  [LN-101] download tool in CM-100
  http://www.robotis-shop-kr.com/goods_detail.php?goodsIdx=348
    
  You can also find all information about ROBOTIS products
  http://support.robotis.com/
  
  created 14 Nov. 2012 by ROBOTIS
*/

void setup() {
  //Initialize Serial2
  Serial2.begin(57600);
}
int nCount=0;
void loop() {
    //print "Hello World!!" to PC though Serial2
    Serial2.println("Hello World!!");
    Serial2.print("nCount : "); // display nCount variable and increase nCount.
    Serial2.println(nCount++);
    delay(1000);
}

