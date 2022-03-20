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
//sets the channel to transmit on
const byte slaveAddress[5] = {'R','x','A','A','A'};
//defines where the radio is connected
RF24 radio(CE_PIN, CSN_PIN);
//variable used that is sent via radio
conData sendData;
//variables used for transmit frequency
unsigned long currentMillis;
unsigned long prevMillis;
unsigned long txIntervalMillis = 1000; // send once per second
//==========================================

void setup() {
  //start the serial monitor
  Serial.begin(9600);
  Serial.println("SimpleTx Starting");
  //start the radio and set send rate
  radio.begin();
  radio.setDataRate( RF24_250KBPS );
  radio.setRetries(3,5); // delay, count
  radio.openWritingPipe(slaveAddress);
}

void loop() {
  // put your main code here, to run repeatedly:

}
