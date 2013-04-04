/*
  Dynamixel read/write exmaples

  Reads an dynaixel current position, and set goal position
  turn left and right repeatly. 

 You can buy DYNAMIXEL in ROBOTIS-SHOP
 [KOREAN]
 http://www.robotis-shop-kr.com/goods_list.php?Index=273
 [English]
 http://www.robotis-shop-en.com/shop/step_submain.php?b_code=B20070914050547
 
  You can also find all information about DYNAMIXEL
  http://support.robotis.com/

  created 14 Nov. 2012  ported to CM9  by ROBOTIS
*/


#define P_GOAL_POSITION_L     30
#define P_GOAL_POSITION_H     31
#define P_PRESENT_POSITION_L  36
#define P_PRESENT_POSITION_H  37
#define P_MOVING              46

word  Position;
word  wPresentPos;
byte  INDEX = 0;
byte  bMoving, CommStatus;
byte  id = 1;
word  GoalPos[2] = {0, 1023};

void setup() {
  Dxl.begin(1);
  //print to USART2 Zigbee port
  SerialUSB.begin();
}

void loop() {
  bMoving = Dxl.readByte( id, P_MOVING);
  CommStatus = Dxl.getResult();
  if( CommStatus == COMM_RXSUCCESS ){
    if( bMoving == 0 ){
      // Change goal position
      if( INDEX == 0 )
       	INDEX = 1;
      else
      	INDEX = 0;
      // Write goal position
      Dxl.writeWord( id, P_GOAL_POSITION_L, GoalPos[INDEX] );
    }
    // Read present position
    wPresentPos = Dxl.readWord( id, P_PRESENT_POSITION_L );
    SerialUSB.print("Goal Position : ");
    SerialUSB.println(GoalPos[INDEX]);
    SerialUSB.print("Present position :");
    SerialUSB.println(wPresentPos);
    SerialUSB.println("Success");
  }else {
    SerialUSB.println("Fail");
  }
  delay(1000);
}

