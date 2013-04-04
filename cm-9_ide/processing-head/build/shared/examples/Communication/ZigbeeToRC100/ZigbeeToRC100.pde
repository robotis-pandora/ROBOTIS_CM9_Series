/*
  Zigbee to RC100 remote control

  Demonstrates communication the CM-900 and RC100,
  RC100 is a remote controller made by ROBOTIS.
  You can buy it the link below.(Korea only)
  [RC-100] Controller like joystick
  http://www.robotis-shop-kr.com/goods_detail.php?goodsIdx=817
  
  You can connect the below products to RC-100 in CM-900
  [BT-110A] or [BT-110A Set]
  http://www.robotis-shop-kr.com/goods_detail.php?goodsIdx=875
  [ZIG-110A Set]
  http://www.robotis-shop-kr.com/goods_detail.php?goodsIdx=405
  [LN-101] download tool in CM-100
  http://www.robotis-shop-kr.com/goods_detail.php?goodsIdx=348
    
  You can also find all information about ROBOTIS products
  http://support.robotis.com/
  
  created 19 Dec 2012 by ROBOTIS
*/
void setup() {
  pinMode(BOARD_LED_PIN, OUTPUT);
  afio_cfg_debug_ports(AFIO_DEBUG_NONE);
  zgbInitialize(0);
  SerialUSB.begin();
}
int RcvData =0;

void loop() {
	
  if(zgbRxCheck() == 1){
      RcvData = zgbRxData();
      SerialUSB.print("RcvData = ");
      SerialUSB.println(RcvData);
      
      if(RcvData & RC100_BTN_1)
      	digitalWrite(BOARD_LED_PIN,LOW);
      
      delay(100);
   }
  digitalWrite(BOARD_LED_PIN,HIGH);

}