/*
 Dynamixel Reg Action Example
 
 This example shows how to use reg/action instruction
 Open serial monitor and type 'a' on keyboard
 you can check moving dynamixel, type 'a' again -> moves its origin postion 0

 You can buy DYNAMIXEL in ROBOTIS-SHOP
 [KOREAN]
 http://www.robotis-shop-kr.com/goods_list.php?Index=273
 [English]
 http://www.robotis-shop-en.com/shop/step_submain.php?b_code=B20070914050547
 
  You can also find all information about DYNAMIXEL
  http://support.robotis.com/
  
 Ported to CM9 from the ROBOTIS E-manual 21 Oct 2012
*/

void setup(){
  Dxl.begin(1);
}
char temp;// need to receive from USB(PC)
uint32 GoalPos = 0;

void loop(){
  Dxl.setTxPacketId(1); // ID 1 is set, insert your dynamixel id
  Dxl.setTxPacketInstruction(INST_REG_WRITE);//save instruction and value in ID 1 dynamixel
  //Parameter start
  Dxl.setTxPacketParameter(0, 30);//30 is goal position control table, refer support.robotis.com
  Dxl.setTxPacketParameter(1, Dxl.getLowByte(GoalPos));  // Low Byte
  Dxl.setTxPacketParameter(2, Dxl.getHighByte(GoalPos)); // High Byte
  //Parameter end, so N is 3-> 3+2 =  5
  Dxl.setTxPacketLength(5);// calculate instruction length, N(Number of parameters) + 2
  Dxl.txrxPacket();
  if( Dxl.getResult() == COMM_RXSUCCESS )
    SerialUSB.println("Success");
 
  delay(100);
  if(SerialUSB.available()){
    temp = SerialUSB.read();
    if(temp == 'a'){
      SerialUSB.println("Reg Action");//Now start move dynamixel
      Dxl.setTxPacketId(BROADCAST_ID);
      Dxl.setTxPacketInstruction(INST_ACTION);
      Dxl.setTxPacketLength(2);//This case is no parameter, so length is 0+2=2
      Dxl.txrxPacket();
      if( Dxl.getResult() == COMM_RXSUCCESS ){
          SerialUSB.println("Comm Success");
          if(GoalPos == 0)
            GoalPos = 1023;
          else
            GoalPos = 0;
      }
      else
          SerialUSB.println("Comm Fail");

    }
  }

}
