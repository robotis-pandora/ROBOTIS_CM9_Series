/*
 OLLO Button interrupt example
 
 When push OLLO button, toggle built-in LED using external interrupt on CM-904.
 connect OLLO Button Module to port 2.
  
 Created to CM9 by ROBOTIS,.LTD. 30 MAY 2013
 */

#include <OLLO.h>
OLLO myOLLO;

void setup(){
  myOLLO.beginButton(2,pin3int);//OLLO Button Module must be connected at port 2.
  pinMode(BOARD_LED_PIN,OUTPUT);
}
void pin3int(void){
  toggleLED();
}
void loop(){
}




