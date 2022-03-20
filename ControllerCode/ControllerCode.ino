/*
 * Official controller code 
 */

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//Pin definitions ==========================
#define CE_PIN 9
#define CSN_PIN 10
//==========================================

//Controller Data Struct ===================
typedef struct {
  byte yaw;
  byte pitch;
  byte roll;
  byte throttle;
}conData;
//==========================================

//Radio Setup ==============================
const byte thisSlaveAddress[5] = {'R','x','A','A','A'};

RF24 radio(CE_PIN, CSN_PIN);

conData dataRe
//==========================================

void setup() {
  

}

void loop() {
  // put your main code here, to run repeatedly:

}
