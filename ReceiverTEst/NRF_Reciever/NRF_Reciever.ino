// SimpleRx - the slave or the receiver
//Libraries =====================================
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
//=================================================

//Radio ===========================================
#define CE_PIN   25
#define CSN_PIN 23

const byte thisSlaveAddress[5] = {'R','x','A','A','A'};

RF24 radio(CE_PIN, CSN_PIN);

typedef struct {
  byte yaw;
  byte pitch;
  byte roll;
  byte throttle;
}conData;
typedef struct {
  int yaw;
  int pitch;
  int roll;
  int throttle;
}Data;

int M1, M2, M3, M4 = 0;

conData dataReceived; // this must match dataToSend in the TX
Data mapped;
Data x;
bool newData = false;
//===================================================

//Servo =============================================
//Values for ESC pins
byte escFL = 30;
byte escFR = 32;
byte escBL = 34;
byte escBR = 36;
// Initialize ESCs (Done as Servos to facilitate PWM signals)
Servo ESC_FL;
Servo ESC_FR;
Servo ESC_BL;
Servo ESC_BR;
//===================================================

void setup() {
  // Radio =========================================
  Serial.begin(9600);

  Serial.println("SimpleRx Starting");
  radio.begin();
  radio.setDataRate( RF24_250KBPS );
  radio.openReadingPipe(1, thisSlaveAddress);
  radio.startListening();
  //================================================

  //Servo Setup ====================================
  // Attach Servos to corresponding Pins
  ESC_FL.attach(escFL);
  ESC_FR.attach(escFR);
  ESC_BL.attach(escBL);
  ESC_BR.attach(escBR);

  ESC_FR.writeMicroseconds(1000);
  ESC_FL.writeMicroseconds(1000);
  ESC_BR.writeMicroseconds(1000);
  ESC_BL.writeMicroseconds(1000);

  delay(5000);
  //================================================
}

//=============

void loop() {
  
  getData();
  showData();
  M1 = mapped.throttle + mapped.yaw - mapped.pitch + mapped.roll;
  M2 = mapped.throttle - mapped.yaw - mapped.pitch - mapped.roll;
  M3 = mapped.throttle - mapped.yaw + mapped.pitch + mapped.roll;
  M4 = mapped.throttle + mapped.yaw + mapped.pitch - mapped.roll;
  
  ESC_FR.writeMicroseconds(1000 + minMax(M1,0,1000)+100);
  ESC_FL.writeMicroseconds(1000 + minMax(M1,0,1000));
  ESC_BR.writeMicroseconds(1000 + minMax(M1,0,1000)+100);
  ESC_BL.writeMicroseconds(1000 + minMax(M1,0,1000));

//  Serial.println( 
}

//==============

void getData() {
    if ( radio.available() ) {
        radio.read( &dataReceived, sizeof(dataReceived) );
        newData = true;
        mapped.yaw = map( dataReceived.yaw, 0, 255, -100, 100 );
        mapped.pitch = map( dataReceived.pitch, 0, 255, -100, 100 );
        mapped.roll = map( dataReceived.roll, 0, 255, -100, 100 );
        mapped.throttle = map(dataReceived.throttle, 0, 255, 100, 800 );
    }
}

void showData() {
    if (newData == true) {
        Serial.print("Data received ");
        Serial.print("\nYaw: " );
        Serial.print((int)dataReceived.yaw);
        Serial.print("\nPitch: ");
        Serial.print((int)dataReceived.pitch);
        Serial.print("\nRoll: ");
        Serial.print((int)dataReceived.roll);
        Serial.print("\nThrottle: ");
        Serial.print((int)dataReceived.throttle);
        Serial.print("\n");
        newData = false;
    }
}

int minMax(int value, int min_value, int max_value) {
    if (value > max_value) {
        value = max_value;
    } else if (value < min_value) {
        value = min_value;
    }

    return value;
}
