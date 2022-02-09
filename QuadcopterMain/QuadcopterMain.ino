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
  byte escBR = 31;
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
  // put your main code here, to run repeatedly:

}
