/*
  Dynamixel SyncWrite exmaples

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

#define P_GOAL_POSITION_L   30
#define P_GOAL_POSITION_H   31
#define P_GOAL_SPEED_L      32
#define P_GOAL_SPEED_H      33

#define NUM_ACTUATOR        5 // Number of actuator
#define CONTROL_PERIOD      (1000) // msec (Large value is more slow)
#define MAX_POSITION        1023

word  AmpPos = 512;
word  wPresentPos;
word  GoalPos = 0;
byte  id[NUM_ACTUATOR];
byte  CommStatus;
byte  i;

void setup() {
  Dxl.begin(1);
  SerialUSB.begin();
  //Insert dynamixel ID number to array id[]
  for(i=0; i<NUM_ACTUATOR; i++ ){
    id[i] = i+1;
  }
  // Set goal speed
  Dxl.writeWord( BROADCAST_ID, P_GOAL_SPEED_L, 0 );
  // Set goal position
  Dxl.writeWord( BROADCAST_ID, P_GOAL_POSITION_L, AmpPos );
  delay(1000);
}

void loop() {
// Make syncwrite packet
  Dxl.setTxPacketId(BROADCAST_ID);
  Dxl.setTxPacketInstruction(INST_SYNC_WRITE);
  Dxl.setTxPacketParameter(0, P_GOAL_POSITION_L);
  Dxl.setTxPacketParameter(1, 2);
  
  for( i=0; i<NUM_ACTUATOR; i++ ){
    Dxl.setTxPacketParameter(2+3*i, id[i]);
    Dxl.setTxPacketParameter(2+3*i+1, Dxl.getLowByte(GoalPos));
    Dxl.setTxPacketParameter(2+3*i+2, Dxl.getHighByte(GoalPos));
    
    SerialUSB.println(GoalPos);
  }
  Dxl.setTxPacketLength((2+1)*NUM_ACTUATOR+4);
  Dxl.txrxPacket();

  CommStatus = Dxl.getResult();
  //SerialUSB.print("CommSatus = ");SerialUSB.println(CommStatus);
  if( CommStatus == COMM_RXSUCCESS ){
    PrintCommStatus(CommStatus);
  }
  else{
    PrintErrorCode();
  }
  GoalPos += 100;
  
  if( GoalPos > MAX_POSITION )
    GoalPos -= MAX_POSITION;
  delay(CONTROL_PERIOD);

}
// Print communication result
void PrintCommStatus(int CommStatus)
{
  switch(CommStatus){
    case COMM_TXFAIL:
      SerialUSB.println("COMM_TXFAIL: Failed transmit instruction packet!");
      break;
    
    case COMM_TXERROR:
      SerialUSB.println("COMM_TXERROR: Incorrect instruction packet!");
      break;
    
    case COMM_RXFAIL:
      SerialUSB.println("COMM_RXFAIL: Failed get status packet from device!");
      break;
    
    case COMM_RXWAITING:
      SerialUSB.println("COMM_RXWAITING: Now recieving status packet!");
      break;
    
    case COMM_RXTIMEOUT:
      SerialUSB.println("COMM_RXTIMEOUT: There is no status packet!");
      break;

    case COMM_RXCORRUPT:
      SerialUSB.println("COMM_RXCORRUPT: Incorrect status packet!");
      break;
  
    default:
      SerialUSB.println("COMM_RXSUCCESS");
      break;
    }
}

// Print error bit of status packet
void PrintErrorCode()
{
  if(Dxl.getRxPacketError(ERRBIT_VOLTAGE) == 1)
    SerialUSB.println("Input voltage error!");
  
  if(Dxl.getRxPacketError(ERRBIT_ANGLE) == 1)
    SerialUSB.println("Angle limit error!");
  
  if(Dxl.getRxPacketError(ERRBIT_OVERHEAT) == 1)
    SerialUSB.println("Overheat error!");
  
  if(Dxl.getRxPacketError(ERRBIT_RANGE) == 1)
    SerialUSB.println("Out of range error!");
  
  if(Dxl.getRxPacketError(ERRBIT_CHECKSUM) == 1)
    SerialUSB.println("Checksum error!");
  
  if(Dxl.getRxPacketError(ERRBIT_OVERLOAD) == 1)
    SerialUSB.println("Overload error!");
  
  if(Dxl.getRxPacketError(ERRBIT_INSTRUCTION) == 1)
    SerialUSB.println("Instruction code error!");
}





