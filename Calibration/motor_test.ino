/*
 * This is for running an individual motor on a test stand or other apparatus. Open the serial monitor and enter the PWM pulse width value of choice between 1000 and 2000.
 * The value entered will be directly applied to the connected ESC, allowing for accurate control of pulse width. Be sure to consider the necessary ESC arming/calibration procedure
 * when using this sketch as it will still be necessary to follow the applicable procedure. Note that the initial pulse length in microseconds is set to 2000. 
 */


#include <Servo.h>

int us; // microsecond input from serial monitor
Servo ESC_M1;
Servo ESC_M2;
Servo ESC_M3;
Servo ESC_M4;

void setup() {
  Serial.begin(9600);
  ESC_M1.attach(30);
  ESC_M2.attach(32);
  ESC_M3.attach(34);
  ESC_M4.attach(36);
  us = 1000; //Initial pulse length
  Serial.print("Initial us value: ");
  Serial.println(us);
  Serial.println("Enter microseconds value between 1000 and 2000");
}

void loop() {
    while(!Serial.available()){}
    if(Serial.available()){
      us = Serial.parseInt();
      
      if(us > 2000)
        us = 2000;
        else if(us < 1000)
          us = 1000;
         
      Serial.println(us);
        while(Serial.available() > 0){
          Serial.read();
        }
      delay(10);
    }
   ESC_M1.writeMicroseconds(us);
   ESC_M2.writeMicroseconds(us);
   ESC_M3.writeMicroseconds(us);
   ESC_M4.writeMicroseconds(us);
}
