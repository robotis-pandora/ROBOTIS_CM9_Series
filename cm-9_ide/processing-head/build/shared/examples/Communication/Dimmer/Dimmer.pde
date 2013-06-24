/*
  Dimmer

  Demonstrates sending data from the computer to the CM-9, in this
  case to control the brightness of an LED.  The data is sent in
  individual bytes, each of which ranges from 0 to 255.  CM-9 reads
  these bytes and uses them to set the brightness of the LED.

  The circuit:
  LED must be connected to Pin 6 in CM-9 board as current sink
  
  created 2006
  by David A. Mellis
  modified 14 Apr 2009
  by Tom Igoe and Scott Fitzgerald

  http://leaflabs.com/docs/lang/api/pwmwrite.html

  Ported to the Maple 28 May 2010
  Ported to the Maple 15 Nov 2012
*/

int ledPin = 6;

void setup() {
    // Declare ledPin as an OUTPUT:
    pinMode(ledPin, PWM);
}

void loop() {
    int brightness;
    int temp=0;

    // Check if data has been sent from the computer:
    if (SerialUSB.available()) {
        // Read the most recent byte (which will be from 0 to 255), then
        // convert it to be between 0 and 65,535, which are the minimum
        // and maximum values usable for PWM:
        brightness = map(SerialUSB.read(), 0, 255, 0, 65535);
        // Set the brightness of the LED:
        pwmWrite(ledPin, brightness);
    }
}
