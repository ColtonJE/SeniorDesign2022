/*
 * Official controller code 
 */

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//Pin definitions ==========================
#define CE_PIN 9
#define CSN_PIN 10
#define LEFT 4
#define RIGHT 2
//==========================================

//Controller Data Struct ===================
typedef struct {
  byte yaw;
  byte pitch;
  byte roll;
  byte throttle;
  bool button_left;
  bool button_right;
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
  pinMode(LEFT, INPUT_PULLUP);
  pinMode(RIGHT, INPUT_PULLUP);
}

void loop() {
  //read the values from the joysticks
  //A0 = yaw, A1 = pitch, A2 = roll, A3 = throttle
  sendData.yaw      = map( analogRead(A0), 0, 1024, 255, 0 ); //map values inverted because joystick is upside down
  sendData.pitch    = map( analogRead(A1), 0, 1024, 0, 255 ); 
  sendData.roll     = map( analogRead(A2), 0, 1024, 0, 255 );
  sendData.throttle = map( analogRead(A3), 0, 1024, 0, 255 ); //map values inverted because joystick is upside down
  sendData.button_left = digitalRead(LEFT);
  sendData.button_right = digitalRead(RIGHT);
  //For testing ============================
//  Serial.println("Conroller Data: ");
//  Serial.print("Yaw: " );
//  Serial.print((int)sendData.yaw);
//  Serial.print("\nPitch: ");
//  Serial.print((int)sendData.pitch);
//  Serial.print("\nRoll: ");
//  Serial.print((int)sendData.roll);
//  Serial.print("\nThrottle: ");
//  Serial.print((int)sendData.throttle);
//  Serial.print("\n");
    Serial.print(sendData.button_left);
    Serial.print(" ");
    Serial.print(sendData.button_right);
    Serial.print("\n");
  //========================================
  //send data
  bool result;
  result = radio.write( &sendData, sizeof(sendData) );
  //check for acknowledgment ==============
//  if(result) Serial.println( "ACK" );
//  else Serial.println( "TxFailed" );
  //=======================================
//  delay(500);
}
