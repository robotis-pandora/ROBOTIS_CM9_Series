/*
 Blink

 Turns on the built-in LED on for one second, then off for one second,
 repeatedly.

 Ported to CM9 Series from the Arduino example 27 May 2011
 By Sangmin Lee (ROBOTIS,.LTD.)
*/

void setup() {
    // Set up the built-in LED pin as an output:
    pinMode(BOARD_LED_PIN, OUTPUT);
}

void loop() {
    digitalWrite(BOARD_LED_PIN, HIGH);
    delay(100);          // Wait for 1 second (1000 milliseconds)
    digitalWrite(BOARD_LED_PIN, LOW);
    delay(100);          // Wait for 1 second (1000 milliseconds)
}
