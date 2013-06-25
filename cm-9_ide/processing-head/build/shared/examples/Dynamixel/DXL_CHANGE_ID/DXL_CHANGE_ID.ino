/*
 *******************************************************************************
 *  Dynamixel ID Change Example
 *  Modified from Dynamixel Bus Scanner (CM-900 version) by NaN
 *******************************************************************************
 *
 */

// My gigantic dynamixel header file
#include <HaViMo2.h>

#define DXL_BAUDRATE_NUMBER 1  // number = 1 is 1000000 bps, 34 is 57600 bps
uint8 oldID=0;
uint8 newID=0;
void setup()
{
  SerialUSB.begin();
  Dxl.begin(DXL_BAUDRATE_NUMBER);

  pinMode(BOARD_LED_PIN, OUTPUT);

  // Waits 2 seconds for you to open the console (open too quickly after
  //   downloading new code, and you will get errors
  delay(2000);
  SerialUSB.print("Start Changing Dynamixel ID...\n");
  while(!SerialUSB.available())
  {
    delay(1000);
    digitalWrite(BOARD_LED_PIN, LOW);
    SerialUSB.print("Type current dxl ID...\n");
    delay(1000);
    digitalWrite(BOARD_LED_PIN, HIGH);
  }
  oldID = SerialUSB.read() - 48;
  SerialUSB.print("Current ID = ");SerialUSB.println(oldID);
  
  while(!SerialUSB.available())
  {
    delay(1000);
    digitalWrite(BOARD_LED_PIN, LOW);
    SerialUSB.print("Type new dxl ID...\n");
    delay(1000);
    digitalWrite(BOARD_LED_PIN, HIGH);
  }
  newID = SerialUSB.read() - 48;
  SerialUSB.print("New ID = ");SerialUSB.println(newID);
}

void loop()
{
  if(Dxl.writeByte(oldID,3,newID)){
    SerialUSB.print("Change successfully to new ID ");
    SerialUSB.println(newID);    
  }else{
    SerialUSB.println("Fail to change id!!");
  }
  // Indicate search is finished by toggling the LED endlessly
  while(1)
  {
    digitalWrite(BOARD_LED_PIN, LOW);
    delay(100);
    digitalWrite(BOARD_LED_PIN, HIGH);
    delay(100);
  }
}

