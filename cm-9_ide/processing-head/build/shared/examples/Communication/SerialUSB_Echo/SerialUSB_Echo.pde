/*
  Echo

  Demonstrates sending data from the computer to the CM900,
  echoes it to the computer again.
  You can just type in terminal program, character you typed will be displayed
  
  
  created 16 Nov 2012
  by Sangmin Lee

*/

void setup(){
  //USB Serial initialize
  SerialUSB.begin();
}
void loop(){
  // when you typed any character in terminal
  if(SerialUSB.available()){
      //print it out though USB
      SerialUSB.print((char)SerialUSB.read());
  }
}