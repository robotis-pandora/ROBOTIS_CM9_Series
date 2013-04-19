/*
  With the CM900, these pulses can easily be generated using the pwmWrite command.  
  There is no external hardware required, but it is STRONGLY recommended that 
  you use an external 5V power supply to generate the voltage for the servos. 
  I used a hextronics HX5010 servo for testing, which uses a JXT connector, 
  but have also included the Hitec pins below.
  
  Servo is attached as follows:
    Orange or White:  Digital Pin 23
    Black or Brown:  Ground on CM900 and External Power supply
    Red:  External power supply OR CM900 5V supply (Warning using the 5V supply on your CM900 could damage the CM900 or USB port!) 
  
   Basic servo control for full range movement
   Code written by Crenn adapted from ideas from Arduino Examples and Leaflabs Documentation
   Adapted to CM900 by Martin Mason http://www.profmason.com
   As usual full documentation is at: http://profmason.com/?p=1207
*/
#define SERVO 23  //This maps to CM900 Pin 23 which is on Timer 4
#define SERTIME 20

// Define the Servo upper and lower limits and also the servo prescaler
#define PRESCALE 22
#define UPPERLIMIT 7194
#define LOWERLIMIT 2616

// Measured period of the output signal in uS
#define PERIOD 20040

// Set SERVO pin to PWM mode and set the timer's prescaler
void setup(){
  pinMode(SERVO, PWM);
  Timer4.setPrescaleFactor(PRESCALE);
}

// Move the servo to one extreme then to the other
void loop(){
  for (int i=0; i<180;i++){
    pwmWrite(SERVO, map(i,0,180, LOWERLIMIT, UPPERLIMIT));
    delay(SERTIME);
  }
  for (int i=180; i>0;i--){
    pwmWrite(SERVO, map(i,0,180, LOWERLIMIT, UPPERLIMIT));
    delay(SERTIME);
  }
}
