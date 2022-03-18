// SimpleRx - the slave or the receiver

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   9
#define CSN_PIN 10

const byte thisSlaveAddress[5] = {'R','x','A','A','A'};

RF24 radio(CE_PIN, CSN_PIN);

typedef struct {
  byte yaw;
  byte pitch;
  byte roll;
  byte throttle;
}conData;

conData Rx; // this must match dataToSend in the TX
bool newData = false;

//===========

void setup() {

    Serial.begin(9600);

    Serial.println("SimpleRx Starting");
    radio.begin();
    radio.setDataRate( RF24_250KBPS );
    radio.openReadingPipe(1, thisSlaveAddress);
    radio.startListening();
}

//=============

void loop() {
    getData();
    showData();
}

//==============

void getData() {
    if ( radio.available() ) {
        radio.read( &Rx, sizeof(Rx) );
        newData = true;
    }
}

void showData() {
    if (newData == true) {
        Serial.print("Data received ");
        Serial.println(Rx.yaw);
        Serial.println(Rx.pitch);
        Serial.println(Rx.roll);
        Serial.println(Rx.throttle);
        newData = false;
    }
}
