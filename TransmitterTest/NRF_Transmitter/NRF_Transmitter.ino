// SimpleTx - the master or the transmitter

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


#define CE_PIN   9
#define CSN_PIN 10

const byte slaveAddress[5] = {'R','x','A','A','A'};


RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

typedef struct {
  byte yaw;
  byte pitch;
  byte roll;
  byte throttle;
}conData;

conData s = {0,127,127,0};
conData s2 = {127,127,127,0};
conData x = {127,127,127,127};



unsigned long currentMillis;
unsigned long prevMillis;
unsigned long txIntervalMillis = 1000; // send once per second


void setup() {

    Serial.begin(9600);

    Serial.println("SimpleTx Starting");

    radio.begin();
    radio.setDataRate( RF24_250KBPS );
    radio.setRetries(3,5); // delay, count
    radio.openWritingPipe(slaveAddress);
}



void loop() {
    radio.write(&s, sizeof(s));
    radio.write(&s2, sizeof(s2));
    radio.write(&x, sizeof(x));
}
