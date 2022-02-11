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
  // servo test
  delay(5000);
  while(true){
    ESC_FR.write(500);
    ESC_FL.write(500);
    ESC_BR.write(500);
    ESC_BL.write(500);
    delay(1000);
    ESC_FR.write(0);
    ESC_FL.write(0);
    ESC_BR.write(0);
    ESC_BL.write(0);
    delay(1000);
  }
}
