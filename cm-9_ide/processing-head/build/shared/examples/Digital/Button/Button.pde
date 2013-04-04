/*
 Button

 Turns on and off the built-in LED when the button is
 pressed.

  Cirtuit:
  Pin 2 is connected to button 
  
 Ported to Maple from the Arduino example 27 May 2011
 by Marti Bolivar
 
  Ported to CM900 from the Maple example 15 Nov 2012
 by Sangmin Lee
*/

int buttonPin = 2; // Button pin is connected to pin 2

void setup() {
  // Initialize the built-in LED pin as an output:
  pinMode(BOARD_LED_PIN, OUTPUT);
  // Initialize pin 2 as an input:
  pinMode(buttonPin, INPUT);
}

void loop() {
    // Check if the button is pressed.
    if (isButtonPressed()) {
        // If so, turn the LED from on to off, or from off to on:
        toggleLED();
    }
}
