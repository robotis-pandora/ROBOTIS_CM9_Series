/*
 External Interrupt example
 Cicuit : 
   Toggle Button must be conneted Pin 5 with pull-down 3.3V
   ID 1 dynamixel is connected to TTL or RS485, anything is good.

 This example demonstrate how to use EXIT Interrupt with Dynamixel.
 If button is pushed, dynamixel connected moves to position 0. 
 If pushed again, it moves to position 500 repeatedly with LED blinking

 Created to CM9 series by ROBOTIS,.LTD.
*/
void setup(){
  Dxl.begin(1);
  //Button must be connected to Pin 5, also check if has pull-up or pull-down
  pinMode(5, INPUT_PULLUP);
  /*It can be choose as CHANGE, RISING or FALLING*/
  attachInterrupt(5,changeDirection, RISING);
}
/* If directionDxl is 1, other direction is 0*/
volatile byte directionDxl = 1;

void changeDirection(void){
  SerialUSB.print("Current direction = ");SerialUSB.println(directionDxl);

  if(directionDxl == 1){
    directionDxl = 0;
    Dxl.writeWord(1,32,0); // move to position 0
  }else{
    directionDxl = 1;
    Dxl.writeWord(1,32,500);// move to position 500
  }
}
void loop(){
  toggleLED();// bliking status LED on CM-9 board
  delay(100);
}
