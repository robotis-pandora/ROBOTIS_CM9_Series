/*
 Configuration Debug Ports
 This example how to configure JTAG debug ports(11,12,13,17,18).
 If declared as disableDebugPorts(), do not use ST-LINK or any JTAG dongles.
 So, if you need JTAG/SWD debugger, must declare enableDebugPorts().
 
 Created by ROBOTIS,.LTD.
*/
void setup(){
  /* Pin 11, 12, 13, 17, 18 must be used with the below option*/
  disableDebugPorts(); // if you want to use JTAG, set to enableDebugPorts();
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(18, OUTPUT);  
}
void loop(){
  /* Just make pulse using delay() and digital output*/
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(17, HIGH);
  digitalWrite(18, HIGH);
  delay(50);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  digitalWrite(17, LOW);
  digitalWrite(18, LOW);
  delay(50);
  
}
