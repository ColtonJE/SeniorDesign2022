/*
 * Official Flight Code for Senior Design Team: Angelo Fatica, Colton Eisenreich, Seam McCray, Vishal Mansuria
 * Created Jan 7 2022
 * Handles all main flight functions
 */

#include <Servo.h>

  //Values for ESC pins
  byte escFL = 35;
  byte escFR = 33;
  byte escBL = 31;
  byte escBR = 29;
  // Initialize ESCs (Done as Servos to facilitate PWM signals)
  Servo ESC_FL;
  Servo ESC_FR;
  Servo ESC_BL;
  Servo ESC_BR;
  
void setup() {
  // Attach Servos to corresponding Pins
  ESC_FL.attach(escFL);
  ESC_FR.attach(escFR);
  ESC_BL.attach(escBL);
  ESC_BR.attach(escBR);
    
}

void loop() {
  // servo test
  int mSpeed = 1000;
  delay(2000);
  ESC_FR.writeMicroseconds(1000);
  ESC_FL.writeMicroseconds(1000);
  ESC_BR.writeMicroseconds(1000);
  ESC_BL.writeMicroseconds(1000);
  delay(2000);
  ESC_FR.writeMicroseconds(2000);
  ESC_FL.writeMicroseconds(2000);
  ESC_BR.writeMicroseconds(2000);
  ESC_BL.writeMicroseconds(2000);
  delay(3000);
  do{
    mSpeed += 100;
    ESC_FR.writeMicroseconds(mSpeed);
    ESC_FL.writeMicroseconds(mSpeed);
    ESC_BR.writeMicroseconds(mSpeed);
    ESC_BL.writeMicroseconds(mSpeed);
    delay(1000);
  }while( mSpeed < 2000 );
  ESC_FR.writeMicroseconds(1000);
  ESC_FL.writeMicroseconds(1000);
  ESC_BR.writeMicroseconds(1000);
  ESC_BL.writeMicroseconds(1000);
 exit(0);
}
