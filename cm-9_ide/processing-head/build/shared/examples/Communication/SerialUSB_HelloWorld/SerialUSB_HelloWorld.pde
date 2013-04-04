/*
  USB Serial print "Hello World!!" to PC 
  You can see it any terminal program, putty, TeraTerm, Hyper Terminal, etc...


  created 14 Nov. 2012
  by Sangmin Lee

*/

void setup() {
  //Initialize USB Serial
  SerialUSB.begin();
}
int nCount=0;
void loop() {
    //print "Hello World!!" to PC though USB Virtual COM port
    SerialUSB.println("Hello World!!");
    SerialUSB.print("nCount : "); // display nCount variable and increase nCount.
    SerialUSB.println(nCount++);
    delay(1000);
}

